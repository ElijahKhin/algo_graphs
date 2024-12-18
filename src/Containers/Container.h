#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include "./ContainerList.h"

template <typename T>
class Container {
 protected:
  ContainerList<T> *head;
  int len;

 public:
  Container();
  virtual ~Container();
  virtual int length();
  virtual void showData();
  virtual T peek();
  virtual T pop();
};

#endif
