#pragma once
#include "Iterator.h"

class PeekingIterator : public Iterator {
private:
    const vector<int> &nums;
    int size;
    int index;
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums), nums(nums), size(nums.size()), index(0) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.

    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        if (index < size) {
            return nums[index];
        } else {
            return -1;
        }
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        if (index < size) {
            return nums[index++];
        } else {
            return -1;
        }
    }

    bool hasNext() const {
        return index < size;
    }
};
