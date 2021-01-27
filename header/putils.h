#include <iostream>

#ifndef P_UTILS
#define P_UTILS

template<typename T>
class Node
{
    T value;
    Node<T> *next;

public:
    Node(T value);
    Node(T value, Node<T> *next);
    Node(const Node<T> &other);
    ~Node();
    T getValue() const;
    void setValue(T value);
    Node<T> * getNext() const;
    void setNext(Node<T> *next);
    bool hasNext() const;
    bool operator==(Node<T> other);
};

template<typename T>
class List
{
    Node<T> *head;
    int size;
    Node<T> * getHead() const;

public:
    List();
    List(const List<T> &other);
    ~List();
    int getSize() const;
    bool isEmpty() const;
    T get(int index) const;
    T operator[](int index) const;
    void append(T value);
    void clear();
    void remove(int index);
    void insert(int index, T value);
};

#endif
