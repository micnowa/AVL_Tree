//
// Created by Michał Nowaliński on 27-Nov-18.
//

#include <iostream>
#include <string>

using namespace std;
/**
 * Data structure that extends double linked list with feature that last elements
 * point to the first elements
 * @tparam t1 key
 * @tparam t2 info
 */
template<typename t1, typename t2>
class Ring {
    /**
     * Structure that holds an element of the list
     */
    struct Element {
        /**
         * key
         */
        t1 key;
        /**
         * info
         */
        t2 info;
        /**
         * pointer to next element
         */
        Element *next;
        /**
         * pointer to previous element
         */
        Element *prev;

        /**
         * Friend function used to printing iterator using cout
         * @param output
         * @param show
         * @return ostream
         */
        friend ostream &operator<<(ostream &output, const Element &show) {
            output << show.key << " " << show.info << endl;
            return output;
        }
    };

    /**
     * first element in the ring
     */
    Element *head;

public:
    /**
     * Class object that iterates throughout full ring.
     * @tparam K key
     * @tparam I info
     */
    template<typename K, typename I>
    class Iterator {
        Element *it;
    public:
        /**
         * Default constructor
         */
        Iterator() { it = nullptr; }

        /**
         * Constructor with element iterator points to
         * @param node
         */
        Iterator(Element *element) { it = element; }

        /**
         * Destructor
         */
        ~Iterator() {}

        /**
         * Copying constructor
         * @param cc iterator to be copied
         */
        Iterator(const Iterator &cc) { it = cc.it; }

        /**
         * Overwritten operator =
         * @param iterator iterator ro be asigned
         * @return object
         */
        Iterator operator=(const Iterator &iterator) {
            if (this == &iterator) return *this;
            it = iterator.it;
            return *this;
        }

        /**
         * Overwritten operator +. It moves iterator by length position forwards
         * @param length number by which iterator is moved forwards
         * @return iterator
         */
        Iterator operator+(int length) {
            if (length > 0)for (int i = 0; it && it->next && i < length; i++) it = it->next;
            return *this;
        }

        /**
         * Overwritten operator +. It moves iterator by length position backword
         * @param length number by which iterator is moved backword
         * @return iterator
         */
        Iterator operator-(int length) {
            if (length > 0)for (int i = 0; it && it->next && i < length; i++) it = it->prev;
            return *this;
        }

        /**
         * Overwritten operator ++. Moves forward by one
         * @return iterator
         */
        Iterator &operator++() {
            if (!it) it = it->next;
            return *this;
        }

        /**
         * Overwritten operator ++. Moves forward by one
         * @return iterator
         */
        Iterator &operator++(int) {
            if (!it) return *this;
            else {
                auto *temporary = new Iterator(it);
                it = it->next;
                return *temporary;
            }
        }

        /**
         * Overwritten operator --. Moves backword by one
         * @return iterator
         */
        Iterator &operator--() {
            if (it) it = it->prev;
            return *this;
        }

        /**
         * Overwritten operator --. Moves backword by one
         * @return iterator
         */
        Iterator &operator--(int) {
            if (!it) return *this;
            else {
                auto *temporary = new Iterator(it);
                it = it->prev;
                return *temporary;
            }
        }

        /**
         * Overwritten operator ==, compares to iterators
         * @param iterator iterator to be compared
         * @return true if iterators point to same object, false otherwise
         */
        bool operator==(Iterator iterator) const { return it == iterator.it; }

        /**
         * Overwritten operator ==, compares to iterators
         * @param iterator iterator to be compared
         * @return false if iterators point to same object, true otherwise
         */
        bool operator!=(Iterator iterator) const { return it != iterator.it; }

        /**
         * Overwritten operator *, return object via accessing pointer
         * @return iterator object
         */
        Element &operator*() const { return *it; }

        /**
         * Overwritten operator->. Used to access iterator pointer
         * @return iterator pointer
         */
        Element *operator->() const { return it; }

        /**
         * returns key
         * @return key
         */
        t1 getKey() { return it->key; }

        /**
         * returns info
         * @return info
         */
        t2 getInfo() { return it->info; }

        /**
         * Friend function used to printing ring using cout
         * @param output output
         * @param iter iterator
         * @return ostream
         */
        friend ostream &operator<<(ostream &output, const Iterator &iter) {
            output << *iter;
            return output;
        }

    };

    typedef Iterator<t1, t2> RingIterator;
    typedef Iterator<const t1, const t2> ConstRingIterator;

    /**
     * returns iterator to begin
     * @return begin iterator
     */
    RingIterator begin() { return RingIterator(head); }

    /**
     * returns iterator to end
     * @return end interator
     */
    RingIterator end() { return RingIterator(head); }

    /**
     * returns iterator to last element
     * @return iterator to last element
     */
    RingIterator last() { return !head ? RingIterator(nullptr) : RingIterator(head->prev); }

    /**
     * Searches for iterator with given value
     * @param value value
     * @return iterator with given value
     */
    RingIterator find(const t1 &value) {
        for (RingIterator iter = begin(); iter != last(); ++iter) if (iter->key == value) return iter;
        return RingIterator(nullptr);
    }

    /**
     * returns iterator pointing to the first element
     * @return iterator pointing to the first element
     */
    ConstRingIterator constBegin() const { return ConstRingIterator(head); }

    /**
     * returns iterator pointing to the last element
     * @return iterator pointing to the last element
     */
    ConstRingIterator constEnd() const { return ConstRingIterator(head); }

    /**
     * returns last iterator
     * @return last iterator
     */
    ConstRingIterator constLast() const { return !head ? ConstRingIterator(nullptr) : ConstRingIterator(head->prev); }

    /**
     * Look for iterator with given value
     * @param value value
     * @return iterator with given value
     */
    ConstRingIterator constFind(const t1 &value) const {
        for (ConstRingIterator iter = begin(); iter != last(); ++iter) if (iter->key == value) return iter;
        return ConstRingIterator(nullptr);
    }

    /**
     * default constructor
     */
    Ring() { head = nullptr; }

    /**
     * destroyer
     */
    ~Ring() { destroy(); }

    /**
     *
     * @param cc
     */
    Ring(const Ring<t1, t2> &cc) {
        head = nullptr;
        if (!cc.isEmpty()) copy(cc);
    }

    /**
     * Overwritten operator =
     * @param rhs to which ring ring is asigned
     * @return reference to the ring
     */
    Ring<t1, t2> &operator=(const Ring<t1, t2> &rhs) {
        if (this == &rhs) return *this;
        destroy();
        if (!rhs.isEmpty()) copy(rhs);
        return *this;
    }

    /**
     * return head
     * @return head
     */
    Element *getHead() const {
        return head;
    }

    /**
     * adds key and value to the ring at end
     * @param key key to be added
     * @param info infor to be added
     */
    void addEnd(const t1 &key, const t2 &info) {
        Element *adder = new Element;
        adder->key = key;
        adder->info = info;
        if (!head) {
            adder->next = adder;
            adder->prev = adder;
            head = adder;
            return;
        }
        adder->prev = head->prev;
        adder->next = head;
        adder->prev->next = adder;
        head->prev = adder;
    }

    /**
     * adds key and value to the ring at begin
     * @param key key to be added
     * @param info infor to be added
     */
    void addBegin(const t1 &key, const t2 &info) {
        Element *adder = new Element;
        adder->key = key;
        adder->info = info;
        if (!head) {
            adder->next = adder;
            adder->prev = adder;
            head = adder;
            return;
        }
        adder->next = head->next;
        adder->prev = head;
        adder->next->prev = adder;
        head->next = adder;
    }

    /**
     * add given key and value to the ring
     * @param iter iterator form which value and key are added
     */
    void add(const ConstRingIterator &iter) { addEnd(iter->key, iter->info); }

    /**
     * Removes given value form the ring
     * @param value value to be removed
     */
    void remove(const t1 &value) {
        if (isEmpty()) return;
        else {
            if (head->next == head || head->prev == head) {
                delete head;
                head = nullptr;
            } else {
                Element *before = head->prev;
                Element *after = head->next;
                before->next = after;
                after->prev = before;
                delete head;
                head = after;
            }
        }
    }

    /**
     * Destroys ring
     */
    void destroy() {
        while (!isEmpty()) {
            if (head->next == head || head->prev == head) {
                delete head;
                head = NULL;
            } else {
                Element *ptr = head->prev;
                Element *ntr = head->next;
                ptr->next = ntr;
                ntr->prev = ptr;
                delete head;
                head = ntr;
            }
        }
    }

    /**
     * Copies ring
     * @param ring ring to copy
     */
    void copy(const Ring<t1, t2> &ring) {
        Ring<t1, t2>::ConstRingIterator iter = ring.constBegin();
        do {
            add(iter);
            iter++;
        } while (iter != ring.constEnd());
    }

    /**
     * Returns true is ring is not empty, false if it is
     * @return true is ring is not empty, false if it is
     */
    bool isEmpty() const { return head == nullptr; }

    /**
     * Friend function used to printing ring using cout
     * @param output output
     * @param ring ring
     * @return ostream
     */
    friend ostream &operator<<(ostream &output, const Ring &ring) {
        Ring<t1, t2>::ConstRingIterator iterator = ring.constBegin();
        do {
            output << iterator.getKey() << " " << iterator.getInfo() << endl;
            iterator++;
        } while (iterator != ring.constEnd());

        return output;
    }
};
