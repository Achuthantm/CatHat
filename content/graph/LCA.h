/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

// USES Sparse Table 

struct LCA{
	int n;
	SparseTable<int> st;
	vector<vector<int>> adj;
	vector<int> d, tour, dep_tour, pos;
	LCA(int _n){
		n = _n;
		adj.resize(n);
		d.resize(n);
		pos.resize(n);
	}
	void add(int a,int b){
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	void dfs(int i,int p){
		pos[i] = tour.size();
		tour.push_back(i);
		dep_tour.push_back(d[tour.back()]);
		for(int e : adj[i]){
			if(e != p){
				d[e] = d[i] + 1;
				dfs(e, i);
				tour.push_back(i);
				dep_tour.push_back(d[tour.back()]);
			}
		}
	}
	void init(int root){
		dfs(root, root);
		st.init(dep_tour);
	}
	int lca(int a,int b){
		a = pos[a];
		b = pos[b];
		if(a > b)swap(a,b);
		return tour[st.index(a, b)];
	}
};
