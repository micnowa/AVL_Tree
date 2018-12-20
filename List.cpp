//
// Created by Michał Nowaliński on 19.10.2018.
//

#include <cstddef>
#include <stdexcept>

/**
 * Element of a list. Data structure used for holding data of type T.
 * It has a pointer to another Element, so the list having access to
 * header Element has the access to all elements.
 */
template<typename a0, typename a1>
struct Element {
    /**
     * Key
     */
    a0 key;

    /**
     * Info
     */
    a1 info;

    /**
     * Pointer to another Element
     */
    Element *next;

    /**
     * Constructor with arguments
     * @param dataKey key
     * @param dataInfo info
     * @param next pointer to the next Element
     */
    Element(a0 const &dataKey, a1 const &dataInfo, Element *next) : key(dataKey), info(dataInfo), next(next) {}

    /**
     * Constructor with arguments
     * @param key key
     * @param info info
     * @param next pointer to next Element
     */
    Element(a0 &&key, a0 &&info, Element *next) : key(std::move(key)), info(std::move(info)), next(next) {}

    /**
     * Return key
     * @return key
     */
    a0 getKey() const {
        return key;
    }

    /**
     * Returns info
     * @return info
     */
    a1 getInfo() const {
        return info;
    }
};


/**
 * An ordered collection. This collection allows access to elements
 * by position, as well as control on where elements are inserted.
 * Unlike sets, duplicate elements are permitted by this general
 * contract (if a subclass forbids duplicates, this should be
 * documented).
 * Each element of type T is kept in a structure Node<a0,a1>. Each node
 * holds an element T and a pointer pointing to a node. The list keeps
 * one node, called head, which has a pointer to another node, which
 * has a node to another node and so on. This allows list to have access
 * to each element.
 * @tparam a0 type of elements of the list
 */
template<typename a0, typename a1>
class MyRing {
private:


public:
    /**
     * Overwritten operator =
     * @return reference to the list
     */
    MyRing<a0, a1> &operator=(const MyRing<a0, a1> &);

    /**
     * Default destructor
     */
    ~MyRing();

    /**
     * Adds an element with given key and info
     * @param key key
     * @param info info
     */
    void push_back(a0 key, a1 info);

    /**
     * Clears the list destroying all its elements
     */
    void clear();

    /**
     * Returns lists's size
     * @return list's size
     */
    size_t size() const;

    /**
     * Checks if the list is empty
     * @return true of false depending on if the list is empty
     */
    bool empty() const;

    /**
     * Returns first element of the list.
     * @return first element of the list
     */
    Element<a0, a1> &front();

    /**
     * Returns first element of the list.
     * @return first element of the list
     */
    Element<a0, a1> const &front() const;

    /**
     * Returns element of given index.
     * @param index number of element to be returned
     * @return element of given index
     */
    Element<a0, a1> &at(int index);

    /**
     * Returns element of given index.
     * @param index number of element to be returned
     * @return element of given index
     */
    Element<a0, a1> const &at(int index) const;

    /**
     * Overwritten operator []. Enables list to return object using arrays' notation
     * @param index number of element to be returned
     * @return element of given index
     */
    Element<a0, a1> &operator[](int index);

    /**
     * Overwritten operator []. Enables list to return object using arrays' notation
     * @param index number of element to be returned
     * @return element of given index
     */
    Element<a0, a1> const &operator[](int index) const;

    /**
     * Size of the list, in other words number of elements
     */
    size_t elements = 0;
    /**
     * Pointer to first element of the list
     */
    Element<a0, a1> *head = nullptr;
    /**
     * Pointer to last element of the list
     */
    Element<a0, a1> *tail = nullptr;
};

template<typename a0, typename a1>
MyRing<a0, a1> &MyRing<a0, a1>::operator=(const MyRing<a0, a1> &that) {
    if (this == &that)
        return *this;
    Element<a0, a1> *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    elements = that.elements;
    head = that.head;
    tail = that.tail;
}

template<typename a0, typename a1>
MyRing<a0, a1>::~MyRing() {
    Element<a0, a1> *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}


template<typename a0, typename a1>
Element<a0, a1> &MyRing<a0, a1>::front() {
    if (head == nullptr)
        throw std::runtime_error("MyRing is empty ...");
    return *head;
}

template<typename a0, typename a1>
Element<a0, a1> const &MyRing<a0, a1>::front() const {
    if (head == nullptr)
        throw std::runtime_error("Invalid Action!");
    return *head;
}

template<typename a0, typename a1>
void MyRing<a0, a1>::push_back(a0 key, a1 info) {
    auto *newNode = new Element<a0, a1>(key, info, nullptr);
    if (head == nullptr)
        head = newNode;
    if (tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    tail->next = head;
    ++elements;
}

template<typename a0, typename a1>
bool MyRing<a0, a1>::empty() const { return head == nullptr; }

template<typename a0, typename a1>
size_t MyRing<a0, a1>::size() const { return elements; }

template<typename a0, typename a1>
Element<a0, a1> &MyRing<a0, a1>::operator[](int const index) {
    int cont = 0;
    Element<a0, a1> *curr = head;
    while (curr) {
        if (cont == index)
            return curr->key;
        curr = curr->next;
        ++cont;
    }
    return nullptr;
}

template<typename a0, typename a1>
Element<a0, a1> const &MyRing<a0, a1>::operator[](int const index) const {
    int cont = 0;
    Element<a0, a1> *curr = head;
    while (curr) {
        if (cont == index)
            return curr->key;
        curr = curr->next;
        ++cont;
    }
    return nullptr;
}

template<typename a0, typename a1>
Element<a0, a1> &MyRing<a0, a1>::at(int const index) {
    int cont = 0;
    Element<a0, a1> *curr = head;
    while (curr) {
        if (cont == index)
            return *curr;
        curr = curr->next;
        cont++;
    }
}

template<typename a0, typename a1>
Element<a0, a1> const &MyRing<a0, a1>::at(int const index) const {
    int cont = 0;
    Element<a0, a1> *curr = head;
    while (curr) {
        if (cont == index)
            return curr->key;
        curr = curr->next;
        cont++;
    }
}


template<typename a0, typename a1>
void MyRing<a0, a1>::clear() {
    Element<a0, a1> *curr;
    while (head) {
        curr = head;
        head = head->next;
        delete curr;
    }
    head = tail = nullptr;
    elements = 0;
}