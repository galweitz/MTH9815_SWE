#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class MaxHeap {
private:
    std::vector<int> heap;

    // Function to maintain the heap property while inserting
    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Function to maintain the heap property while removing
    void heapifyDown(int index) {
        int size = heap.size();
        int largest = index;

        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(int element) {
        heap.push_back(element);
        heapifyUp(heap.size() - 1);
    }

    int extractMax() {
        if (heap.size() == 0) {
            throw std::runtime_error("Heap is empty");
        }

        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return max;
    }

    int getMax() const {
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

