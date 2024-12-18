#include "Queue.h"

template <typename T>
Queue<T>::Queue() : Container<T>() {
  this->tail = nullptr;
}

template <typename T>
Queue<T> *Queue<T>::init() {
  return new Queue<T>();
}

template <typename T>
void Queue<T>::push(T value) {
  (void)value;
  if (this->len == 0)
    this->head = new ContainerList<T>(value);
  else if (this->len == 1) {
    this->tail = new ContainerList<T>(value);
    this->head->setNext(this->tail);
  } else {
    ContainerList<T> *buf = this->tail;
    this->tail = new ContainerList<T>(value);
    buf->setNext(this->tail);
  }
  this->len++;
}

template <typename T>
Queue<T>::~Queue() {
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

template <typename T>
void Queue<T>::operator+=(Queue<T> &otherQueue) {
  ContainerList<T> *buf = otherQueue.head;
  while (buf) {
    this->push(buf->getData());
    buf = buf->getNext();
  }
}

template <typename T>
T *Queue<T>::fromQueueToArr() {
  T *res = new T[this->length() + 1];
  int i = 0;
  ContainerList<T> *buf = this->head;
  while (buf) {
    res[i] = buf->getData();
    buf = buf->getNext();
    i++;
  }
  res[i] = (T)0;
  return res;
}

template class Queue<int>;
