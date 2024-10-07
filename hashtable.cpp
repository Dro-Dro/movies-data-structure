#include "hashtable.h"

template <class T> HashTable<T>::HashTable() {

  for (int i = 0; i < MAXHASHSIZE; i++)
    array[i] = nullptr;
}

// destructor
template <class T> HashTable<T>::~HashTable() {
  node *curr;
  node *next;
  for (int i = 0; i < MAXHASHSIZE; i++) {
    curr = array[i];
    while (curr != nullptr) {
      delete curr->data;
      curr->data = nullptr;
      next = curr->next;
      if (curr != nullptr) {
        delete curr;
      }
      curr = next;
    }
    array[i] = nullptr;
  }
}

// finding item in hashtable
template <class T> T *HashTable<T>::retrieve(string key) {
  int num = 0;
  for (int i = 0; i < key.length(); i++) {
    num += key[i];
  }
  int index = hash(num);
  node *curr;
  curr = array[index];
  if (curr == nullptr) {
    return nullptr;
  }
  if (curr->key == key)
    return curr->data;
  while (curr->next != nullptr) {
    if (curr->next->key == key)
      return curr->next->data;
    curr = curr->next;
  }
  return nullptr;
}

template <class T> void HashTable<T>::insertItem(string key, T *data) {
  int num = 0;
  for (int i = 0; i < key.length(); i++) {
    num += key[i];
  }
  int index = hash(num);
  if (array[index] != nullptr) {
    node *curr;
    curr = array[index];
    if (curr->data == nullptr) {
      curr->data = data;
      curr->key = key;
    }
    while (curr->next != nullptr) {
      if (curr->next->data == nullptr) {
        curr->next->data = data;
        curr->next->key = key;
        return;
      }
      curr = curr->next;
    }
    curr->next = new node(data, nullptr, key);
  } else {
    array[index] = new node(data, nullptr, key);
  }
}

template <class T> void HashTable<T>::deleteItem(string key) {
  if (retrieve(key) != nullptr)
    delete retrieve(key);
}

// show all contents in hashtable
template <class T> void HashTable<T>::printHash() {
  for (int i = 0; i < MAXHASHSIZE; i++)
    if (array[i] != nullptr)
      cout << *array[i]->data << endl;
}

template <class T> int HashTable<T>::hash(int ID) { return ID % MAXHASHSIZE; }
