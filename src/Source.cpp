#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <chrono>
#include "VectorContainer.h"
#include "ListContainer.h"
#include "VectorList.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int container_type;
	cin >> container_type;

	std::unique_ptr <oimlock::IContainer> c;

	switch (container_type) 
	{
	case 0: 
		c = std::make_unique <oimlock::VectorContainer>();
		cout << "VectorContainer\n";
		break;
	case 1:
		c = std::make_unique <oimlock::ListContainer>();
		cout << "ListContainer\n";
		break;
	case 2:
		c = std::make_unique <oimlock::VectorList>();
		cout << "VectorList\n";
		break;
	}

	int n;
	cin >> n;
	auto t1 = std::chrono::high_resolution_clock::now();

	for (int k = 0; k < n; ++k) {
		int command;
		cin >> command;
		if (command == 0) {
			int i;
			cin >> i;
			cout << "element " << i << " is " << c->get(i) << endl;
		}
		else if (command == 1) {
			int i, x;
			cin >> i >> x;
			c->insert(i, x);
		}
		else if (command == 2) {
			int i;
			cin >> i;
			c->erase(i);
		}
		else if (command == 3) {
			int i, x;
			cin >> i >> x;
			c->set(i, x);
		}
		else if (command == 4) {
			cout << "size " << c->size() << endl;
		}
		else if (command == 5) {
			cout << "empty " << (c->empty() ? 1 : 0) << endl;
		}
		else if (command == 6) {
			c->clear();
		}
		else if (command == 7) {
			int l, r;
			cin >> l >> r;
			cout << "summ from " << l << " to " << r << " is " << c->summ_range(l, r) << endl;
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	int int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	cout << endl << int_ms << " ms " << endl;

	return 0;
}
