#include <bits/stdc++.h>
using namespace std;

#define int int64_t

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    for (const auto& i: v) out << i << ' ';
    return out;
}

template<typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() > b.size()) {
        std::vector<T> c(a);
        for (int i = 0; i < b.size(); i++) c[i] = c[i] + b[i];
        return c;
    } else {
        std::vector<T> c(b);
        for (int i = 0; i < a.size(); i++) c[i] = c[i] + a[i];
        return c;
    }
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> c(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            c[i+j] = c[i+j] + a[i]*b[j];
    return c;
}

void pyn(bool b) { std::cout << (b ? "YES" : "NO"); }

template<typename T>
class ST {
    std::vector<T> m_st;
    std::vector<T> m_arr;
    std::function<T(const T& a, const T& b)> m_sum;
    
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
        ST(std::initializer_list<T> ilist, std::function<T(const T& a, const T& b)> sum) : m_arr(ilist), m_sum{sum} {
            m_st.resize(4*m_arr.size());
            m_build(0, 0, m_arr.size()-1);
        }
        
        template<class Iter1, class Iter2>
        ST(Iter1 iter1, Iter2 iter2, std::function<T(const T& a, const T& b)> sum) : m_arr(iter1, iter2), m_sum{sum} {
            m_st.resize(4*m_arr.size());
            m_build(0, 0, m_arr.size()-1);
        }
        
        ST(const std::vector<T>& v, std::function<T(const T& a, const T& b)> sum) : m_arr(v), m_sum{sum} {
            m_st.resize(4*m_arr.size());
            m_build(0, 0, m_arr.size()-1);
        }

        ST(const ST<T>& st) : ST(st.getArr(), st.m_sum) {}
        
        const std::vector<T>& getArr() const { return m_arr; };
        
        void update(int pos, const T& new_val) {
            m_update(0, 0, m_arr.size()-1, pos, new_val);
        }
};

signed main() {


#if 0
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
    }
#endif


#if 0
    int n; cin >> n;
#endif



    return 0;
}
