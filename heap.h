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
        upheap(size, weightArr); //upheap always starts at the index you just pushed because all other values should have already been upheaped into correct position
        //so upheap starts at size/where you pushed
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
        downheap(0, weightArr); //downheaps start from top and heaps downwards so it always starts at index 0
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
            else break; //stop when the parent of the node you are in is bigger than it's parent
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (pos*2+1<size) {
            int LC = pos*2 + 1;
            int RC = pos*2 + 2;
            int min = LC;
            if (RC<size && weightArr[data[RC]]<weightArr[data[LC]]) min = RC; //if RC is not out of bounds and if the LC<RC the min is RC not LC
            if (weightArr[data[pos]] > weightArr[data[min]]) {
                swap(data[pos], data[min]);
                pos = min;
            }
            else break; //stop when the index you are in is lesser than both of it's children

        }
    }
};

#endif