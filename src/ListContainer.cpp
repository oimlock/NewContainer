#include "ListContainer.h"
#include <list>

namespace oimlock {

ListContainer::ListContainer() {}

int ListContainer::get(int i) {
	auto it = container_.begin();
	advance(it, i);
	return *it;
}

void ListContainer::insert(int i, int x) {
	auto it = container_.begin();
	advance(it, i);
	container_.insert(it, x);
}

void ListContainer::erase(int i) {
	auto it = container_.begin();
	advance(it, i);
	container_.erase(it);
}

void ListContainer::set(int i, int x) {
	auto it = container_.begin();
	advance(it, i);
	container_.erase(it);
	container_.insert(it, x);
}

int ListContainer::size() {
	return container_.size();
}

bool ListContainer::empty() {
	return container_.empty();
}

void ListContainer::clear() {
	container_.clear();
}

int ListContainer::summ_range(int left, int right) {
	int summ = 0;
	for (int i = left; i <= right; ++i) {
		auto it = container_.begin();
		advance(it, i);
		summ += *it;
	}
	return summ;
}

}
