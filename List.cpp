//
// Created by Michał on 19.10.2018.
//

#include <cstddef>
#include <stdexcept>

template<typename T>
class List {
public:
    List<T> &operator=(const List<T> &);

    ~List();

    /* Modifiers */
    void push_back(T &&data);

    void push_back(T const &data);

    void push_front(T &&data);

    void push_front(T const &data);

    void pop_back();

    void pop_front();

    void swap(List &x);

    void clear();

    /* Iterators */
    typedef T *iterator;
    typedef T *const const_iterator;

    const_iterator begin() const; // cbegin
    iterator begin();

    const_iterator end() const; //cend()
    iterator end();

    const_iterator rbegin() const;

    iterator rbegin();

    const_iterator rend() const;

    iterator rend();

    /* Capacity */
    size_t size() const;

    bool empty() const;

    /* Element Access */
    T &front();

    T const &front() const;

    T &back();

    T const &back() const;

    T &at(T const indx);

    T const &at(T const indx) const;

    T &operator[](T const indx);

    T const &operator[](T const indx) const;

private:
    struct node {
        T key;
        T info;
        node *next, *prev;

        node(T const &data, node *next, node *prev)
                : key(data), next(next), prev(prev) {
        }

        node(T &&data, node *next, node *prev)
                : key(std::move(data)), next(next), prev(prev) {
        }
    };

    int elements = 0;
    node *head = nullptr;
    node *tail = nullptr;
};

template<typename T>
List<T> &List<T>::operator=(const List<T> &that) {
    node *tmp = head;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    elements = that.elements;
    head = that.head;
    tail = that.tail;
}

template<typename T>
List<T>::~List() {
    node *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}


template<typename T>
T &List<T>::front() {
    if (head == nullptr)
        throw std::runtime_error("Invalid Action!");
    return head->key;
}

template<typename T>
T const &List<T>::front() const {
    if (head == nullptr)
        throw std::runtime_error("Invalid Action!");
    return head->key;
}

template<typename T>
T &List<T>::back() {
    if (tail == nullptr)
        throw std::runtime_error("Invalid Action!");
    return tail->key;
}

template<typename T>
T const &List<T>::back() const {
    if (tail == nullptr)
        throw std::runtime_error("Invalid Action!");
    return tail->key;
}

template<typename T>
void List<T>::push_back(T const &data) {
    node *newNode = new node(data, nullptr, tail);
    if (head == nullptr)
        head = newNode;
    if (tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    ++elements;
}

template<typename T>
void List<T>::push_back(T &&data) {
    node *newNode = new node(std::move(data), nullptr, tail);
    if (head == nullptr)
        head = newNode;
    if (tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    ++elements;
}

template<typename T>
void List<T>::push_front(T const &data) {
    node *newNode = new node(data, head, nullptr);
    if (tail == nullptr)
        tail = newNode;
    if (head != nullptr)
        head->prev = newNode;
    head = newNode;
    ++elements;
}

template<typename T>
void List<T>::push_front(T &&data) {
    node *newNode = new node(data, head, nullptr);
    if (tail == nullptr)
        tail = newNode;
    if (head != nullptr)
        head->prev = newNode;
    head = newNode;
    ++elements;
}

template<typename T>
void List<T>::pop_front() {
    if (head == nullptr)
        throw std::runtime_error("Invalid Action");
    node *tmp = head;
    head = head->next;
    if (head != nullptr)
        head->prev = nullptr;
    --elements;
    delete tmp;
}

template<typename T>
void List<T>::pop_back() {
    if (tail == nullptr)
        throw std::runtime_error("Invalid Action");
    node *tmp = tail;
    tail = tail->prev;
    if (tail != nullptr)
        tail->next = nullptr;
    --elements;
    delete tmp;
}

template<typename T>
bool List<T>::empty() const {
    return head == nullptr;
}

template<typename T>
size_t List<T>::size() const {
    return elements;
}

template<typename T>
T &List<T>::operator[](T const indx) {
    int cont = 0;
    node *curr = head;
    while (curr) {
        if (cont == indx)
            return curr->key;
        curr = curr->next;
        ++cont;
    }
    return nullptr;
}

template<typename T>
T const &List<T>::operator[](T const indx) const {
    int cont = 0;
    node *curr = head;
    while (curr) {
        if (cont == indx)
            return curr->key;
        curr = curr->next;
        ++cont;
    }
    return nullptr;
}

template<typename T>
T &List<T>::at(T const indx) {
    int cont = 0;
    node *curr = head;
    while (curr) {
        if (cont == indx)
            return curr->key;
        curr = curr->next;
        cont++;
    }
//    return (T)NULL;
}

template<typename T>
T const &List<T>::at(T const indx) const {
    int cont = 0;
    node *curr = head;
    while (curr) {
        if (cont == indx)
            return curr->key;
        curr = curr->next;
        cont++;
    }
//    return (T) NULL;
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return head;
}

template<typename T>
typename List<T>::iterator List<T>::begin() {
    return head;
}


template<typename T>
typename List<T>::const_iterator List<T>::end() const {
    return tail;
}

template<typename T>
typename List<T>::const_iterator List<T>::rbegin() const {
    return tail;
}

template<typename T>
typename List<T>::iterator List<T>::rbegin() {
    return tail;
}

template<typename T>
typename List<T>::const_iterator List<T>::rend() const {
    return head;
}

template<typename T>
typename List<T>::iterator List<T>::rend() {
    return head;
}

template<typename T>
typename List<T>::iterator List<T>::end() {
    return tail;
}

template<typename T>
void List<T>::swap(List &that) {
    std::swap(head, that.head);
    std::swap(tail, that.tail);
    std::swap(elements, that.elements);
}

template<typename T>
void List<T>::clear() {
    node *curr = head;
    while (head) {
        curr = head;
        head = head->next;
        delete curr;
    }
    head = tail = nullptr;
    elements = 0;
}