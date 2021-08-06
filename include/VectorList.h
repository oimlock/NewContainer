#pragma once

#include "IContainer.h"
#include <list>
#include <vector>

namespace oimlock {

class VectorList : public IContainer {
public:
	VectorList();
	int get(int i) override;
	void insert(int i, int x) override;
	void erase(int idx) override;
	void set(int i, int x);
	int size() override;
	bool empty() override;
	void clear() override;
	int summ_range(int left, int right);

private:
	void rebalance_k_new();
	void rebalance_insert(int i);
	void rebalance_erase(int i);
	int summ_in_one_section(int l, int r);
	int summ_with_diff_sections(int l, int r);

	std::vector <std::list<int>> container_;
	std::vector <int> summ_;
	int k_;
	int size_;
};

}
