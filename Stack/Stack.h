#pragma once

#include <iostream>

#define MAXSTACKSIZE 100

template <typename T>
class Stack
{
public:
  Stack(int s = 0);
  Stack(const Stack& other);
  ~Stack();
  const Stack& operator=(const Stack& other);
  void push(T element);
  T pop();
  T get_top_element();

private:
  T* top_ptr;
  T* buttome_ptr;
  int length;
  int size;
  T* type;
};

template <typename T>
Stack<T>::Stack(int s)
{
  length = 0;
  size = (s > 0) ? s : MAXSTACKSIZE;
  buttome_ptr = new T[size];
  top_ptr = buttome_ptr;
  type = nullptr;
}

template <typename T>
Stack<T>::~Stack()
{
  delete[] buttome_ptr;
  top_ptr = nullptr;
  buttome_ptr = nullptr;
}

template <typename T>
Stack<T>::Stack(const Stack& other)
{
  length = other.length;
  size = other.size;
  buttome_ptr = new T[size];
  for (int i = 0; i < length; ++i) {
    buttome_ptr[i] = other.buttome_ptr[i];
  }
  top_ptr = buttome_ptr + length;
  type = nullptr;
}

template <typename T>
const Stack<T>& Stack<T>::operator=(const Stack& other)
{
  if (this != &other) {
    T* new_buffer = new T[other.size];
    for (int i = 0; i < other.length; ++i) {
      new_buffer[i] = other.buttome_ptr[i];
    }
    delete[] buttome_ptr;
    buttome_ptr = new_buffer;
    top_ptr = buttome_ptr + other.length;
    length = other.length;
    size = other.size;
  }
  return *this;
}

template <typename T>
void Stack<T>::push(T element)
{
  if (top_ptr - buttome_ptr == size) {
    int old_size = size;
    size *= 2;
    T* temp = buttome_ptr;
    buttome_ptr = new T[size];
    for (int i = 0; i < old_size; ++i) {
      buttome_ptr[i] = temp[i];
    }
    top_ptr = buttome_ptr + old_size;
    delete[] temp;
  }
  *top_ptr = element;
  ++top_ptr;
  ++length;
}

template <typename T>
T Stack<T>::pop()
{
  if (buttome_ptr == top_ptr) {
    std::cout << "Empty stack." << std::endl;
    return T();
  }
  --top_ptr;
  --length;
  return *top_ptr;
}

template <typename T>
T Stack<T>::get_top_element()
{
  if (buttome_ptr == top_ptr) {
    std::cout << "Empty stack." << std::endl;
    return T();
  }
  return *(top_ptr - 1);
}