/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

// You can do rectangle queries in 2D array and cuboid queries in 3D array etc
// For update -> (x_i, y_i, z_i, value) for query -> (left_x, right_x, left_y, right_y, left_z, right_z)
template <class T, int ...Ns> struct BITn {
    // It is 0 indexed 
	T val = 0;
	void update(T v) { val += v; }
	T query() { return val; }
};
template <class T, int N, int... Ns> struct BITn<T, N, Ns...> {
	BITn<T,Ns...> bit[N + 1];
	template<typename... Args> void update(int pos, Args... args) {
		for (++pos; pos <= N; pos += (pos&-pos)) bit[pos].update(args...);
	}
	template<typename... Args> T sum(int r, Args... args) {
		T res = 0; for (; r; r -= (r&-r)) res += bit[r].query(args...);
		return res;
	}
	template<typename... Args> T query(int l, int r, Args... args) {
		return sum(r + 1,args...)-sum(l,args...);
	}
}; // BIT<int,10,10> gives a 2D BIT}}}
