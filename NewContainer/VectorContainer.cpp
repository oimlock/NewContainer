#include <vector>
#include "VectorContainer.h"

namespace oimlock {

	VectorContainer::VectorContainer() {}

	int VectorContainer::get(int i) {
		return container_[i];
	}

	void VectorContainer::insert(int i, int x) {
		container_.insert(container_.begin() + i, x);
	}

	void VectorContainer::erase(int i) {
		container_.erase(container_.begin() + i);
	}

	void VectorContainer::set(int i, int x) {
		container_[i] = x;
	}

	int VectorContainer::size() {
		return container_.size();
	}

	bool VectorContainer::empty() {
		return !container_.empty();
	}

	void VectorContainer::clear() {
		container_.clear();
	}

	int VectorContainer::summ_range(int left, int right) {
		int summ = 0;
		for (int i = left; i <= right; ++i) {
			summ += container_[i];
		}
		return summ;
	}
}
