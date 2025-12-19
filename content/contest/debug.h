#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#define deb(...) cout << __LINE__ << ": [", dbg_out(#__VA_ARGS__, __VA_ARGS__)
#else
#define deb(...)
#endif

// Forward declarations
template<typename T> void _p(const T& x);

// Primitive Overloads
void _p(bool x) { cout << (x ? "T" : "F"); }
void _p(char x) { cout << '\'' << x << '\''; }
void _p(const char* x) { cout << '\"' << x << '\"'; }
void _p(const string& x) { cout << '\"' << x << '\"'; }

// Pair Support
template<typename T, typename U>
void _p(const pair<T, U>& x) { cout << '('; _p(x.first); cout << ','; _p(x.second); cout << ')'; }

// Tuple Helper
template<size_t i, typename T>
typename enable_if<i == tuple_size<T>::value>::type _pt(const T&) {}
template<size_t i, typename T>
typename enable_if<i < tuple_size<T>::value>::type _pt(const T& t) {
    if(i) cout << ","; _p(get<i>(t)); _pt<i + 1>(t);
}
template<typename... T>
void _p(const tuple<T...>& x) { cout << "("; _pt<0>(x); cout << ")"; }

// Final logic using tag dispatching to avoid ambiguity
template<typename T>
auto _p_impl(const T& x, int) -> decltype(x.begin(), void()) {
    int f = 0; cout << '{';
    for (auto &i : x) cout << (f++ ? "," : ""), _p(i);
    cout << '}';
}
template<typename T>
void _p_impl(const T& x, long) { cout << x; }

template<typename T>
void _p(const T& x) { _p_impl(x, 0); }

// Variadic Debug Output
void dbg_out(const char*) { cout << "]\n"; }
template<typename T, typename... V>
void dbg_out(const char* names, T head, V... tail) {
    int i = 0, b = 0;
    while(names[i] && (names[i] != ',' || b)) {
        if(names[i] == '(' || names[i] == '<' || names[i] == '{') b++;
        if(names[i] == ')' || names[i] == '>' || names[i] == '}') b--;
        cout << names[i++];
    }
    cout << " = "; _p(head);
    if(sizeof...(tail)) { cout << " ||"; dbg_out(names + i + 1, tail...); }
    else dbg_out("");
}