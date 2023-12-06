#pragma once
#ifndef MINHEAP_HPP 
#define MINHEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class MinHeap 
{
private:
    std::vector<int> heap;

    // Function to maintain the heap property while inserting
    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Function to maintain the heap property while removing
    void heapifyDown(int index) {
        int size = heap.size();
        int smallest = index;

        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Function to insert an element
    void insert(int element) {
        heap.push_back(element);
        heapifyUp(heap.size() - 1);
    }

    // Function to extract the minimum element
    int extractMin() {
        if (heap.size() == 0) {
            throw std::runtime_error("Heap is empty");
        }

        int min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return min;
    }

    // Function to get the minimum element
    int getMin() const {
        if (heap.size() == 0) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // Function to get size of the heap
    size_t size() const {
        return heap.size();
    }
};

#endif // !
