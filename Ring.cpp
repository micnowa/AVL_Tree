//
// Created by micha on 27-Nov-18.
//

#include <iostream>
#include <string>

using namespace std;

template<typename t1, typename t2>
class Ring {
    struct Element {
        t1 key;
        t2 info;
        Element *next;
        Element *prev;

        friend ostream &operator<<(ostream &output, const Element &show) {
            output << show.key << " " << show.info << endl;
            return output;
        }
    };

    Element *head;

public:
    template<typename K, typename I>
    class Iterator {
        Element *it;
    public:
        Iterator() { it = nullptr; }

        Iterator(Element *node) { it = node; }

        ~Iterator() {}

        Iterator(const Iterator &cc) { it = cc.it; }

        Iterator operator=(const Iterator &rhs) {
            if (this == &rhs) return *this;
            it = rhs.it;
            return *this;
        }

        Iterator operator+(int length) {
            if (length > 0)for (int i = 0; it && it->next && i < length; i++) it = it->next;
            return *this;
        }

        Iterator operator-(int length) {
            if (length > 0)for (int i = 0; it && it->next && i < length; i++) it = it->prev;
            return *this;
        }

        Iterator &operator++() {
            if (!it) it = it->next;
            return *this;
        }

        Iterator &operator++(int) {
            if (!it) return *this;
            else {
                auto *temporary = new Iterator(it);
                it = it->next;
                return *temporary;
            }
        }

        Iterator &operator--() {
            if (it) it = it->prev;
            return *this;
        }

        Iterator &operator--(int) {
            if (!it) return *this;
            else {
                auto *temporary = new Iterator(it);
                it = it->prev;
                return *temporary;
            }
        }

        bool operator==(Iterator iterator) const { return it == iterator.it; }

        bool operator!=(Iterator iterator) const { return it != iterator.it; }

        Element &operator*() const { return *it; }

        Element *operator->() const { return it; }

        Element *getIterator() { return it; }

        t1 getKey() { return it->key; }

        t2 getInfo() { return it->info; }

        friend ostream &operator<<(ostream &output, const Iterator &iter) {
            output << *iter;
            return output;
        }

    };

    typedef Iterator<t1, t2> RingIterator;
    typedef Iterator<const t1, const t2> ConstRingIterator;

    RingIterator begin() { return RingIterator(head); }

    RingIterator end() { return RingIterator(head); }

    RingIterator last() { return !head ? RingIterator(nullptr) : RingIterator(head->prev); }

    RingIterator find(const t1 &value) {
        for (RingIterator iter = begin(); iter != last(); ++iter) if (iter->key == value) return iter;
        return RingIterator(nullptr);
    }

    ConstRingIterator constBegin() const { return ConstRingIterator(head); }

    ConstRingIterator constEnd() const { return ConstRingIterator(head); }

    ConstRingIterator constLast() const { return !head ? ConstRingIterator(nullptr) : ConstRingIterator(head->prev); }

    ConstRingIterator constFind(const t1 &value) const {
        for (ConstRingIterator iter = begin(); iter != last(); ++iter) if (iter->key == value) return iter;
        return ConstRingIterator(nullptr);
    }

    void print() {
        if (isEmpty()) cout << endl << "Empty Ring." << endl;
        else {
            auto iter = constBegin();
            cout << endl;
            do {
                cout << iter << endl;
                ++iter;
            } while (iter != constEnd());
        }
    }

    Ring() { head = nullptr; }

    ~Ring() { destroy(); }

    Ring(const Ring<t1, t2> &cc) {
        head = nullptr;
        if (!cc.isEmpty()) copy(cc);
    }

    Ring<t1, t2> &operator=(const Ring<t1, t2> &rhs) {
        if (this == &rhs) return *this;
        destroy();
        if (!rhs.isEmpty()) copy(rhs);
        return *this;
    }

    Element *getHead() const {
        return head;
    }

    void add(const t1 &key, const t2 &info) {
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

    void add(const ConstRingIterator &iter) { add(iter->key, iter->info); }

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

    void copy(const Ring<t1, t2> &tc) {
        Ring<t1, t2>::ConstRingIterator iter = tc.constBegin();
        do {
            add(iter);
            iter++;
        } while (iter != tc.constEnd());
    }

    bool isEmpty() const { return head == nullptr; }

    /*friend ostream &operator<<(ostream &output, const Ring &ring) {
        Iterator it
        output << show.key << " " << show.info << endl;
        return output;
    }*/
};
