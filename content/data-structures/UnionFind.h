/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
#pragma once
struct ufds{
        int n;
        vector<int> par, siz;
        ufds(int _n){
                n = _n;
                par.resize(n);
                iota(par.begin(), par.end(), 0);
                siz.resize(n, 1);
        }
        int f(int i){
                return (par[i] == i)?i : par[i] = f(par[i]);
        }
        bool u(int i,int j){
                i = f(i);
                j = f(j);
                if(i == j)return false;
                if(siz[i] < siz[j])swap(i, j);
                siz[i] += siz[j];
                par[j] = i;
                return true;
        }
        bool same(int a,int b){
            return f(a) == f(b);
        }
};
