#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "./Container.h"

template <typename T>
class Queue : public Container<T> {
 private:
  ContainerList<T> *tail;

 public:
  Queue();
  virtual ~Queue();
  void push(T value);
  Queue *init();
  T *fromQueueToArr();
  void operator+=(Queue &otherFixed);
};

#endif
