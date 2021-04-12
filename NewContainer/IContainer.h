#pragma once

namespace oimlock {

class IContainer {
public:
	virtual int get(int i) = 0;
	virtual void insert(int i, int x) = 0;
	virtual void erase(int i) = 0;
	virtual void set(int i, int x) = 0;
	virtual int size() = 0;
	virtual bool empty() = 0;
	virtual void clear() = 0;
	virtual int summ_range(int left, int right) = 0;
};

}
