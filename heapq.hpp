#pragma once

#include <vector>

// shameless pluck from https://raw.githubusercontent.com/python/cpython/3.10/Lib/heapq.py


template <typename T>
class heapq_t : private std::vector<T> {
public:
  void push(const T& item) {
    this->push_back(item);
    siftdown(0, size() - 1);
  }

  T pop() {
    T last = this->back();
    this->pop_back();
    if (!size()) {
      return last;
    }
    T ret = (*this)[0];
    (*this)[0] = last;
    siftup(0);
    return ret;
  }

  int size() const {
    return std::vector<T>::size();
  }
  
private:
  void siftdown(int startpos, int pos) {
    // heap at all indices >= startpos, except possibly for pos.
    // pos is the index of a leaf with a possibly out-of-order
    // value. Restore the heap invariant.
    T newitem = (*this)[pos];
    // Follow the path to the root, moving parents down until finding a
    // place newitem fits.
    while (pos > startpos) {
      int parentpos = (pos - 1) >> 1;
      T parent = (*this)[parentpos];
      if (newitem < parent) {
	(*this)[pos] = parent;
	pos = parentpos;
	continue;
      }
      break;
    }
    (*this)[pos] = newitem;
  }

  void siftup(int pos) {
    // the children of [pos] are already heaps, and we want to make
    // a heap at [pos], too. Do this by bubbling the smaller child
    // of pos up (and so on with the child's children) until hitting
    // a leaf, then use siftdown to move the oddball originally at [pos]
    // into pos.
    int endpos = size();
    int startpos = pos;
    T newitem = (*this)[pos];
    // Bubble up the smaller child until hitting a leaf.
    int childpos = 2 * pos + 1; // left child
    while (childpos < endpos) {
      // Set childpos to index of smaller child.
      int rightpos = childpos + 1;
      if (rightpos < endpos && !((*this)[childpos] < (*this)[rightpos])) {
	childpos = rightpos;
      }
      // Move the smaller child up
      (*this)[pos] = (*this)[childpos];
      pos = childpos;
      childpos = 2 * pos + 1; // left child
    }
    // The leaf at pos is empty now. Put new item there, and bubble it up
    // to its final resting place (by sifting its parents down).
    (*this)[pos] = newitem;
    siftdown(startpos, pos);
  }
  
};



