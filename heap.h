//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size==64) return;
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) {
            return -1;
        }
        int min = data[0];
        size--;
        data[0] = data[size];
        downheap(0, weightArr);
        return min;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos>0) {
            int parent = (pos-1)/2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                swap(data[pos], data[parent]);
                pos = parent;
            }
            else break;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (pos*2+1<size) {
            int LC = pos*2 + 1;
            int RC = pos*2 + 2;
            int min = LC;
            //if RC exist && if RC<LC
            if (RC<size && weightArr[data[RC]]<weightArr[data[LC]]) min = RC;
            if (weightArr[data[pos]] > weightArr[data[min]]) {
                swap(data[pos], data[min]);
                pos = min;
            }
            else break;

        }
    }
};

#endif