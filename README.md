 All three tasks are complete. Here's the full report:

---

## 任务1：清屏功能 ✅

已修改 `ConsoleUI/ConsoleUI.cpp` 的 `print_board()` 函数。在 Windows 上用 Win32 API（`FillConsoleOutputCharacter` + `SetConsoleCursorPosition`）清空整个控制台缓冲区；在其他平台用 ANSI 转义码 `\x1b[2J\x1b[H`。这比 `system("cls")` 更可靠，不会启动子进程，也不会影响颜色设置。构建已验证通过（exit code 0）。

---

## 任务2：ych 分支 vs main 分支的代码差异

两个分支在**架构层面**有根本差异，不是简单的功能差异：

### 架构差异（最重要）

| 方面 | main 分支（当前） | ych 分支 |
|---|---|---|
| **文件组织** | 按模块分子目录（`Board/`、`Game/`、`ConsoleUI/` 等） | 所有文件平铺在根目录 |
| **Board 存储方式** | `Chess pieces[32]` — **值类型数组**，Board 可直接复制 | `Chess* pieces[32]` — **指针数组**，涉及堆内存管理 |
| **get_chess() 返回值** | `Chess`（值） | `Chess*`（裸指针） |
| **Move 中的棋子** | `Chess eating_piece; Chess acting_piece;`（值） | `Chess* eaten_piece; Chess* acting_piece;`（裸指针） |
| **悔棋功能** | ✅ 有（`Stack<Board>`、`undo_last_move()`、`u` 命令） | ❌ 没有 |
| **RuleChecker** | ✅ 独立模块，完整规则检查（`is_move_legal`、`is_checkmate`、`is_stalemate`、`are_kings_facing`） | ❌ 没有 RuleChecker，规则逻辑分散在各棋子的 `is_legal()` 方法里 |
| **Stack** | ✅ 独立 Stack 模块用于悔棋历史 | ❌ 没有 |
| **Game::run() 的 read_move 签名** | `read_move(start, end, undo_request)` 带悔棋参数 | `read_move(start, end)` 不支持悔棋 |
| **ConsoleUI::get_piece_symbol 参数** | `const Chess&`（引用） | `const Chess*`（指针） |
| **King::is_legal()** | King 的移动逻辑在 RuleChecker 中，`King.cpp` 的 `is_legal` 已不被主流程使用 | King 的照将逻辑在 `King::is_legal()` 内，但逻辑有 bug（`return check_legal_a && check_legal_b && is_direct` 要求照将才能移动，明显错误） |

### 合并建议

ych 分支的核心代码（如某些棋子逻辑）可以参考，但**不能直接合并**，因为：
1. `Chess*` 指针 vs `Chess` 值这个根本差异会导致大量编译错误
2. main 分支的 RuleChecker 架构更健壮，ych 的 King::is_legal 有 bug
3. main 分支多了悔棋功能，合并时要保留

如果要合并，建议以 **main 为基础**，只从 ych 提取你需要的具体改动，手动移植。

---

## 任务3：将军检测逻辑分析与测试方法

### 现有将军检测流程

当前代码中将军检测已经完整实现，流程如下：

**检测链路**（`Game::try_move()` 执行移动后）：
```
Move 构造函数
  └─ checker.is_in_check(next_board, opponent)  → 设置 check_king 标志

Game::try_move() 执行后：
  ├─ history.back().get_check_king() == true
  │    └─ ConsoleUI::show_check(opponent)  →  输出 "Blue side is in check."
  ├─ rule_checker.is_checkmate(board, opponent)
  │    └─ is_in_check() && !has_any_legal_move()  → 将死
  └─ rule_checker.is_stalemate(board, opponent)
       └─ !is_in_check() && !has_any_legal_move()  → 困毙
```

`is_in_check()` 的实现是遍历所有敌方棋子，看任意一个是否能攻击到己方将/帅的位置，完全正确。

**控制台输出**：
- 将军时：`"Blue side is in check."` 或 `"Red side is in check."`（在移动记录行之后立即输出）
- 将死时：`"Blue side wins by checkmate."`（附带最终棋盘展示）
- 已就绪，不需要额外修改。


之前给的序列有误，抱歉。炮将军的规则是：**吃子时中间恰好1个炮架，移动到空格时中间必须0个棋子**。

验证将军最简便的完整步骤如下（红先）：

```
步1 红: 4 3 4 4    红中兵前进一格
步2 黑: 0 9 0 8    黑随便走（左车退一格）
步3 红: 4 4 4 5    红中兵再前进（未过河还不能横移，继续推）
步4 黑: 0 8 0 9    黑随便走
步5 红: 4 5 4 6    红中兵吃黑中卒(4,6)
步6 黑: 0 9 0 8    黑随便走
步7 红: 1 2 4 2    红左炮横移到x=4列
步8 黑: 0 8 0 9    黑随便走
步9 红: 4 2 4 9    红炮从(4,2)跳过(4,6)红兵，吃黑将(4,9) → 将死
```

第9步会触发 `Red side wins by checkmate.`（将死，黑将直接被吃）。

如果只想看**将军提示**而不是直接将死，可以改步7前先让黑将逃到(3,9)或(5,9)，但初始局面最简便的验证就是上面这9步直接将死。

注意：游戏实际使用 `RuleChecker::is_piece_move_legal` 而不是各棋子自己的 `is_legal` 方法，两者逻辑稍有不同，但炮的规则是一致的。

