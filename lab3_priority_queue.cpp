#include <iostream>
#include "lab3_priority_queue.hpp"

using namespace std;

// Lab Assignment 2:
//    Group #28
//    Kate Harvey, ID# 20829173
//    Jessica Lui, ID# 20837325


// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    heap = new TaskItem*[n_capacity + 1];
    capacity = n_capacity;
    size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
 PriorityQueue::~PriorityQueue() {
    for(int index = 1 ; index <= size ; index ++) {
        delete heap[index];
        heap[index] = NULL;
    }
    delete[] heap;
    heap = NULL;
    capacity = 0;
    size = 0;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    if(size == 0) return true;
    else return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    if(size == capacity) return true;
    else return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    int index = 0;
    while(index < size) {
        cout << "Task " << index + 1 << endl;
        cout << "Priority: " << heap[index] -> priority << endl;
        cout << "Description: " << heap[index] -> description << endl;
        cout << endl;
        index ++;
    }
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if(size == 0) return TaskItem(-1, "NULL");
    else {
        return *heap[1];
    }
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue(TaskItem val) {
    if(size == capacity) return false; // PriorityQueue is full
    if(size == 0) heap[1] = new TaskItem(val); // PriorityQueue is empty
    else heap[size + 1] = new TaskItem(val); // insert TaskItem at first empty spot
    
    int index = size + 1;
    
    while(index > 1 && heap[index/2] -> priority < heap[index] -> priority) {
        TaskItem* temp = heap[index/2];
        heap[index/2] = heap[index];
        heap[index] = temp;
        index = index/2;
    }
     
    size ++;
    return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    if(size == 0) return false;
    TaskItem* temp = heap[size];
    heap[size] = heap[1]; // swap root with rightmost leaf node
    heap[1] = temp; // remove the swapped node
    
    delete heap[size];
    heap[size] = NULL;
    
    if(size > 1) {
        int index = 1;
        
        // swap root node with largest-valued child until it respects max heap property
        while(index < size + 1 && index < size/2 && (heap[2*index] -> priority > heap[index] -> priority || heap[2*index + 1] -> priority > heap[index] -> priority)) {
            
            if(heap[2*(index)] > heap[2*(index) + 1]) { // left child > right child
                TaskItem* temp = heap[index];
                heap[index] = heap[2*(index)];
                heap[2*(index)] = temp;
                index = 2*(index);
            }
            else { // right child > left child
                TaskItem* temp = heap[index];
                heap[index] = heap[2*(index) + 1];
                heap[2*(index) + 1] = temp;
                index = 2*(index) + 1;
            }
        }
    }
    
    size --;
    return true;
}
