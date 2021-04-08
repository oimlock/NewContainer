#pragma once

using std::vector;

class NewContainer {
public:

	int operator[]  (int i) const {
		return container_[i];
	}

	int& operator[]  (int i) {
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

	struct Range {
		int left;
		int right;
	};

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

		for (int i = d.left; i <= d.right; ++i) { // �������� ����
			summ += container_sqrt_[i];
		}
		for (int j = section_.left; j < d.left * k_; ++j) { // ����� �����
			summ += container_[j];
		}
		for (int j = (d.right + 1) * k_; j <= section_.right; ++j) { // ������ �����
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
