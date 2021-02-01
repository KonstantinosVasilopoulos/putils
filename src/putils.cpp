#include "putils.h"

namespace
{
    template <typename T>
    Node<T>::Node(T value)
    {
        this->value = value;
        next = nullptr;
    }

    template <typename T>
    Node<T>::Node(T value, Node<T> *next)
    {
        this->value = value;
        this->next = next;
    }

    template <typename T>
    Node<T>::Node(const Node<T> &other)
    {
        value = other.getValue();
        next = other.getNext();
    }

    template <typename T>
    Node<T>::~Node()
    {
        // delete next;
    }

    template <typename T>
    T Node<T>::getValue() const
    {
        return value;
    }

    template <typename T>
    void Node<T>::setValue(T value)
    {
        this->value = value;
    }

    template <typename T>
    Node<T> *Node<T>::getNext() const
    {
        return next;
    }

    template <typename T>
    void Node<T>::setNext(Node<T> *next)
    {
        this->next = next;
    }

    template <typename T>
    bool Node<T>::hasNext() const
    {
        return next != nullptr;
    }

    template <typename T>
    bool Node<T>::operator==(Node<T> other)
    {
        return value == other.value;
    }

    template <typename T>
    List<T>::List()
    {
        head = nullptr;
        size = 0;
    }

    template <typename T>
    List<T>::List(const List<T> &other)
    {
        size = other.getSize();

        for (int i = 1; i < size; i++)
        {
            this->append(other.get(i));
        }
    }

    template <typename T>
    List<T>::~List()
    {
        // delete head;
    }

    template <typename T>
    Node<T> *List<T>::getHead() const
    {
        return head;
    }

    template <typename T>
    int List<T>::getSize() const
    {
        return size;
    }

    template <typename T>
    bool List<T>::isEmpty() const
    {
        return size == 0;
    }

    template <typename T>
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

    template <typename T>
    T List<T>::operator[](int index) const
    {
        T val = get(index);
        return val;
    }

    template <typename T>
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

    template <typename T>
    void List<T>::clear()
    {
        head = nullptr;
        size = 0;
    }

    template <typename T>
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

    template <typename T>
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

    template <typename K, typename V>
    HashNode<K, V>::HashNode()
    {
    }

    template <typename K, typename V>
    HashNode<K, V>::HashNode(K key, V value)
    {
        this->key = key;
        this->value = value;
    }

    template <typename K, typename V>
    HashNode<K, V>::~HashNode()
    {
    }

    template <typename K, typename V>
    int HashMap<K, V>::getBucketIndex(K key) const
    {
        std::size_t hashCode = std::hash<K>{}(key);
        int bucketIndex = hashCode & (size - 1);
        return bucketIndex;
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap()
    {
        size = 16;
    }

    template <typename K, typename V>
    HashMap<K, V>::~HashMap()
    {
    }

    template <typename K, typename V>
    int HashMap<K, V>::getSize() const
    {
        return size;
    }

    template <typename K, typename V>
    void HashMap<K, V>::put(K key, V value)
    {
        // Create a new node
        HashNode<K, V> *node = new HashNode<K, V>(key, value);

        // Find the index for the node and add it to its bucket
        int bucketIndex = getBucketIndex(key);
        buckets[bucketIndex].append(*node);
    }

    template <typename K, typename V>
    V HashMap<K, V>::get(K key) const
    {
        int bucketIndex = getBucketIndex(key);

        // Search all nodes in the bucket for the key
        for (int i = 0; i < buckets[bucketIndex].getSize(); i++)
        {
            if (key == buckets[bucketIndex][i].key)
                return buckets[bucketIndex][i].value;
        }

        // No such element found. Throw exception.
        std::cout << "No such element exception" << std::endl;
        exit(-1);
    }

    template <typename K, typename V>
    void HashMap<K, V>::remove(K key)
    {
        int bucketIndex = getBucketIndex(key);
        for (int i = 0; i < buckets[bucketIndex].getSize(); i++)
        {
            if (key == buckets[bucketIndex][i].key)
            {
                buckets[bucketIndex].remove(i);
                break;
            }
        }
    }

    template <typename K, typename V>
    bool HashMap<K, V>::containsKey(K key) const
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < buckets[i].getSize(); j++)
            {
                if (key == buckets[i][j].key)
                    return true;
            }
        }

        return false;
    }

    template <typename T>
    void MinHeap<T>::resize()
    {
        // Create new temp array
        T *temp = new T[capacity];
        int i;

        // Copy all elements from the main array to the temp one
        for (i = 0; i < size; i++)
        {
            temp[i] = head[i];
        }

        // Resize the main array
        capacity += 16;
        delete[] head;
        head = new T[capacity];

        // Copy all elements from the temp array to the main array
        for (i = 0; i < size; i++)
        {
            head[i] = temp[i];
        }
    }

    template <typename T>
    int MinHeap<T>::parent(int i) const
    {
        return (i - 1) / 2;
    }

    template <typename T>
    int MinHeap<T>::leftChild(int i) const
    {
        return 2 * i + 1;
    }

    template <typename T>
    int MinHeap<T>::rightChild(int i) const
    {
        return 2 * i + 2;
    }

    template <typename T>
    void MinHeap<T>::swap(int i, int j)
    {
        T temp = head[i];
        head[i] = head[j];
        head[j] = temp;
    }

    template <typename T>
    void MinHeap<T>::heapifyDown(int i)
    {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;

        if (left < size && head[left] < head[i])
            smallest = left;

        if (right < size && head[right] < head[smallest])
            smallest = right;

        // swap with child having lesser value and
        // call heapify-down on the child
        if (smallest != i)
        {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

    template <typename T>
    MinHeap<T>::MinHeap()
    {
        size = 0;
        capacity = 16;
        head = new T[capacity];
    }

    template <typename T>
    MinHeap<T>::~MinHeap()
    {
        delete[] head;
    }

    template <typename T>
    int MinHeap<T>::getSize() const
    {
        return size;
    }

    template <typename T>
    bool MinHeap<T>::isEmpty() const
    {
        return size == 0;
    }

    template <typename T>
    void MinHeap<T>::show() const
    {
        for (int i = 0; i < size; i++)
            std::cout << i << ": " << head[i] << " ";

        std::cout << std::endl;
    }

    template <typename T>
    void MinHeap<T>::add(T value)
    {
        // Check if the array needs to be resized
        if (size >= capacity)
            resize();

        // Insert element at the end of the heap
        head[size] = value;

        // Heapify up
        int index = size++;
        while (index > 0 && head[parent(index)] > head[index])
        {
            // Swap the element with its parent
            swap(index, parent(index));
            index = parent(index);
        }
    }

    template <typename T>
    T MinHeap<T>::pop()
    {
        if (isEmpty())
        {
            std::cout << "Heap is empty exception" << std::endl;
            exit(-1);
        }

        T returnValue = head[0];

        // Swap the final element with the first and delete the final
        head[0] = head[size - 1];
        size--;
        heapifyDown(0);

        return returnValue;
    }

    template <typename T>
    TreeNode<T>::TreeNode()
    {
        value = NULL;
        left = nullptr;
        right = nullptr;
    }

    template <typename T>
    TreeNode<T>::TreeNode(T value)
    {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    template <typename T>
    TreeNode<T>::TreeNode(T value, TreeNode<T> *left, TreeNode<T> *right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    template <typename T>
    TreeNode<T>::TreeNode(const TreeNode &node)
    {
        value = node.getValue();
        left = nullptr;
        right = nullptr;
    }

    template <typename T>
    TreeNode<T>::~TreeNode()
    {
        delete left;
        delete right;
    }

    template <typename T>
    T TreeNode<T>::getValue() const
    {
        return value;
    }

    template <typename T>
    void setValue(T &value)
    {
        this->value = value;
    }

    template <typename T>
    TreeNode<T> * TreeNode<T>::getLeft() const
    {
        return left;
    }

    template <typename T>
    TreeNode<T> * TreeNode<T>::getRight() const
    {
        return right;
    }

    template <typename T>
    void TreeNode<T>::setLeft(TreeNode<T> *left)
    {
        this->left = left;
    }

    template <typename T>
    void TreeNode<T>::setRight(TreeNode<T> *right)
    {
        this->right = right;
    }
}