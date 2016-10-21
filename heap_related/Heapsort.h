//
// Created by Rui Xia on 10/20/16.
//

#ifndef BASIC_DS_HEAPSORT_H
#define BASIC_DS_HEAPSORT_H

#include <iterator>
#include <functional>
#include <algorithm>

template <typename RandomIterator>
void HeapSort(RandomIterator begin, RandomIterator end);



template <typename RandomIterator, typename Comparator>
void HeapSort(RandomIterator begin, RandomIterator end, Comparator comp);


namespace heapsort_detail{


    template <typename  RandomIterator, typename Comparator>
    void HeapJoin(RandomIterator begin, RandomIterator heapStart,
                  RandomIterator end, Comparator comp){


        typedef typename std::iterator_traits<RandomIterator>::difference_type  diff_t;
        const diff_t kNumElems = distance(begin, end);

        diff_t position = distance(begin, heapStart);

        while( 2*position +1 < kNumElems){

            diff_t compareIndex = 2 * position +1;

            if( 2 * position +2 < kNumElems && comp( begin[2* position+1], begin[2* position+2] ) )
                compareIndex = 2* position + 2;

            if (comp(begin[compareIndex], begin[position]))
                break;

            std::swap(begin[compareIndex], begin[position]);
            position = compareIndex;
        }
    }
}



template <typename  RandomIterator, typename Comparator>
void HeapSort(RandomIterator begin, RandomIterator end, Comparator comp) {

    if (begin == end || begin +1 == end)
        return;

    for (RandomIterator itr = end; itr != begin; --itr)
        heapsort_detail::HeapJoin(begin, itr - 1, end, comp);

    for (RandomIterator itr = end - 1; itr != begin; --itr) {
        std::iter_swap(begin, itr);
        heapsort_detail::HeapJoin(begin, begin, itr, comp);
    }
}

template  <typename  RandomIterator>
void HeapSort(RandomIterator begin, RandomIterator end){
    HeapSort(begin, end,
            std::less<typename std::iterator_traits<RandomIterator>::value_type>());

}




#endif //BASIC_DS_HEAPSORT_H
