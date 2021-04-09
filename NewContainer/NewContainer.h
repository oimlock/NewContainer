#pragma once

#include <vector>
#include "IContainer.h"

using std::vector;

class NewContainer: public IContainer {
public:

	int get(int i) override {
		return container_[i];
	}

	void insert(int i, int x) override {
		container_.insert(container_.begin() + i, x);
	}

	void erase(int i) override {
		container_.erase(container_.begin() + i);
	}

	void set(int i, int x) override {
		container_[i] = x;
	}

	int size() override {
		return container_.size();
	}

	bool empty() override {
		return !container_.empty();
	}

	void clear() override {
		container_.clear();
	}

	int summ_range(int left, int right) override {
		int summ = 0;
		for (int i = left; i <= right; ++i) {
			summ += container_[i];
		}
		return summ;
	}

private:
	vector <int> container_;
};
