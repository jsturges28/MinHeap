//
//  main.cpp
//  Min heap
//
//  Created by Jacob Sturges on 12/18/20.
//

#include <iostream>
#include <vector>

using namespace std;

//function prototypes

void reheapUp(vector<int> & x, int idx);
void insertion(vector<int> & x, int key);
void reheapDown(vector<int> & x, int idx);
void deletion(vector<int> & x);

int main() {
    
    int node, input, key;
    int i = 0;
    vector<int> heap;
    
    // While reading in values, we organize each value to make a min heap
    
    while (cin >> node) {
        heap.push_back(node);
        reheapUp(heap, i);
        i++;
    }
    
    cin.clear();
    
    cin.ignore(2, '\n');
    
    cin >> input >> key;
    
    // Input 0 = Enumeration, input 1 = Insertion, input 2 = Deletion
    
    switch(input) {
            
        case 0: {
            
            // print out -1 if the heap is empty
            
            if (heap.empty()) {
                cout << -1;
            }
            
            // else print out the values in the heap in heap order
            
            else {
                for (int i = 0; i < heap.size(); i++) {
                    cout << heap[i] << " ";
                }
            }
            break;
        }
        
        case 1: {
            
            // if the key we want to insert is already in the heap, we print out -1
            
            if (find(heap.begin(), heap.end(), key) != heap.end()) {
                
                    cout << -1;
            }
            
            // else we insert the key and reheap the heap. Then we print
            
            else {
                insertion(heap, key);
                reheapUp(heap, (int) heap.size() - 1);
                
                for (int i = 0; i < heap.size(); i++) {
                    cout << heap[i] << " ";
                }
            }
            break;
        }
            
        case 2: {
            
            // if the root node is empty (equivalent to saying the heap is empty), we print out -1
            
            if (heap.empty()) {
                cout << -1;
            }
            
            // else we perform deletion and print out the reheapified heap
            
            else {
                deletion(heap);
                reheapDown(heap, 0);
                
                for (int i = 0; i < heap.size(); i++) {
                    cout << heap[i] << " ";
                }
                break;
            }
        }
            
    }
    
    return 0;
}

// function to reorgainze the heap when we went to insert. Indexes of the children compared to the parent are calculated as follows: if parent is index i, the left child is index k = 2i + 1, and the right child is k = 2i + 2. So, if the child node at index k is odd, the parent index is i = (k-1)/2. If the child node is even, then the parent index is i = (k-2)/2.

void reheapUp(vector<int> & x, int idx) {
    int idx_parent;
    
    if (idx == 0) {                     // if we reached the root
        return;
    }
    if (idx % 2 == 0) {                 // if child index is even
        idx_parent = (idx - 2) / 2;
    }
    else {                              // if child index is odd
        idx_parent = (idx - 1) / 2;
    }
    
    if (x[idx_parent] <= x[idx]) {      // reached the end of our swapping. We want the parent to be less than a child node in the min heap.
        return;
    }
    else {
        swap(x[idx_parent], x[idx]);    // swap values
        reheapUp(x, idx_parent);
    }
}

// function to reorgainze the heap when we went to insert. Indexes of the children compared to the parent are calculated as follows: if parent is index i, the left child is index k = 2i + 1, and the right child is k = 2i + 2.

void reheapDown(vector<int> & x, int idx_parent) {
    int idx_ch1, idx_ch2, idx_ch;
    
    idx_ch1 = 2*(idx_parent) + 1;
    idx_ch2 = 2*(idx_parent) + 2;
    
    // here, we want to make sure we don't go out of bounds. We may encounter a situation where a node may only have 0 or 1 child nodes, so we want to return the vector as is when we run into this situation.
    
    while (idx_ch1 < x.size() && idx_ch2 < x.size()) {
    
        if (x[idx_ch1] < x[idx_ch2]) {  // we want to compare the parent to the smaller child in a min heap.
            idx_ch = idx_ch1;
        }
        else {
            idx_ch = idx_ch2;
        }
        
        if (x[idx_parent] <= x[idx_ch]) {   // we've reached the end and the heap is balanced.
            return;
        }
        else {
            swap(x[idx_parent], x[idx_ch]);
            reheapDown(x, idx_ch);
        }
    }
    return;
}

// simple funciton to push a value in a vector

void insertion(vector<int> & x, int key) {
    x.push_back(key);
}

// function used to swap the rightmost (last) node in the heap with the root node, and delete the last value after swapping. When deleting in a heap, you swap the root node with the last node, and you then delete the previous root node (now at the back of the vector).

void deletion(vector<int> & x) {
    int idx_last = (int) x.size() - 1;
    swap(x[0], x[idx_last]);
    x.pop_back();
    idx_last = (int) x.size() - 1;
}
