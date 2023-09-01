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
	std::vector<T> m_arr;

	using sum_sig = T(const T& a, const T& b);

	std::function<sum_sig> m_sum;
	
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
		ST(std::initializer_list<T> ilist, std::function<sum_sig> sum) : m_arr(ilist), m_sum{sum} {
			m_st.resize(4*m_arr.size());
			m_build(0, 0, m_arr.size()-1);
		}
		
		template<class Iter1, class Iter2>
		ST(Iter1 iter1, Iter2 iter2, std::function<sum_sig> sum) : m_arr(iter1, iter2), m_sum{sum} {
			m_st.resize(4*m_arr.size());
			m_build(0, 0, m_arr.size()-1);
		}
		
		ST(const std::vector<T>& v, std::function<sum_sig> sum) : m_arr(v), m_sum{sum} {
			m_st.resize(4*m_arr.size());
			m_build(0, 0, m_arr.size()-1);
		}

		ST(const ST<T>& st) : ST(st.getArr(), st.m_sum) {}
		
		const std::vector<T>& getArr() const { return m_arr; };
		
		void update(int pos, const T& new_val) {
			m_update(0, 0, m_arr.size()-1, pos, new_val);
		}
};

template <typename T>
class DST { // DISJOINT SPARSE TABLE
	std::vector<std::vector<T>> m_dst;
	std::vector<T> m_arr;

	using min_sig = T(const T& a, const T& b);

	std::function<min_sig> m_min;

	public:
		DST(std::initializer_list<T> ilist, std::function<min_sig> _min) : m_arr(ilist), m_min{_min} {
		   
		}
		
		template<class Iter1, class Iter2>
		DST(Iter1 iter1, Iter2 iter2, std::function<min_sig> _min) : m_arr(iter1, iter2), m_min{_min} {
			
		}
		
		DST(const std::vector<T>& v, std::function<min_sig> _min) : m_arr(v), m_min{_min} {
			
		}

		DST(const DST<T>& dst) : DST(dst.getArr(), dst.m_min) {}
		
		const std::vector<T>& getArr() const { return m_arr; };
};

signed main() {



	return 0;
}
