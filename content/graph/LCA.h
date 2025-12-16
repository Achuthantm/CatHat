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
// USES Sparse Table 

template <typename T>
struct SparseTable {
    int n;
    vector<vector<int>> st;
    vector<int> log;
    vector<T> arr;

    void init(const vector<T>& a) {
        n = a.size();
        arr = a;
        int k = __lg(n) + 1;
        st.assign(n, vector<int>(k));
        log.assign(n + 1, 0);

        for (int i = 2; i <= n; i++)
            log[i] = log[i / 2] + 1;

        for (int i = 0; i < n; i++)
            st[i][0] = i;

        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                int left_idx = st[i][j - 1];
                int right_idx = st[i + (1 << (j - 1))][j - 1];
                
                if (arr[left_idx] < arr[right_idx])
                    st[i][j] = left_idx;
                else
                    st[i][j] = right_idx;
            }
        }
    }

    int index(int L, int R) {
        int j = log[R - L + 1];
        int left_idx = st[L][j];
        int right_idx = st[R - (1 << j) + 1][j];

        if (arr[left_idx] < arr[right_idx])
            return left_idx;
        else
            return right_idx;
    }
};

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
