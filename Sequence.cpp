//
// Created by Michał Nowaliński on 17.10.2018.
//

#include "List.cpp"

/**
 * Data structure that is used as an list adaptor.
 * @tparam a0
 * @tparam a1
 */
template <typename a0, typename a1>
class Sequence {
public:
    /**
     * list with keys and infos
     */
    MyRing<a0, a1> list;

    /**
     * Constructor with arguments
     * @param elements elements
     */
    Sequence(const MyRing<a0, a1> &elements) : list(elements) {}

    /**
     * Default constructor
     */
    Sequence() = default;

    /**
     * Gets list
     * @return list
     */
    const MyRing<a0, a1> &getList() const {
        return list;
    }


    /**
     * Returns info corresponding to key provided as the argument
     * @param key key
     * @return info associated with given key
     */
    a1 getInfo(a0 key) {
        for (int i = 0; i < list.size(); ++i) {
            if (list[i].getKey() == key) return list[i].getInfo();
        }
        return NULL;
    }

    /**
     * Adds an element
     * @param key key of the element
     * @param value value of the element
     */
    void addElement(a0 key, a1 value) {
        list.push_back(key, value);
    }

    /**
     * Gets element
     * @param index index of the element
     * @return element at given index
     */
    Element<a0,a1> getElement(int index) {
        return list.at(index);
    }

    Element<a0,a1> getElementByKy(a0 key) {
        for(int i= 0;i < list.size(); i++) if(list.getElement(i).getKey() == key) return list.getElement();
        return NULL;
    }

    /**
     * Compares two sequences
     * @param sequence sequence to compare
     * @return true if sequences are equal, false if they are not
     */
    bool compare(Sequence sequence) {
        int size = list.size();
        if(sequence.getList().size() != size) return false;
        for (int i = 0; i < size; ++i) {
            if(list.at(i).getKey() != sequence.getList().at(i).getKey()) return false;
            if(list.at(i).getInfo() != sequence.getList().at(i).getInfo()) return false;
        }
        return true;
    }

};