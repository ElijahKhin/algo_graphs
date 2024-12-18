#include "ContainerList.h"

template <typename T>
ContainerList<T>::ContainerList(T data) : data(data) {
  // this->prev = nullptr;
  this->next = nullptr;
}

template <typename T>
T ContainerList<T>::getData() {
  return this->data;
}

// template<typename T>
// ContainerList<T> *ContainerList<T>::getPrev(){
//     return this->prev;
// }

template <typename T>
ContainerList<T> *ContainerList<T>::getNext() {
  return this->next;
}

// template<typename T>
// void ContainerList<T>::setPrev(ContainerList *prev){
//     this->prev = prev;
// }

template <typename T>
void ContainerList<T>::setNext(ContainerList *next) {
  this->next = next;
}

template class ContainerList<int>;
