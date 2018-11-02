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
    List<a0, a1> list;

    /**
     * Constructor with arguments
     * @param elements elements
     */
    Sequence(const List<a0, a1> &elements) : list(elements) {}

    /**
     * Default constructor
     */
    Sequence() = default;

    /**
     * Gets list
     * @return list
     */
    const List<a0, a1> &getList() const {
        return list;
    }

    /**
     * Sets list
     * @param list list
     */
    void setList(const List<a0, a1> &list) {
        Sequence::list = list;
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
};