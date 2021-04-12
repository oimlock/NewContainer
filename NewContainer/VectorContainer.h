#pragma once

#include "IContainer.h"
#include <vector>

namespace oimlock {

class VectorContainer : public IContainer {
public:
	VectorContainer();
	int get(int i) override;
	void insert(int i, int x) override;
	void erase(int i) override;
	void set(int i, int x);
	int size() override;
	bool empty() override;
	void clear() override;
	int summ_range(int left, int right);

private:
	std::vector <int> container_;
};

}
