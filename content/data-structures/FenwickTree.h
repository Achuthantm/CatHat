/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once
template<class T>
struct BIT{
    // It is 0 indexed
    vector<T> bit;
    int n;
    BIT(){}
    BIT(int _n){ init(_n); }
    void init(int _n){
        n = _n;
        bit.resize(_n + 1);
    }
    void update(int idx, T val){
        for(++idx;idx<=n;idx += (idx&-idx)){
            bit[idx]+= val;
        }
    }
    T sum(int idx){
        T sum = 0;
        for(++idx;idx>0;idx -= (idx&-idx)){
            sum += bit[idx];
        }
        return sum;
    }
    T query(int l,int r){
        return sum(r) - sum(l - 1);
    }
};
