
## ConsoleUI、Game、RuleChecker 代码梳理

---

### 一、ConsoleUI —— 终端界面层

**职责**：所有和用户交互、显示有关的逻辑都集中在这里，与游戏逻辑完全解耦。

**设计方式**：全静态类（所有方法都是 `static`），不需要实例化，直接用类名调用。

**主要方法**：

| 方法 | 作用 |
|---|---|
| `print_board` | 打印 9×10 棋盘，y 轴从 9→0 倒序遍历 |
| `read_move` | 读取玩家输入，解析坐标或 `u/q` 命令 |
| `show_turn / show_check / show_checkmate` 等 | 显示各类游戏状态提示 |
| `clear_screen` | 跨平台清屏 |
| `get_piece_symbol` | 把棋子对象转成中文汉字符号 |
| `initialize_console` | 初始化控制台编码，只运行一次（用 `static bool` 守卫） |

**技术点**：

1. **跨平台编译隔离（`#ifdef _WIN32`）**  
   Windows 下用 WinAPI（`GetConsoleMode` / `SetConsoleMode` / `ENABLE_VIRTUAL_TERMINAL_PROCESSING`）开启虚拟终端；Linux/Mac 直接输出 ANSI 转义序列 `\x1b[2J\x1b[H`。两套路径用宏分离，编译时选一套。

2. **ANSI 转义色彩（ANSI Escape Codes）**  
   `\x1b[31m` = 红色，`\x1b[34m` = 蓝色，`\x1b[0m` = 重置。红方棋子显示红色，黑方显示蓝色。若控制台不支持则 `gUseColors = false` 降级为无色输出。

3. **UTF-8 控制台初始化**  
   Windows 下调 `SetConsoleOutputCP(CP_UTF8)` + `SetConsoleCP(CP_UTF8)` + `setlocale(LC_ALL, ".UTF-8")`，保证中文汉字（车马炮等）能正确输出到 Windows cmd/Terminal。

4. **输入解析用 `std::stringstream`**  
   `read_move` 把整行字符串放进 `std::stringstream`，再用 `>>` 依次提取 4 个整数坐标，失败则提示重新输入。支持 `u/undo`（悔棋）和 `q/quit`（退出）两个特殊命令，通过 `undo_request` 引用参数回传。

5. **单次初始化守卫（Static local flag）**  
   `initialize_console` 里用 `static bool initialized = false` 保证无论调用多少次，实际初始化逻辑只执行一次。

---

### 二、Game —— 游戏主控层

**职责**：管理整局游戏的状态机——谁走棋、走了什么、游戏是否结束、能不能悔棋。

**成员变量**：

```
Board board               // 当前棋盘状态
Stack<Board> board_history // 棋盘历史快照（用于悔棋）
Stack<char> side_history   // 当前方历史（用于悔棋）
RuleChecker rule_checker   // 规则检查器
std::vector<Move> history  // 每步棋的记录
char current_side          // 当前走棋方 'r' / 'b'
bool game_over
char winner
int step_count
```

**核心方法**：

**`run()`** —— 主游戏循环：
```
while (!game_over):
    clear_screen → 显示上一步消息 → print_board → show_turn
    → read_move → 处理悔棋/移动 → 收集 pending_message
游戏结束后显示最终棋盘和胜者
```
用 `pending_message` 字符串缓存上一步的结果文字，等下一帧 `clear_screen` 后再显示，避免清屏把提示抹掉。

**`try_move()`** —— 尝试走一步棋：
1. 调 `rule_checker.is_move_legal` 验证合法性
2. 若非法，额外检查是否是"会暴露将"导致的，设置 `caused_self_check` 给上层
3. 合法则把当前 `board` 和 `current_side` 压栈（为悔棋准备快照）
4. 创建 `Move` 记录、调 `board.move_chess` 实际移动
5. 检查将军/将死/逼将（stalemate），更新 `game_over` 和 `winner`

**`undo_last_move()`** —— 悔棋：
- 直接从 `board_history` 和 `side_history` 弹出快照恢复，`game_over` 重置为 false。

**技术点**：

1. **快照式悔棋（Snapshot Undo）**  
   每次合法移动前把整个 `Board` 对象拷贝压入 `Stack<Board>`。悔棋时弹出恢复，实现简单但内存代价是每步存一整张棋盘（32 个指针的深拷贝）。`Board` 实现了拷贝构造和赋值运算符，支持值语义。

2. **自定义泛型栈 `Stack<T>`**  
   手写模板栈，底层是堆分配数组，满时自动 `size *= 2` 扩容（类似 `std::vector` 的增长策略），完整实现了拷贝构造/赋值/析构（三法则），同时保存了两个 `Stack`（棋盘快照 + 当前方快照）以保持一致性。

3. **状态机设计**  
   `current_side`、`game_over`、`winner` 三个字段构成一个简单状态机。`switch_side()` 用三目运算符在 `'r'` 和 `'b'` 之间切换。

4. **关注点分离（SRP）**  
   `Game` 不知道任何棋子移动规则的细节，全部委托给 `RuleChecker`；不知道任何界面细节，全部委托给 `ConsoleUI`。`Game` 只负责协调流程。

---

### 三、RuleChecker —— 规则检查层

**职责**：所有象棋规则的判定，无状态（所有方法都是 `const`），每次接受 `Board` 引用做判断。

**主要方法调用关系**：

```
is_move_legal
 ├─ is_piece_move_legal     // 该棋子的走法规则
 │    ├─ count_pieces_between  // 统计路径上棋子数
 │    └─ is_in_palace          // 判断宫格范围
 ├─ Board::move_chess (在临时副本上试走)
 ├─ are_kings_facing        // 检查将帅对面
 └─ is_in_check             // 检查是否被将
      └─ can_piece_attack → is_piece_move_legal

is_checkmate = is_in_check && !has_any_legal_move
is_stalemate = !is_in_check && !has_any_legal_move
would_cause_self_check = are_kings_facing || is_in_check (试走后)
```

**各棋子规则实现（在 `is_piece_move_legal` 中）**：

| 棋子 | 规则要点 |
|---|---|
| 车（rook） | 直线走，路径上无阻挡（`count_pieces_between == 0`） |
| 炮（cannon） | 直线走，移动时路径无阻；**吃子必须隔一个棋子**（`pieces_between == 1`） |
| 马（horse） | 日字形，检查拐脚位是否有阻挡（"蹩马腿"） |
| 象（elephant） | 田字形，不能过河（红方 y≤4，黑方 y≥5），检查象眼阻挡 |
| 士（advisor） | 斜走一步，必须在宫格内（x∈[3,5]，y 按阵营限定） |
| 将/帅（king） | 一步横纵，必须在宫格内；特殊：允许"将吃将"（两将同列无阻直接对吃） |
| 兵/卒（pawn） | 未过河只能前进；过河后可左右移动（按阵营方向判断） |

**技术点**：

1. **试走验证（Simulation / "What-if" Check）**  
   `is_move_legal` 不直接判断走后状态，而是 `Board next_board = board`（触发深拷贝）在副本上 `move_chess`，然后检查副本上是否将帅对面或自己被将。这是象棋规则引擎的标准做法——先试走再验合法。

2. **暴力枚举合法走法（`has_any_legal_move`）**  
   遍历棋盘全部 90 个格子作为起点，再遍历全部 90 个格子作为终点，对每个组合调 `is_move_legal`。最坏 90×90=8100 次调用，每次内部还有一次棋盘深拷贝。逻辑正确但性能较重，对于 90 格的象棋棋盘实际上可接受。

3. **将帅对面规则（`are_kings_facing`）**  
   找到双方将帅坐标，判断同列 + 之间无棋子，是象棋特有规则，单独抽成一个方法，在试走验证和 `would_cause_self_check` 里复用。

4. **无状态设计（Stateless）**  
   `RuleChecker` 没有任何成员变量，所有方法都接受 `const Board&` 参数，`const` 修饰。天然线程安全，也方便在 `is_move_legal` 里创建 Board 副本、反复调用自身而不产生副作用。

5. **`count_pieces_between` 的通用性**  
   只处理同行/同列两种情况（步进方向用符号决定），返回路径上的棋子数。车、炮、将帅对面检查、马象的阻挡判断都复用这一方法，而不是各自写循环。

---

### 整体架构总结

```
main
 └─ Game::run()          ← 游戏主控
      ├─ ConsoleUI        ← 所有 I/O
      ├─ Board            ← 棋盘数据（深拷贝支持快照）
      ├─ RuleChecker      ← 无状态规则引擎
      ├─ Stack<Board/char>← 手写泛型栈（悔棋快照）
      └─ vector<Move>     ← 棋步历史记录
```

三个模块分别对应经典的 **MVC** 中的不同层：`ConsoleUI` ≈ View，`Game` ≈ Controller，`RuleChecker` + `Board` ≈ Model。每层职责清晰，依赖方向单向，是这个项目设计上最值得肯定的地方。
