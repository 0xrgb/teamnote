// Original Code: ?
// C++11
#include <random>

namespace treap {
	std::mt19937 rng;
	typedef struct node {
		node *l, *r;
		int idx, val, x, y, sz; // Change x, y, sz
		unsigned t;

		node() = default;
		node(int i, int v) : idx(i), val(v) {
			l = r = nullptr;
			t = rng();
			x = v, y = 0, sz = 1; // Change here
		}

		/* Change below */
		void update() {
			sz = (l ? l->sz : 0) + (r ? r->sz : 0) + 1;
			x = val ^ (l ? l->x : 0) ^ (r ? r->x : 0) ^ ((sz & 1) ? y : 0);
		}
		void downdate() {
			val ^= y;
			if (l) {
				l->y ^= y;
				if (l->sz & 1) l->x ^= y;
			}
			if (r) {
				r->y ^= y;
				if (r->sz & 1) r->x ^= y;
			}
			y = 0;
		}
	} *pnode;

	pnode merge(pnode left, pnode right) {
		if (!left) return right;
		else if (!right) return left;
		else if (left->t > right->t) {
			left->downdate();
			left->r = merge(left->r, right);
			left->update();
			return left;
		}
		right->downdate();
		right->l = merge(left, right->l);
		right->update();
		return right;
	}

	// Find all v, k <= v->idx => right
	void split(pnode root, int k, pnode &left, pnode &right) {
		if (!root) {
			left = right = nullptr;
			return;
		}

		root->downdate();
		if (k > root->idx) {
			split(root->r, k, root->r, right);
			left = root;
		} else {
			split(root->l, k, left, root->l);
			right = root;
		}
		root->update();
	}
};

// Test Code - BOJ 12844
#include <cstdio>
#include <algorithm>

const int MAXN = 500004;

int N;
treap::node T[MAXN];

void query1(treap::pnode&, int, int, int);
int  query2(treap::pnode&, int, int);

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		int k;
		scanf("%d", &k);

		T[i].idx = i;
		T[i].val = T[i].x = k;
		T[i].sz = 1;
		T[i].t = treap::rng();
	}

	treap::pnode root = &T[0];
	for (int i = 1; i < N; ++i)
		root = treap::merge(root, &T[i]);

	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		int qt, a, b, c;
		scanf("%d", &qt);
		switch (qt) {
		case 1:
			scanf("%d%d%d", &a, &b, &c);
			query1(root, a, b, c);
			break;
		case 2:
			scanf("%d%d", &a, &b);
			int ans = query2(root, a, b);
			printf("%d\n", ans);
			break;
		}
	}

	return 0;
}

void query1(treap::pnode &root, int l, int r, int val) {
	if (l > r) std::swap(l, r);

	treap::pnode r1, r2, r3;
	treap::split(root, l, r1, r2);
	treap::split(r2, r + 1, r2, r3);

	r2->y ^= val;
	if (r2->sz & 1) r2->x ^= val;
	root = treap::merge(r1, treap::merge(r2, r3));
}

int query2(treap::pnode &root, int l, int r) {
	if (l > r) std::swap(l, r);

	treap::pnode r1, r2, r3;
	treap::split(root, l, r1, r2);
	treap::split(r2, r + 1, r2, r3);

	const int ans = r2->x;

	root = treap::merge(r1, treap::merge(r2, r3));
	return ans;
}
