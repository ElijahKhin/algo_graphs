#ifndef CONTAINERLIST_HPP
#define CONTAINERLIST_HPP
#include <iostream>

template <typename T>
class ContainerList {
 private:
  ContainerList *next;
  const T data;

 public:
  T getData();
  void setNext(ContainerList *next);
  ContainerList *getNext();
  ContainerList(T data);
};

#endif
