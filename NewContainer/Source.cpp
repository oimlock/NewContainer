#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "VectorContainer.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int n;
	oimlock::IContainer* c = new oimlock::VectorContainer;

	cin >> n;

	for (int k = 0; k < n; ++k) {
		int command;
		cin >> command;
		if (command == 0) {
			int i;
			cin >> i;
			cout << "element " << i << ' ' << c->get(i) << endl;
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
			cout << "summ " << l << ' ' << r << ' ' << c->summ_range(l, r) << endl;
		}
	}

	return 0;
}
