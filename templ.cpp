#include <bits/stdc++.h>
using namespace std;

#define int int64_t

#define all(x) (x).begin(),(x).end()

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
	for (const auto& i: v) out << i << ' ';
	return out;
}

template<class T>
std::istream& operator<<(std::istream& in, std::vector<T>& v) {
	for (auto& i: v) in >> i;
	return in;
}



template<class T>
class ST { // SEGMENT TREE
	std::vector<T> m_st;
	const std::vector<T> m_arr;

	std::function<T(const T& a, const T& b)> m_sum;
	std::function<void(T&, T&, T&)> m_push;
	
	void m_build(int v, int tl, int tr) {
		if (tl == tr) m_st[v] = m_arr[tl];
		else {
			int tm = (tl + tr) / 2;
			m_build(v*2 + 1, tl, tm);
			m_build(v*2 + 2, tm + 1, tr);
			m_st[v] = m_sum(m_st[v*2 + 1], m_st[v*2 + 2]);
		}
	}

	void m_update(int v, int tl, int tr, const int pos, const T& new_val) {
		if (tl == tr) m_st[v] = new_val;
		else {
			m_push(m_st[v], m_st[2*v + 1], m_st[2*v + 2]);
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				m_update(v*2 + 1, tl, tm, pos, new_val);
			else
				m_update(v*2 + 2, tm + 1, tr, pos, new_val);
			m_st[v] = m_sum(m_st[v*2 + 1], m_st[v*2 + 2]);
		}
	}

	T m_query(int v, int tl, int tr, int l, int r) {
	    if (r != l) m_push(m_st[v], m_st[2*v + 1], m_st[2*v + 2]);
	    if (l == tl && r == tr) { return m_st[v]; }
	    int tm = (tl + tr) / 2;
	    if (l <= tm && r <= tm) return m_query(v*2 + 1, tl, tm, l, r);
	    else if (l > tm && r > tm) return m_query(v*2 + 2, tm+1, tr, l, r);
	    else
	    	return m_sum(m_query(v*2 + 1, tl, tm, l, tm), m_query(v*2 + 2, tm+1, tr, tm+1, r));
	}


	public:
		ST(const std::vector<T>& v, std::function<T(const T&, const T&)> sum) : m_arr(v), m_sum{sum} {
			m_push = [](T& a, T& b, T& c){};
			m_st.resize(4*m_arr.size());
			m_build(0, 0, m_arr.size()-1);
		}

		ST(const std::vector<T>& v, std::function<T(const T&, const T&)> sum, std::function<void(T&, T&, T&)> _push) : m_arr(v), m_sum{sum}, m_push{_push} {
			m_st.resize(4*m_arr.size());
			m_build(0, 0, m_arr.size()-1);
		}
		
		void upd(const int pos, const T& new_val) {
			m_update(0, 0, m_arr.size()-1, pos, new_val);
		}

		T q(int l, int r) {
			return m_query(0, 0, m_arr.size()-1, l, r);
		}
};

template <class T>
class DST { // DISJOINT SPARSE TABLE
	std::vector<std::vector<T>> m_dst_l;
	std::vector<std::vector<T>> m_dst_r;

	std::function<T(const T&, const T&)> m_min;

	public:
		const std::vector<T> m_arr;

		DST(const std::vector<T>& v, std::function<T(const T&, const T&)> _min) : m_arr(v), m_min{_min} {
			m_dst_l.resize(63, m_arr);
			m_dst_r.resize(63, m_arr);
			for (int i = 1; i < 63; i++) {
				const int curr = ((int)1)<<i;
				for (int j = 0; j < m_arr.size(); j++) {
					if (j%curr != 0) m_dst_l[i][j] = m_min(m_dst_l[i][j], m_dst_l[i][j-1]);
				}
				for (int j = m_arr.size()-2; j >= 0; j--) {
					if (j%curr != curr-1) m_dst_r[i][j] = m_min(m_dst_r[i][j], m_dst_r[i][j+1]);
				}
			}
		}

		DST(const DST<T>& dst) : DST(dst.m_arr, dst.m_min) {}

		T query(int l, int r) {
			if (l == r) return m_arr[l];

			const int diff = r-l+1;
			const char lg = diff&(diff-1) == 0 ? __lg(diff) : __lg(diff)+1;
			const int curr = ((int)1)<<lg;

			if (l%curr <= curr-diff) return m_min(m_dst_r[lg-1][l], m_dst_l[lg-1][r]);
			else return m_min(m_dst_r[lg][l], m_dst_l[lg][r]);
		}
};

signed main() {

	DST<int> dst({1, 2, 3, 4, 5}, [](int a, int b) {return a + b;});
	cout << dst.query(2, 2) << endl;

	return 0;
}
