#pragma once

#include <list>
#include "IContainer.h"

namespace oimlock {

class ListContainer : public IContainer {
public:
	ListContainer();
	int get(int i) override;
	void insert(int i, int x) override;
	void erase(int i) override;
	void set(int i, int x);
	int size() override;
	bool empty() override;
	void clear() override;
	int summ_range(int left, int right);

private:
	std::list <int> container_;
};

}
