// Original Code: Modern Computer Arithmetic (p33)
// C++11
namespace egcd {
	struct solution {
		int g, u, v;
	};

	// Assume a >= 0, b >= 0
	// (a, b) != (0, b), (a, 0), (1, 1) => |u| < b && |v| < a
	solution gcd(int a, int b) {		
		int u = 1, w = 0;
		int v = 0, x = 1;
		int q, r, t;
		while (b != 0) {
			q = a / b;
			r = a % b;
			
			a = b;
			b = r;

			r = w;
			t = u - q * w;
			u = r, w = t;

			r = x;
			t = v - q * x;
			v = r, x = t;
		}

		return solution{ a, u, v };
	}

	// Assume gcd(a, N) = 1, int is 32bit
	int inv(int a, int N) {
		solution ans = gcd(a, N);
		// make result > 0
		return ans.u + ((ans.u >> 31) & N);
	}
};

// Test Code
#include <cstdio>
#include <cassert>
#include <random>

int main() {
	std::random_device rd;
	std::mt19937 rand32(rd());
	std::uniform_int_distribution<int> dis(1, 126);

	for (int i = 0; i < 10; ++i) {
		const int x = dis(rd);
		const int y = egcd::inv(x, 127);
		assert(x * y % 127 == 1);
		printf("Inv[%3d] = %3d\n", x, y);
	}

	return 0;
}
