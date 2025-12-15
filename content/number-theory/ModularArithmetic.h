/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

const ll mod = 17; // change to something else
struct Mod {
	ll x;
	Mod(ll xx) : x(xx) {}
	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return Mod((x + mod) % mod);
	}
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};

const int MOD = 998244353;
inline void add(int &v, int b){
    v += b;
    if(v < 0)v += MOD;
    if(v >= MOD)v -= MOD;
}
inline int mul(int a, int b){
    return (1ll*a*b)%MOD;
}
int mp(int x, int pw){
    int ans = 1;
    while(pw != 0){
        if(pw&1)ans = mul(ans, x);
        x = mul(x, x);
        pw /= 2;
    }
    return ans;
}
inline int inv(int x){
    assert(x != 0);
    return mp(x, MOD - 2);
}
// const int MX = 5e6 + 10;
// int f[MX], invf[MX], iv[MX];
// inline int C(int n, int r){
//     assert(r <= n);
//     assert(r >= 0);
//     return mul(f[n], mul(invf[n - r], invf[r]));
// }
// void precalc(){
//     f[0] = 1;
//     for(int i = 1;i<MX;i++)
//         f[i] = mul(f[i - 1], i);
//     for(int i = 0;i<MX;i++)
//         invf[i] = inv(f[i]);
//     iv[1] = 1;for(int i = 2;i<MX;i++)iv[i] = MOD - mul(MOD/i, iv[MOD%i]);
// }
