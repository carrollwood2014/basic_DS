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

namespace detail{

    template <typename  T> struct BinomialNode{

        T mValue;
        BinomialNode * mRight;
        BinomialNode * mChild;

        BinomialNode(const T& value, BinomialNode* right, BinomialNode *child){
            mValue = value;
            mRight = right;
            mChild = child;

        }

    };

    template <typename  T>
    bool CompareNodesByValue(const BinomialNode<T> *lhs, const BinomialNode<T>* rhs){
        if (!lhs || !rhs){
            return !lhs < !rhs;
        }
        return lhs->mValue < rhs->mValue;

    }

    template  <typename T>
    BinomialNode<T> * MergeTrees(BinomialNode<T>* lhs, BinomialNode<T> *rhs){

        if (rhs->mValue < lhs->mValue){
            std::swap(rhs, lhs);
        }

        rhs->mRight = lhs->mChild;
        lhs->mChild = rhs;
        return lhs;
    }



    template <typename T>
    void BinomialHeapMerge(std::vector<BinomialNode<T>*>& lhs,
                           std::vector<BinomialNode<T>*>& rhs) {
        /* vector to hold the result.  We use auxiliary scratch space so that we
         * don't end up with weirdness from modifying the lists as we traverse
         * them.
         */
        std::vector<BinomialNode<T>*> result;

        /* As a simplification, we'll ensure that the two lists have the same
         * size by padding each with null elements until they're the same size.
         */
        const size_t maxOrder = std::max(lhs.size(), rhs.size());
        lhs.resize(maxOrder);
        rhs.resize(maxOrder);

        /* Merging two binomial heaps is similar to adding two binary numbers.
         * We proceed from the "least-significant tree" to the "most-significant
         * tree", merging the two trees and storing the result either back in the
         * same slot (if no trees were added) or in a carry register to be used in
         * the next computation.  This next variable declaration contains the
         * carry.
         */
        BinomialNode<T>* carry = NULL;

        /* Start marching! */
        for (size_t order = 0; order < maxOrder; ++order) {
            /* There are eight possible combinations of the nullity of the carry,
             * lhs, and rhs trees.  To make the logic simpler, we'll add them all to
             * a temporary buffer and proceed from there.
             */
            std::vector<BinomialNode<T>*> trees;
            if (carry)
                trees.push_back(carry);
            if (lhs[order])
                trees.push_back(lhs[order]);
            if (rhs[order])
                trees.push_back(rhs[order]);

            /* There are now four cases to consider. */

            /* Case one: both trees and the carry are null.  Then the result of
             * this step is null and the carry should be cleared.
             */
            if (trees.empty()) {
                result.push_back(NULL);
                carry = NULL;
            }
                /* Case two: There's exactly one tree.  Then the result of this
                 * step is that tree and the carry is cleared.
                 */
            else if (trees.size() == 1) {
                result.push_back(trees[0]);
                carry = NULL;
            }
                /* Case three: There's exactly two trees.  Then the result of this
                 * operation is NULL and the carry will be set to the merge of those
                 * trees.
                 */
            else if (trees.size() == 2) {
                result.push_back(NULL);
                carry = MergeTrees(trees[0], trees[1]);
            }
                /* Case four: There's exactly three trees.  Then we'll arbitrarily
                 * store one of them in the current slot, then put the merge of the
                 * other two into the carry.
                 */
            else {
                result.push_back(trees[0]);
                carry = MergeTrees(trees[1], trees[2]);
            }
        }

        /* Finally, if the carry is set, append it to the result. */
        if (carry)
            result.push_back(carry);

        /* Clear out the rhs and assign the lhs the value of result. */
        rhs.clear();
        lhs = result;
    }


    template <typename T>
    void DestroyBinomialTree(BinomialNode<T>* root){
        if(!root) return;

        DestroyBinomialTree(root->mRight);
        DestroyBinomialTree(root->mChild);

        delete root;
    }

    template <typename T>
    BinomialNode<T> * CloneBinomialTree(BinomialNode<T>* root){
        if(!root) return NULL;

        return  new BinomialNode<T>(root->mValue,
                                    CloneBinomialTree(root->mRight),
                                    CloneBinomialTree(root->mChild));



    }
}

template <typedef T>
BinomialHeap<T>::BinomialHeap() {
    mSize = 0;
}

template <typename T>
BinomialHeap<T>::~BinomialHeap() {
    std::for_each(mTrees.begin(), mTrees.end(), detail::DestroyBinomialTree<T>);
}

template <typename T>
BinomialHeap<T>::BinomialHeap(const BinomialHeap& other) {
    mSize = other.mSize;
    for(size_t i =0 ; i < other.mTrees.size(); i++){
        mTrees.push_back(detail::CloneBinomialTree(other.mTrees[i]));
    }

}



#endif //BASIC_DS_BINOMIALHEAP_H
