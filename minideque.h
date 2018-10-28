//
//  minideque.h
//  minidequeproject
//

#ifndef minideque_h
#define minideque_h

#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <iostream>
#include <math.h>

template <typename T>
class minideque {
private:
  std::vector<T> fronthalf_;
  std::vector<T> backhalf_;

public:
  minideque() = default;                                   // do not change, C++ defaults are ok
  minideque(const minideque<T>& other) = default;          // rule of three
  minideque& operator=(const minideque<T>& other) = default;
  ~minideque() = default;

  size_t size() const { return fronthalf_.size() + backhalf_.size(); }           
  size_t fronthalfsize() const { return fronthalf_.size(); }   
  size_t backhalfsize() const { return backhalf_.size(); }    
  bool empty()  const { return size() == 0; }

  // balance queue across both vectors if pop_front/back is requested on an empty vector
  // e.g., minideque has this:                  | ABCDEFG
  // after pop_front                        BCD | EFG (A discarded)
  // symmetric logic for converse case: ABCDEFG | ===> ABC | DEF (G discarded) after pop_back
  void pop_front() {
	  if (empty()) { throw std::range_error("popping empty queue"); }
	  if ((fronthalfsize() == 0) && (backhalfsize() != 0)) {
		  for (int i = 0; i < ceil((backhalfsize() / 2)); i++) {
			  fronthalf_.push_back(backhalf_[0]);
              backhalf_.erase(0);
		  }
	  }
	  fronthalf_.pop_back();
  }

  void pop_back() {
	  if (empty()) { throw std::range_error("popping empty queue"); }
	  if ((fronthalfsize() != 0) && (backhalfsize() == 0)) {
		  for (int i = 0; i < ceiling((fronthalfsize() / 2)); i++) {
			  backhalf_.push_back(fronthalf_[0]);
			  fronthalf_.erase(0);
		  }
	  }
	  backhalf_.pop_back();
  }

  void push_front(const T& value) {
	  fronthalf_.push_back(value);
  }
  void push_back(const T& value) {
	  backhalf_.push_back(value);
  }

  const T& front() const {
	  if (fronthalf_.empty()) { return backhalf_.front(); }
	  else {
		return fronthalf_.back();
	  }
  }
  const T& back() const {
	  if (fronthalf_.empty()) { return fronthalf_.front(); }
	  else {
		  return backhalf_.back();
	  }
  }

  T& front() {
	  if (fronthalf_.empty()) { return backhalf_.front(); }
	  else {
		  return fronthalf_.back();
	  }
  }
  T& back() {
	  if (fronthalf_.empty()) { return fronthalf_.front(); }
	  else {
		  return backhalf_.back();
	  }
  }

  const T& operator[](size_t index) const {
	  if (index > fronthalfsize()) {
          return backhalf_.at(index - fronthalfsize() - 1);
	  }
	  else {
		  return fronthalf_.at(fronthalfsize() - index - 1);
	  }
  }
  T& operator[](size_t index) {
	  if (index > fronthalfsize()) {
          return backhalf_.at(index - fronthalfsize() - 1);
	  }
	  else {
		  return fronthalf_.at(fronthalfsize() - index - 1);
	  }
  }

  void clear() {
	  fronthalf_.clear;
	  backhalf_.clear;
  }

  friend std::ostream& operator<<(std::ostream& os, const minideque<T>& dq) {    // do not change
    if (dq.empty()) { return os << "minideque is empty"; }

    dq.printFronthalf(os);
    os << "| ";
    dq.printBackhalf(os);
    os << ", front:" << dq.front() << ", back:" << dq.back() << ", size:" << dq.size();
    return os;
  }

  void printFronthalf(std::ostream& os=std::cout) const {                    // do not change
    if (empty()) { std::cout << "fronthalf vector is empty"; }

    for (typename std::vector<T>::const_reverse_iterator crit = fronthalf_.crbegin();
         crit != fronthalf_.crend(); ++crit) {
      os << *crit << " ";
    }
  }

  void printBackhalf(std::ostream& os=std::cout) const {                     // do not change
    if (empty()) { os << "backhalf vector is empty"; }

    for (typename std::vector<T>::const_iterator cit = backhalf_.cbegin();
         cit != backhalf_.cend(); ++cit) {
      os << *cit << " ";
    }
  }
};

#endif /* minideque_h */
