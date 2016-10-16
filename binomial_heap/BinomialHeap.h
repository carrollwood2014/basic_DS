//
// Created by Rui Xia on 10/15/16.
//

#ifndef BASIC_DS_BINOMIALHEAP_H
#define BASIC_DS_BINOMIALHEAP_H

#include <vector>
#include <algorithm>
#include <stdlib.h>


namespace  detail {
    template <typename T> struct  BinomialNode;
}

template  <typename  T> class BinomialHeap{
public:
    BinomialHeap();
    ~BinomialHeap();

    BinomialHeap(const BinomialHeap&);
    BinomialHeap& operator= (const BinomialHeap&);

    void push(const T&);

    const T& top() const;

    void pop();

    void merge(BinomialHeap& other);

    size_t size() const;
    bool empty() const;

    void swap(BinomialHeap& other);

private:
    std::vector<detail::BinomialNode<T>*> mTrees;
    size_t mSize;

};





#endif //BASIC_DS_BINOMIALHEAP_H
