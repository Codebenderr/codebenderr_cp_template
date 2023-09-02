#include <bits/stdc++.h>
using namespace std;

#define int int64_t

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
	for (const auto& i: v) out << i << ' ';
	return out;
}

void pyn(bool b) { std::cout << (b ? "YES" : "NO"); }

template<typename T>
class ST { // SEGMENT TREE
	std::vector<T> m_st;
	const std::vector<T> m_arr;

	using sum_sign = T(const T& a, const T& b);

	std::function<sum_sign> m_sum;
	
	void m_build(int v, int tl, int tr) {
		if (tl == tr) m_st[v] = m_arr[tl];
		else {
			int tm = (tl + tr) / 2;
			m_build(v*2 + 1, tl, tm);
			m_build(v*2 + 2, tm + 1, tr);
			m_st[v] = m_sum(m_st[v*2 + 1], m_st[v*2 + 2]);
		}
	}

	void m_update(int v, int tl, int tr, int pos, const T& new_val) {
		if (tl == tr) { m_st[v] = new_val; m_arr[pos] = new_val; }
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				m_update(v*2 + 1, tl, tm, pos, new_val);
			else
				m_update(v*2 + 2, tm + 1, tr, pos, new_val);
			m_st[v] = m_sum(m_st[v*2 + 1], m_st[v*2 + 2]);
		}
	}

	public:
		ST(const std::vector<T>& v, std::function<sum_sign> sum) : m_arr(v), m_sum{sum} {
			m_st.resize(4*m_arr.size());
			m_build(0, 0, m_arr.size()-1);
		}
		
		void update(const int pos, const T& new_val) {
			m_update(0, 0, m_arr.size()-1, pos, new_val);
		}
};

template <typename T>
class DST { // DISJOINT SPARSE TABLE
	std::vector<std::vector<T>> m_dst;

	using min_sign = T(const T& a, const T& b);

	std::function<min_sign> m_min;

	public:
		const std::vector<T> m_arr;

		DST(const std::vector<T>& v, std::function<min_sign> _min) : m_arr(v), m_min{_min} {
			m_dst.resize(63, m_arr);
			for (int i = 0; i < )			
		}

		DST(const DST<T>& dst) : DST(dst.m_arr, dst.m_min) {}
};

signed main() {



	return 0;
}
