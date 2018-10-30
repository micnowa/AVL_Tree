//
// Created by Michał Nowaliński on 17.10.2018.
//

#include "List.cpp"

/**
 *
 * @tparam a0
 * @tparam a1
 */
template <typename a0, typename a1>
class Sequence {
public:
    List<a0> keys;
    List<a1> infos;

    Sequence(const List<a0> &keys, const List<a1> &infos) : keys(keys), infos(infos) {}

    Sequence() = default;

    const List<a0> &getKeys() const {
        return keys;
    }

    void setKeys(const List<a0> &keys) {
        Sequence::keys = keys;
    }

    const List<a1> &getInfos() const {
        return infos;
    }

    void setInfos(const List<a1> &infos) {
        Sequence::infos = infos;
    }
};