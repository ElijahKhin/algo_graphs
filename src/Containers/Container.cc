#include "Container.h"

template <typename T>
Container<T>::Container() : len(0) {
  this->head = nullptr;
}

template <typename T>
int Container<T>::length() {
  return this->len;
}

template <typename T>
void Container<T>::showData() {
  ContainerList<T> *buf = this->head;
  while (buf) {
    std::cout << buf->getData() << "  ";
    buf = buf->getNext();
  }
  std::cout << "\n";
}

template <typename T>
T Container<T>::peek() {
  return this->head->getData();
}

template <typename T>
T Container<T>::pop() {
  if (this->len == 0) throw std::runtime_error("Length is zero");
  T dataBuf = this->head->getData();
  ContainerList<T> *pointBuf = this->head;
  this->head = this->head->getNext();
  delete pointBuf;
  this->len--;
  return dataBuf;
}

template <typename T>
Container<T>::~Container() {}

template class Container<int>;
