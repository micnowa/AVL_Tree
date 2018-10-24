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

    void push_back(T &&data);

    void push_back(T const &data);

    void pop_back();

    void pop_front();

    void swap(List &that);

    void clear();

    size_t size() const;

    bool empty() const;

    T &front();

    T const &front() const;

    T &get_last();

    T const &get_last() const;

    T &at(T index);

    T const &at(T index) const;

    T &operator[](T index);

    T const &operator[](T index) const;

private:
    struct Element {
        T data;
        Element *next;

        Element(T const &data, Element *next) : data(data), next(next) {}

        Element(T &&data, Element *next) : data(std::move(data)), next(next) {}
    };
    size_t elements = 0;
    Element *head = nullptr;
    Element *tail = nullptr;
};

template<typename T>
List<T> &List<T>::operator=(const List<T> &that) {
    Element *tmp;
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
    Element *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}


template<typename T>
T &List<T>::front() {
    if (head == nullptr)
        throw std::runtime_error("List is empty ...");
    return head->data;
}

template<typename T>
T const &List<T>::front() const {
    if (head == nullptr)
        throw std::runtime_error("Invalid Action!");
    return head->data;
}

template<typename T>
T &List<T>::get_last() {
    if (tail == nullptr)
        throw std::runtime_error("List is empty ...");
    return tail->data;
}

template<typename T>
T const &List<T>::get_last() const {
    if (tail == nullptr)
        throw std::runtime_error("List is empty ...");
    return tail->data;
}

template<typename T>
void List<T>::push_back(T const &data) {
    Element *newNode = new Element(data, nullptr);
    if (head == nullptr)
        head = newNode;
    if (tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    ++elements;
}

template<typename T>
void List<T>::push_back(T &&data) {
    Element *newNode = new Element(std::move(data), nullptr);
    if (head == nullptr)
        head = newNode;
    if (tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    ++elements;
}


template<typename T>
void List<T>::pop_front() {
    if (head == nullptr)
        throw std::runtime_error("Invalid Action");
    Element *tmp = head;
    head = head->next;
    --elements;
    delete tmp;
}

template<typename T>
void List<T>::pop_back() {
    if (tail == nullptr)
        throw std::runtime_error("Invalid Action");
    Element *tmp = tail;
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
T &List<T>::operator[](T const index) {
    int cont = 0;
    Element *curr = head;
    while (curr) {
        if (cont == index)
            return curr->data;
        curr = curr->next;
        ++cont;
    }
    return nullptr;
}

template<typename T>
T const &List<T>::operator[](T const index) const {
    int cont = 0;
    Element *curr = head;
    while (curr) {
        if (cont == index)
            return curr->data;
        curr = curr->next;
        ++cont;
    }
    return nullptr;
}

template<typename T>
T &List<T>::at(T const index) {
    int cont = 0;
    Element *curr = head;
    while (curr) {
        if (cont == index)
            return curr->data;
        curr = curr->next;
        cont++;
    }
}

template<typename T>
T const &List<T>::at(T const index) const {
    int cont = 0;
    Element *curr = head;
    while (curr) {
        if (cont == index)
            return curr->data;
        curr = curr->next;
        cont++;
    }
}

template<typename T>
void List<T>::swap(List &that) {
    std::swap(head, that.head);
    std::swap(tail, that.tail);
    std::swap(elements, that.elements);
}

template<typename T>
void List<T>::clear() {
    Element *curr;
    while (head) {
        curr = head;
        head = head->next;
        delete curr;
    }
    head = tail = nullptr;
    elements = 0;
}