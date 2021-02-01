#include <iostream>

#ifndef P_UTILS
#define P_UTILS


namespace
{
    template <typename T>
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
        Node<T> *getNext() const;
        void setNext(Node<T> *next);
        bool hasNext() const;
        bool operator==(Node<T> other);
    };

    template <typename T>
    class List
    {
        Node<T> *head;
        int size;
        Node<T> *getHead() const;

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

    template <typename K, typename V>
    class HashNode
    {
    public:
        K key;
        V value;
        HashNode();
        HashNode(K key, V value);
        ~HashNode();
    };

    template <typename K, typename V>
    class HashMap
    {
        int size;
        List<HashNode<K, V>> buckets[16];
        int getBucketIndex(K key) const;

    public:
        HashMap();
        ~HashMap();
        int getSize() const;
        void put(K key, V value);
        V get(K key) const;
        void remove(K key);
        bool containsKey(K key) const;
    };

    template <typename T>
    class MinHeap
    {
        T *head;
        int size;
        int capacity;
        void resize();
        int parent(int i) const;
        int leftChild(int i) const;
        int rightChild(int i) const;
        void swap(int i, int j);
        void heapifyDown(int i);

    public:
        MinHeap();
        ~MinHeap();
        int getSize() const;
        bool isEmpty() const;
        void show() const;
        void add(T value);
        T pop();
    };

    template <typename T>
    class TreeNode
    {
        T value;
        TreeNode<T> *left;
        TreeNode<T> *right;

    public:
        // Constructors
        TreeNode();
        TreeNode(T value);
        TreeNode(T value, TreeNode<T> *left, TreeNode<T> *right);

        // Cope only the value from the other node. Not its children!
        TreeNode(const TreeNode<T> &node);

        // Destructor
        ~TreeNode();

        // Getters and setters
        T getValue() const;
        void setValue(T &value);
        TreeNode<T> * getLeft() const;
        TreeNode<T> * getRight() const;
        void setLeft(TreeNode<T> *left);
        void setRight(TreeNode<T> *right); 
    };
}

#endif
