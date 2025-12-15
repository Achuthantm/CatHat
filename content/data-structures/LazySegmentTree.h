/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Time: O(\log N).
 * Status: stress-tested a bit
 */
#pragma once

const int N = 3e5 + 10;
struct node{
    int lz, mn, idx;
}t[4*N];
node merge(node a, node b){
    if(a.lz + a.mn < b.lz + b.mn)
        return {0, a.mn + a.lz, a.idx};
    else if(a.lz + a.mn > b.lz + b.mn) return {0, b.mn + b.lz, b.idx};
    else{
        if(a.idx < b.idx)return {0, a.mn + a.lz, a.idx};
        else return {0, b.mn + b.lz, b.idx};
    }
}
void push(int v){
    t[v*2].lz += t[v].lz;
    t[v*2 + 1].lz += t[v].lz;
    t[v].lz = 0;
    t[v] = merge(t[v*2], t[v*2 + 1]);
}
node nulln = {0, (int)1e9, 0};
void build(int v, int tl, int tr){
    if(tl == tr){
        t[v] = {0, 0, tl};
    }
    else{
        int tm = (tl + tr)/2;
        build(v*2, tl, tm);
        build(v*2 + 1,tm + 1, tr);
        t[v] = merge(t[v*2], t[v*2 + 1]);
    }
}
// void print(int v, int tl, int tr){
//     deb(v, tl, tr);
//     deb(t[v].lz, t[v].mn, t[v].idx);
//     if(tl != tr){
//         int tm = (tl + tr)/2;
//         print(v*2, tl, tm);
//         print(v*2 + 1,tm + 1, tr);
//     }
// }
void update(int add, int l, int r, int v, int tl, int tr){
    if(l < tl || r > tr || l > r){
        return;
    }
    if(l == tl && r == tr){
        t[v].lz += add;
    }
    else{
        push(v);
        int tm = (tl + tr)/2;
        update(add, l, min(r, tm), v*2, tl, tm);
        update(add, max(l, tm + 1), r, v*2 + 1, tm + 1, tr);
        t[v] = merge(t[v*2], t[v*2 + 1]);
    }
}
node query(int l, int r, int v, int tl, int tr){
    if(l > r)return nulln;
    if(l == tl && r == tr){
        return t[v];
    }
    else{
        push(v);
        int tm = (tl + tr)/2;
        return merge(query(l, min(r, tm), v*2, tl, tm), query(max(tm + 1, l), r, v*2 + 1, tm + 1, tr));
    }
}
