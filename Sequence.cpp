//
// Created by micha on 17.10.2018.
//

#include "List.cpp"

template <typename a0, typename a1>
class Sequence {
public:
    List<a0> keys;
    List<a1> infos;

    Sequence(const List<a0> &keys, const List<a1> &infos) : keys(keys), infos(infos) {}
    Sequence() {}

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