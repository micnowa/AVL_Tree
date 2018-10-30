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
    List<key> keys1 = s1.getKeys();
    List<key> keys2 = s2.getKeys();
    List<key> keys3 = List<key>();
    List<info> info1 = s1.getInfos();
    List<info> info2 = s2.getInfos();
    List<info> info3 = List<info>();

    for(int k=0; k < count; k++){
        int i = start1;
        int j = start2;
        while(i!=keys1.size()) {
            for(int m=0; m<len1; m++) {
                keys3.push_back(keys1.at(i));
                info3.push_back(info1.at(i));
                i++;
                std::cout<<"1 list"<<std::endl;
                std::cout<<"i="<<i<<"   "<<"j="<<j<<std::endl;
            }
            for(int m=0; m<len2; m++) {
                keys3.push_back(keys2.at(j));
                info3.push_back(info2.at(j));
                j++;
                std::cout<<"i="<<i<<"   "<<"j="<<j<<std::endl;
            }
        }
        while(j!=keys2.size()) {
            keys3.push_back(keys2.at(j));
            info3.push_back(info2.at(j));
            j++;
            std::cout<<"i="<<i<<"   "<<"j="<<j<<std::endl;
        }
    }

    for (int l = 0; l < keys3.size(); ++l) {
        std::cout<<keys3.at(l)<<std::endl;
    }

    return Sequence<key,info>(keys3, info3);
}

int main() {
    cout << "Hello, World!" << endl;

    List<int> list1 = List<int>();
    List<int> list2 = List<int>();
    int s1_size = 8;
    int s2_size = 10;
    for (int i = 0; i < s1_size; i++) list1.push_back(i+1);
    for (int i = 0; i < s2_size; i++) list2.push_back(10*(i+1));
    for (int i = 0; i < s1_size; i++) cout<<list1.at(i)<<endl;
    for (int i = 0; i < s2_size; i++) cout<<list2.at(i)<<endl;

    Sequence<int, int> s1 = Sequence<int,int>(list1,list1);
    Sequence<int, int> s2 = Sequence<int,int>(list2,list2);

    Sequence<int,int> sequence = shuffle(s1,2,2,s2,0,3,3);

    return 0;
}

