// Original Code: http://blog.myungwoo.kr/54
// C++11
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>

namespace fft {
	typedef std::complex<double> base;
	typedef std::vector<base> vb;
	typedef std::vector<int> vi;

	const double pi = 3.14159265358979324;

	void fft(vb &a, bool inv) {
		const int n = a.size();
		for (int i = 1, j = 0; i < n; ++i) {
			int bit = (n >> 1);
			for (; j >= bit; bit >>= 1) j -= bit;
			j += bit;
			if (i < j) std::swap(a[i], a[j]);
		}
		for (int len = 2; len <= n; len <<= 1) {
			const int hlen = len >> 1;
			const double ang = pi / hlen * (inv ? -1 : 1);
			const base wlen(cos(ang), sin(ang));
			for (int i = 0; i < n; i += len) {
				base w(1);
				for (int j = 0; j < hlen; ++j) {
					base u = a[i + j], v = a[i + j + hlen] * w;
					a[i + j] = u + v;
					a[i + j + hlen] = u - v;
					w *= wlen;
				}
			}
		}

		if (inv) {
			for (int i = 0; i < n; ++i) a[i] /= n;
		}
	}

	// Assume int is 32bit
	int find_p2(int x) {
		--x;
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		return ++x;
	}

	void multiply(const vi &a, const vi &b, vi &res) {
		vb fa(a.begin(), a.end()), fb(b.begin(), b.end());
		const int nz = a.size() + b.size() - 1;
		const int n = find_p2(nz);

		fa.resize(n); fb.resize(n);
		fft(fa, false); fft(fb, false);

		// Multiply results
		for (int i = 0; i < n; ++i) fa[i] *= fb[i];

		fft(fa, true);

		res.resize(nz);
		for (int i = 0; i < nz; ++i) {
			res[i] = (int)round(fa[i].real());
		}
	}
};

// Test Code - BOJ 13277
#include <cstdio>
#include <cstring>

fft::vi na, nb, nc;
char str[300004];

int main() {
	scanf("%s", str);
	int len = strlen(str);
	for (int i = len - 1; i >= 0; --i) na.push_back(str[i] - '0');

	scanf("%s", str);
	len = strlen(str);
	for (int i = len - 1; i >= 0; --i) nb.push_back(str[i] - '0');

	fft::multiply(na, nb, nc);
	nc.push_back(0);

	for (int i = 0; i < nc.size(); ++i) {
		if (nc[i] >= 10) {
			nc[i + 1] += nc[i] / 10;
			nc[i] %= 10;
		}
	}

	bool isZero = true;
	for (int i = nc.size() - 1; i >= 0; --i) {
		if (isZero && nc[i] == 0) continue;
		isZero = false;
		putchar(nc[i] + '0');
	}
	if (isZero) putchar('0'); // result == 0

	return 0;
}
