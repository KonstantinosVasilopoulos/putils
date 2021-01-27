#include "putils.h"

template<typename T>
Node<T>::Node(T value)
{
    this->value = value;
    next = nullptr;
}

template<typename T>
Node<T>::Node(T value, Node<T> *next)
{
    this->value = value;
    this->next = next;
}

template<typename T>
Node<T>::Node(const Node<T> &other)
{
    value = other.getValue();
    next = other.getNext();
}

template<typename T>
Node<T>::~Node()
{
    // delete next;
}

template<typename T>
T Node<T>::getValue() const
{
    return value;
}

template<typename T>
void Node<T>::setValue(T value)
{
    this->value = value;
}

template<typename T>
Node<T> * Node<T>::getNext() const
{
    return next;
}

template<typename T>
void Node<T>::setNext(Node<T> *next)
{
    this->next = next;
}

template<typename T>
bool Node<T>::hasNext() const
{
    return next != nullptr;
}

template<typename T>
bool Node<T>::operator==(Node<T> other)
{
    return value == other.value;
}


template<typename T>
List<T>::List()
{
    head = nullptr;
    size = 0;
}

template<typename T>
List<T>::List(const List<T> &other)
{
    size = other.getSize();

    for (int i = 1; i < size; i++)
    {
        this->append(other.get(i));
    }
}

template<typename T>
List<T>::~List()
{
    // delete head;
}

template<typename T>
Node<T> * List<T>::getHead() const
{
    return head;
}

template<typename T>
int List<T>::getSize() const
{
    return size;
}

template<typename T>
bool List<T>::isEmpty() const
{
    return size == 0;
}

template<typename T>
T List<T>::get(int index) const
{
    if (index >= size || index < 0)
    {
        std::cout << "Invalid index exception" << std::endl;
        exit(-1);
    }

    Node<T> *next = head;
    for (int i = 0; i < index; i++)
    {
        next = next->getNext();
    }

    return next->getValue();
}

template<typename T>
T List<T>::operator[](int index) const
{
    T val = get(index);
    return val;
}

template<typename T>
void List<T>::append(T value)
{
    Node<T> *newNode = new Node<T>(value);

    if (isEmpty())
    {
        head = newNode;
    }
    else
    {
        Node<T> *next = head;
        for (int i = 1; i < size; i++)
        {
            next = next->getNext();
        }

        next->setNext(newNode);
    }
    size++;
}

template<typename T>
void List<T>::clear()
{
    head = nullptr;
    size = 0;
}

template<typename T>
void List<T>::remove(int index)
{
    if (index >= size || index < 0)
    {
        std::cout << "Invalid index exception" << std::endl;
        exit(-1);
    }

    if (index == 0)
    {
        if (head->hasNext())
        {
            Node<T> *temp = head;
            head = head->getNext();
            delete temp;
        }
        else
        {
            delete head;
            head = nullptr;
        }
    }
    else
    {
        Node<T> *beforeNext;
        Node<T> *next = head;
        for (int i = 0; i < index; i++)
        {
            beforeNext = next;
            next = next->getNext();
        }

        if (next->hasNext())
        {
            beforeNext->setNext(next->getNext());
        }
        else
        {
            beforeNext->setNext(nullptr);
        }

        delete next;
    }

    size--;
}

template<typename T>
void List<T>::insert(int index, T value)
{
    if (index > size || index < 0)
    {
        std::cout << "Invalid index exception" << std::endl;
        exit(-1);
    }

    Node<T> *newNode;
    if (index == 0)
    {
        newNode = new Node<T>(value, head);
        head = newNode;
    }
    else
    {
        Node<T> *beforeNext;
        Node<T> *next = head;
        for (int i = 0; i < index; i++)
        {
            beforeNext = next;
            next = next->getNext();
        }

        // Create a new node and insert it between beforeNext and next
        if (beforeNext->hasNext())
        {
            newNode = new Node<T>(value, next);
        }
        else
        {
            newNode = new Node<T>(value);
        }

        beforeNext->setNext(newNode);
    }

    size++;
}
