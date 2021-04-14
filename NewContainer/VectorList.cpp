#include "VectorList.h"
#include <vector>
#include <list>
#include <cmath>

namespace oimlock {

VectorList::VectorList() : size_(0), k_(1) {}

int VectorList::get(int i) { 
	auto it = container_[i / k_].begin();
	advance(it, i % k_);
	return *it;
}

void VectorList::insert(int i, int x) {
	if (empty()) {
		container_.resize(2);
		container_[0].push_back(x);
		++size_;
		k_ = 2;
		summ_.resize(2);
		summ_[0] = x;
		return;
	}

	auto it = container_[i / k_].begin();
	advance(it, i % k_);
	container_[i / k_].insert(it, x);
	summ_[i / k_] += x;
	++size_;
	for (int i = 0; i < container_.size(); ++i) {
		if (container_[i].size() > k_) {
			rebalance_insert(i);
		}
	}
	if (sqrt(size_) >= k_) {
		rebalance_k_new();
	}
	return;
}

void VectorList::erase(int idx) {
	auto it = container_[idx / k_].begin();
	advance(it, idx % k_);
	summ_[idx / k_] -= *it;
	container_[idx / k_].erase(it);
	--size_;
	for (int i = 0; i < size_ / k_; ++i) {
		if (container_[i].size() < k_) {
			rebalance_erase(i);
		}
	}
	if (size_ == (k_ - 1) * (k_ - 1)) {
		rebalance_k_new();
	}
	return;
}

void VectorList::set(int i, int x) {
	auto it = container_[i / k_].begin();
	advance(it, i % k_);
	summ_[i / k_] -= *it;
	summ_[i / k_] += x;
	container_[i / k_].insert(it, x);
	container_[i / k_].erase(it);
	return;
}

int VectorList::size() {
	return size_;
}

bool VectorList::empty() {
	if (size_ == 0) {
		return true;
	}
	else {
		return false;
	}
}

void VectorList::clear() {
	container_.clear();
	size_ = 0;
	k_ = 1;
	return;
}

int VectorList::summ_range(int l, int r) {
	if (l / k_ == r / k_) {
		return summ_in_one_section(l,r);
	}
	else {
		return summ_with_diff_sections(l,r);
	}
	return 0;
}

// ================== private ===============================

void VectorList::rebalance_k_new() {
	if (size_ >= k_ * k_) {
		++k_;
	}
	else {
		--k_;
	}

	std::vector <std::list <int>> new_container(k_);
	std::vector <int> new_summ(k_);
	int list_filled = 0;

	for (int i = 0; i < container_.size(); ++i) {
		for (auto it = container_[i].begin(); it != container_[i].end(); ++it) {
			new_container[list_filled].push_back(*it);
			new_summ[list_filled] += *it;
			if (new_container[list_filled].size() == k_) {
				++list_filled;
			}
		}
	}
	swap(container_, new_container);
	swap(summ_, new_summ);
	return;
}

void VectorList::rebalance_insert(int i) {
	container_[i + 1].push_front(container_[i].back());
	summ_[i + 1] += container_[i + 1].front();
	container_[i].pop_back();
	summ_[i] -= container_[i + 1].front();
	return;
}

void VectorList::rebalance_erase(int i) {
	container_[i].push_back(container_[i + 1].front());
	summ_[i] += container_[i].back();
	container_[i + 1].pop_front();
	summ_[i + 1] -= container_[i].back();
	return;
}

struct Range {
	int left;
	int right;
};

int VectorList::summ_with_diff_sections(int l, int r) {	
	Range d;
	d.left = l / k_ + 1;
	d.right = r / k_ - 1;
	int summ = 0;

	for (int i = d.left; i <= d.right; ++i) { // central part 
		summ += summ_[i];
	}
	for (int i = l; i < d.left * k_; ++i) { // left part
		auto it = container_[i / k_].begin();
		advance(it, i% k_);
		summ += *it;
	}
	for (int i = (d.right + 1) * k_; i <= r; ++i) { // right part
		auto it = container_[i / k_].begin();
		advance(it, i % k_);
		summ += *it;
	}
	return summ;
}

int VectorList::summ_in_one_section(int l, int r) {
	int summ = 0;
	for (int i = l; i <= r; ++i) {
		auto it = container_[i / k_].begin();
		advance(it, i % k_);
		summ += *it;
	}
	return summ;
}

} //namesapce oimlock
