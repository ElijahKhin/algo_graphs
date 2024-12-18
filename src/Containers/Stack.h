#ifndef STACK_HPP
#define STACK_HPP

#include "../Containers/Container.h"

template <typename T>
class Stack : public Container<T> {
 public:
  Stack();
  virtual ~Stack();
  void push(T value);
  Stack *init();
};

#endif
