//
// Created by Rui Xia on 10/20/16.
//

#include <vector>
#include <iostream>
#include "Heapsort.h"

using namespace std;


int main(){

    cout << "Test Heapsort" << endl;

    vector<int> test_array = {14,15,97,1,27,35,36};


    HeapSort( test_array.begin(), test_array.end());

    for (auto i: test_array){
        std::cout << i << ' ' ;
    }


    return 0;
}
