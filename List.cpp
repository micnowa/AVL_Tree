//
// Created by Michał Nowaliński on 19.10.2018.
//

#include <cstddef>
#include <stdexcept>

/**
 * An ordered collection. This collection allows access to elements
 * by position, as well as control on where elements are inserted.
 * Unlike sets, duplicate elements are permitted by this general
 * contract (if a subclass forbids duplicates, this should be
 * documented).
 *
 * Each element of type T is kept in a structure Node<T>. Each node
 * holds an element T and a pointer pointing to a node. The list keeps
 * one node, called head, which has a pointer to another node, which
 * has a node to another node and so on. This allows list to have access
 * to each element.
 *
 * @tparam T type of elements of the list
 */
template<typename T>
class List {
public:
    /**
     * Overwritten operator =
     * @return reference to the list
     */
    List<T> &operator=(const List<T> &);

    /**
     * Default destructor
     */
    ~List();

    /**
     * Adds element to an end of the list
     * @param data element to be added
     */
    void push_back(T &&data);

    /**
     * Adds element to an end of the list
     * @param data element to be added
     */
    void push_back(T const &data);

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
    T &front();

    /**
     * Returns first element of the list.
     * @return first element of the list
     */
    T const &front() const;

    /**
     * Returns element of given index.
     * @param index number of element to be returned
     * @return element of given index
     */
    T &at(T index);

    /**
     * Returns element of given index.
     * @param index number of element to be returned
     * @return element of given index
     */
    T const &at(T index) const;

    /**
     * Overwritten operator []. Enables list to return object using arrays' notation
     * @param index number of element to be returned
     * @return element of given index
     */
    T &operator[](T index);

    /**
     * Overwritten operator []. Enables list to return object using arrays' notation
     * @param index number of element to be returned
     * @return element of given index
     */
    T const &operator[](T index) const;

private:
    /**
     * Element of a list. Data structure used for holding data of type T.
     * It has a pointer to another Element, so the list having access to
     * header Element has the access to all elements.
     */
    struct Element {
        /**
         * Data object
         */
        T data;
        /**
         * Pointer to another Element
         */
        Element *next;

        /**
         * Constructor with arguments
         *
         * @param data data of Element
         * @param next pointer to next Element
         */
        Element(T const &data, Element *next) : data(data), next(next) {}

        /**
         * Constructor with arguments
         *
         * @param data data of Element
         * @param next pointer to next Element
         */
        Element(T &&data, Element *next) : data(std::move(data)), next(next) {}
    };

    /**
     * Size of the list, in other words number of elements
     */
    size_t elements = 0;
    /**
     * Pointer to first element of the list
     */
    Element *head = nullptr;
    /**
     * Pointer to last element of the list
     */
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