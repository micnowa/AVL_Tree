//
// Created by Michał Nowaliński on 19.10.2018.
//

#include <iostream>
#include "Sequence.cpp"
using namespace std;

/**
 * shuffle produces new Sequence based on two sequences provided. It copies len1
 * number of elements of first sequence, starting from start1 offset. Then it adds
 * to the new sequence len2 number of elements of second sequence, starting from
 * start2 offset. Then the same action is performed on both sequences, but the
 * offset begins from the element following the element on which algorithm stopped
 * in both sequences, respectively. Number of copied elements is fixed. If algorithm
 * reached the end of first sequence it simply adds copied elements from second
 * sequence that remain to the end. This action is performed count number of times.
 *
 * @tparam key type of first parameter on which Sequence operates
 * @tparam info type of second parameter on which Sequence operates
 * @param s1 first sequence
 * @param start1 offset from first sequence
 * @param len1 number of copied elements form first sequence
 * @param s2 first sequence
 * @param start2 offset from second sequence
 * @param len2 number of copied elements form second sequence
 * @param count number of times of performed action
 * @return new Sequence built as described in the description
 */
template <typename key, typename info>
Sequence<key,info> shuffle(const Sequence<key, info> &s1, int start1, int len1,
                           const Sequence<key, info> &s2, int start2, int len2, int count) {
    List<key, info> elements1 = s1.getList();
    List<key, info> elements2 = s2.getList();
    List<key, info> elements3 = List<key, info>();

    for(int k=0; k < count; k++){
        int i = start1;
        int j = start2;
        while (i != elements1.size()) {
            for(int m=0; m<len1; m++) {
                elements3.push_back(elements1.at(i).getKey(), elements1.at(i).getInfo());
                i++;
                std::cout<<"1 list"<<std::endl;
                std::cout<<"i="<<i<<"   "<<"j="<<j<<std::endl;
            }
            for(int m=0; m<len2; m++) {
                elements3.push_back(elements2.at(j).getKey(), elements2.at(j).getInfo());
                j++;
                std::cout<<"i="<<i<<"   "<<"j="<<j<<std::endl;
            }
        }
        while (j != elements2.size()) {
            elements3.push_back(elements2.at(j).getInfo(), elements2.at(j).getInfo());
            j++;
            std::cout<<"i="<<i<<"   "<<"j="<<j<<std::endl;
        }
    }

    for (int l = 0; l < elements3.size(); ++l) {
        std::cout << elements3.at(l).getInfo() << std::endl;
    }

    return Sequence<key, info>(elements3);
}

int main() {
    cout << "Hello, World!" << endl;

    List<int, int> list1 = List<int, int>();
    List<int, int> list2 = List<int, int>();
    int s1_size = 8;
    int s2_size = 10;
    for (int i = 0; i < s1_size; i++) list1.push_back(i + 1, i + 1);
    for (int i = 0; i < s2_size; i++) list2.push_back(10 * (i + 1), 10 * (i + 1));
    for (int i = 0; i < s1_size; i++) cout << list1.at(i).getInfo() << endl;
    for (int i = 0; i < s2_size; i++) cout << list2.at(i).getInfo() << endl;

    Sequence<int, int> s1 = Sequence<int, int>(list1);
    Sequence<int, int> s2 = Sequence<int, int>(list2);

    Sequence<int, int> sequence = shuffle(s1, 2, 2, s2, 0, 3, 2);

    std::cout << "LOL" << std::endl;
    return 0;
}

