#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Range {
	int left;
	int right;
};

class NewContainer {
public:

	int get(int i) {
		return container_[i];
	}

	void insert(int i, int x) {
		container_.insert(container_.begin() + i, x);
		k_ = sqrt(container_.size());
		container_sqrt_.resize((container_.size() + k_ - 1) / k_);
		rebalance();
	}

	void erase(int i) {
		container_.erase(container_.begin() + i);
	}

	void emplace(int i, int x) {
		container_[i] = x;
	}

	int size() {
		return container_.size();
	}

	int empty() {
		return !container_.empty();
	}

	void clear() {
		container_.clear();
	}

	int summ_range(int left, int right) {
		section_.left = left;
		section_.right = right;
		if (section_.left / k_ == section_.right / k_) {
			return summ_in_one_sections();
		}
		else {
			return summ_with_diff_sections();
		}
	}

private:
	int k_;
	Range section_;
	vector <int> container_;
	vector <int> container_sqrt_;

	int summ_in_one_sections() {
		int summ = 0;
		for (int i = section_.left; i < section_.right + 1; ++i) {
			summ += container_[i];
		}
		return summ;
	}

	int summ_with_diff_sections() {
		Range d;
		d.left = section_.left / k_ + 1;
		d.right = section_.right / k_ - 1;
		int summ = 0;

		for (int i = d.left; i <= d.right; ++i) { // основное тело
			summ += container_sqrt_[i];
		}
		for (int j = section_.left; j < d.left * k_; ++j) { // левый хвост
			summ += container_[j];
		}
		for (int j = (d.right + 1) * k_; j <= section_.right; ++j) { // правый хвост
			summ += container_[j];
		}
		return summ;
	}
	void rebalance() {
		container_sqrt_.clear();
		k_ = sqrt(container_.size());
		container_sqrt_.resize((container_.size() + k_ - 1) / k_);
		for (int i = 0; i < container_.size(); ++i) {
			container_sqrt_[i / k_] += container_[i];
		}
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int n;
	NewContainer c;

	cin >> n;

	for (int k = 0; k < n; ++k) {
		int command;
		cin >> command;
		if (command == 0) {
			int i;
			cin >> i;
			cout << "element " << i << ' ' << c.get(i) << endl;
		}
		else if (command == 1) {
			int i, x;
			cin >> i >> x;
			c.insert(i, x);
		}
		else if (command == 2) {
			int i;
			cin >> i;
			c.erase(i);
		}
		else if (command == 3) {
			int i, x;
			cin >> i >> x;
			c.emplace(i, x);
		}
		else if (command == 4) {
			cout << "size " << c.size() << endl;
		}
		else if (command == 5) {
			cout << "empty " << c.empty() << endl;
		}
		else if (command == 6) {
			c.clear();
		}
		else if (command == 7) {
			int l, r;
			cin >> l >> r;
			cout << "summ " << l << ' ' << r << ' ' << c.summ_range(l, r) << endl;
		}
	}

	return 0;
}