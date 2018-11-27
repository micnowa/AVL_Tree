//
// Created by Michał Nowaliński on 19.10.2018.
//

#include <iostream>
#include "Shuffle.cpp"
#include "BST.cpp"
#include "Ring.cpp"

using namespace std;

void insertion_sort(int tab[], int size) {
    int temp, j;

    for (int i = 1; i < size; i++) {
        temp = tab[i];

        for (j = i - 1; j >= 0 && tab[j] > temp; j--)
            tab[j + 1] = tab[j];

        tab[j + 1] = temp;
    }
}

template<typename K, typename T>
Ring<K, T>
produce(Ring<K, T> ring1, int start1, int steps1, Ring<K, T> ring2, int start2, int steps2, int times, bool clockwise) {
    if (ring1.getHead() == nullptr || ring2.getHead() == nullptr) return Ring<K, T>();
    auto *ring = new Ring<K, T>();
    typename Ring<K, T>::RingIterator it1 = ring1.begin();
    typename Ring<K, T>::RingIterator it2 = ring2.begin();

    if (clockwise) {
        it1 + start1;
        it2 + start2;
        for (int i = 0; i < times; i++) {
            ring->add(it1.getInfo(), it1.getKey());
            ring->add(it2.getInfo(), it2.getKey());
            it1 + steps1;
            it2 + steps2;
        }
    } else {
        it1 - start1;
        it2 - start2;
        for (int i = 0; i < times; i++) {
            ring->add(it1.getInfo(), it1.getKey());
            ring->add(it2.getInfo(), it2.getKey());
            it1 - steps1;
            it2 - steps2;
        }
    }

    return *ring;
}


int main() {
    cout << "Hello, World!" << endl;
    Ring<int, int> ring1 = Ring<int, int>();
    Ring<int, int> ring2 = Ring<int, int>();

    for (int i = 1; i <= 20; ++i) ring1.add(i, i);
    for (int i = 1; i <= 20; ++i) ring2.add(100 * i, 100 * i);

    Ring<int, int> ring = Ring<int, int>();

    ring = produce(ring1, 10 - 1, 1, ring2, 5 - 1, 2, 10, true);

//    cout<<ring<<endl;
    int cokolwiek = 10000;
    return 0;
}

