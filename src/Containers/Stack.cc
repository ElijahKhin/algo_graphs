#include "Stack.h"

template <typename T>
Stack<T>::Stack() : Container<T>() {}

template <typename T>
Stack<T> *Stack<T>::init() {
  return new Stack<T>();
}

template <typename T>
void Stack<T>::push(T value) {
  (void)value;
  if (this->len == 0)
    this->head = new ContainerList<T>(value);
  else {
    ContainerList<T> *buf = this->head;
    this->head = new ContainerList<T>(value);
    this->head->setNext(buf);
  }
  this->len++;
}

template <typename T>
Stack<T>::~Stack() {
  if (this->len > 0) {
    ContainerList<T> *buf;
    while (this->head) {
      buf = this->head;
      this->head = this->head->getNext();
      delete buf;
    }
  }
  this->len = 0;
}

template class Stack<int>;
