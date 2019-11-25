#include <bits/stdc++.h>
#define SPEED ios_base::sync_with_stdio(false); cin.tie(NULL);
#define FOR(i, a, b) for (ll i = a; i < b; ++i)
#define RFOR(i, b, a) for (ll i = b; i >= a; --i)
#define DEBUG(x) cout << ">> " << #x << " : " << x << endl;
#define endl "\n"
#define pb(x) push_back(x)
#define ALL(x) x.begin(), x.end()
#define mp(x, y) make_pair(x, y)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<long long> vll;
typedef vector<int> vi;
typedef pair<ll, ll> pll;
typedef vector<pair<ll, ll>> vpll;
typedef unordered_map<ll, ll> STll;



/***********************************************************
* DFS                                @author: manishjoshi394
************************************************************/
vector<ll> *adj;
bool *marked;
ll *edgeTo;


bool *onStack;
void dfs(ll v)
{
    onStack[v] = true;
    marked[v] = true;
    for (auto w : adj[v])
    {
        if (!marked[w])
        {
            edgeTo[w] = v;
            dfs(w);
        }
        else if (onStack[w])
        {
            solve(v, w);
        }
    }
    onStack[v] = false;
}
int main ()
{
    freopen("input.txt", "r", stdin);
    ll n;
    cin >> n;
    adj = new vector<ll>[n];
    marked = new bool[n];
    edgeTo = new ll[n];
    FOR(i, 0, n)
    {
        edgeTo[i] = -1;
        marked[i] = false;
    }

    onStack = new bool[n];

}




/******************************************************************************
* Number theory utilities                           @author: manishjoshi394
******************************************************************************/

ll myPow(ll x, ll p)
{
    if (p == 0)
        return 1;
    if (p == 1)
        return x;

    ll tmp = (myPow(x, p/2));
    if (p%2 == 0)
        return (tmp * tmp);
    else
        return (x * tmp * tmp);
}

ll dig(ll n)
{
    ll ans = 0;
    while (n > 0)
    {
        n /= 10;
        ans++;
    }
    return ans;
}

string binary(ll num) {
    string res = "";
    while (num > 0) {
        res += (num & 1) + '0';
        num >>= 1;
    }
    reverse(ALL(res));
    return res;
}


/***********************************************************
* MODULAR ARITHMETIC                 @author: manishjoshi394
***********************************************************/
const ll MOD = 1e9 + 7;

ll myPow(ll base, ll exp, ll mod = MOD)
{
    ll result = 1;
    while (exp > 0)
    {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

ll modInverse(ll a, ll m = MOD)
{
    return myPow(a, m - 2, m);
}

ll mul(ll a, ll b, ll mod = MOD)
{
    return ((a % mod) * (b % mod)) % mod;
}

ll add(ll a, ll b, ll mod = MOD)
{
    return ((a % mod) + (b % mod) + mod) % mod;
}


/*************************************************************
* EDGE                                  @author: manishjoshi394
**************************************************************/
class Edge
{
    ll v, w, m_weight;
public :
    Edge(ll v, ll w, ll weight)
    {
        this->v= v;
        this->w = w;
        this->m_weight = weight;
    }
    ll either()
    {
        return v;
    }
    ll other(ll v)
    {
        if (v == this->v)
        {
            return this->w;
        }
        else if (v == this->w){
            return this->v;
        }
        else {
            cerr << "INVALID EDGE PASSED TO other(ll) IN CLASS Edge";
            return -1;
        }
    }
    ll weight() {
        return m_weight;
    }
    struct edge_comp
    {
        inline bool operator()(Edge a, Edge b)
        {return a.weight() > b.weight();};
    };
};

inline ostream& operator << (ostream& out, Edge e) {
    return out << "(" << e.either() << " - " << e.other(e.either()) << ", " << e.weight() << ")";
}



/*************************************************************************
* UNION FIND - WITH RANK AND PATH-COMPRESSION       @author: manishjoshi394
*************************************************************************/
class UnionFind
{
    vector<int> id, size;
    int m_count, m_total;
    vector<list<int>> parts;
public:
    UnionFind(int n)
    {
        m_count = m_total = n;
        id = vector<int>(n);
        size = vector<int>(n);
        parts = vector<list<int>>(n);
        FOR(i, 0, n)
        {
            id[i] = i;
            size[i] = 1;
            parts[i].push_back(i);
        }
    }
    int find(int x)
    {
        while(id[x] != x)
        {
            id[x] = id[id[x]];     // path compression
            x = id[x];
        }
        return x;
    }
    int count()
    {
        return m_count;
    }
    int total() {
        return m_total;
    }
    void join(int x, int y)
    {
        int xRoot = find(x);
        int yRoot = find(y);
        if (xRoot == yRoot)
            return;

        // ranking the trees by sizes
        if (size[xRoot] < size[yRoot])
        {
            id[xRoot] = yRoot;
            size[yRoot] += size[xRoot];
            parts[yRoot].splice(parts[yRoot].end(), parts[xRoot]);
        }
        else {
            id[yRoot] = xRoot;
            size[xRoot] += size[yRoot];
            parts[xRoot].splice(parts[xRoot].end(), parts[yRoot]);
        }
        m_count--;
    }
    bool connected(int v, int w)
    {
        return find(v) == find(w);
    }
};

inline ostream& operator << (ostream& out, UnionFind m) {
    map<int, vector<int>> mp;
    for (int i = 0; i < m.total(); ++i) {
        mp[m.find(i)].push_back(i);
    }
    return out << mp;
}




/**********************************************************************************
* MATRIX DATA TYPE WITH IN-BUILT '*', '^', '=', '<<' OPERATORS   @author: manishjoshi394
**********************************************************************************/
class Matrix
{
    ///"Writing this class was Awesome ! DATED: 10 Oct-2018, 21:57 @NIT-UK(Strike Days)"///
    vector<vector<ll>> arr; ;
public:
    static ll MOD;
    const int N;
    const int M;

    Matrix(const int _N, const int _M, ll init = 0)
    : arr(_N, vector<ll>(_M, init)), N(_N), M(_M) {}

    Matrix(const int N) : Matrix(N, N) { ; };

    vector<ll>& operator[](int i)
    {
        return arr[i];
    }

    Matrix operator*(const Matrix& that)
    {
        assert(this->M == that.N);
        Matrix product(this->N, that.M, 0);
        FOR(i, 0, this->N)
        {
            FOR(j, 0, that.M)
            {
                ll sum = 0ll;
                FOR(r, 0, this->M)
                {
                    sum += this->arr[i][r] * that.arr[r][j] % MOD;
                    if (sum >= MOD) sum -= MOD;
                }
                product[i][j] = sum;
            }
        }
        return product;
    }

    Matrix operator^(ll exp)
    {
        Matrix base = *(this);
        Matrix result = Matrix::identity(base.N);
        while (exp > 0)
        {
            if (exp & 1) result = result * base;
            base = (base * base);
            exp >>= 1;
        }
        return result;
    }

    Matrix& operator=(const Matrix& m) {
        assert(m.N == this->N);
        assert(m.M == this->M);
        FOR(i, 0, N)
            FOR(j, 0, M)
                arr[i][j] = m.arr[i][j];
        return *(this);
    }

    Matrix& operator=(const initializer_list<ll>& _l)
    {
        auto it = _l.begin();
        FOR(i, 0, N)
        {
            FOR(j, 0, M)
            {
                if (it != _l.end())
                    arr[i][j] = *(it++);
                else break;
            }
        }
        return *(this);
    }

    static Matrix identity(ll N)
    {
        Matrix _i(N);
        FOR(i, 0, N)
            FOR(j, 0, N)
                if (i == j) _i.arr[i][j] = 1;
        return _i;
    }
    friend ostream& operator<<(ostream&, const Matrix&);
};

inline ostream& operator << (ostream& out, const Matrix& m) {
    FOR(i, 0, m.N) {
        cout << '|';
        FOR(j, 0, m.M) {
            cout << m.arr[i][j];
            (j != m.M - 1) ? cout << "   " : cout;
        }
        cout << '|' << endl;
    }
    return out;
}
ll Matrix::MOD = 1e9 + 7;  // MOD to be used in Matrix Exponentiation & Multiplication




/**********************************************************************************
* BINARY INDEXED TREE/FENWICK TREE WITH DEBUGGER  @author: manishjoshi394
**********************************************************************************/
class BIT {
    vector<ll> bit;
    int n;
    void validate(int idx) const {
        if (idx >= n || idx < 0) {
            cerr << "Index out of range in BIT" << endl;
            assert(false);
        }
    }
public:
    BIT(int _n, ll init = 0) {
        this->n = _n;
        bit.resize(n + 1);
        FOR(i, 0, n)
        {
            update(i, init);
        }
    }
    template<typename T>
    BIT(const vector<T>& arr) : BIT(arr.size()) {
        n = arr.size();
        FOR(i, 0, n)
        {
            update(i, arr[i]);
        }
    }
    /// one-indexed
    ll pref_sum(int len) const {
        validate((len > 0) ? len - 1 : 0);
        ll val = 0;
        while (len > 0) {
            val += bit[len];
            len -= (len & -len);
        }
        return val;
    }
    /// zero-indexed
    void update(int idx, ll delta) {
        validate(idx);
        idx++;
        while (idx <= n)
        {
            bit[idx] += delta;
            idx += (idx & -idx);
        }
    }
    int size() const {
        return bit.size();
    }
};
inline ostream& operator << (ostream& out, const BIT& bit) {
    vector<ll> vals;
    for (int i = 1; i < bit.size(); ++i) {
        vals.push_back(bit.pref_sum(i) - bit.pref_sum(i - 1));
    }
    return out << vals;
}




/**********************************************************************************
* SEGMENT TREE WITH DEBUGGER (WITH SAMPLE OPERATION)   @author: manishjoshi394
**********************************************************************************/
class SegmentTree {
    vector<ll> _tree;
    int n;

    int left(int v) const {
        return 2 * v;
    }
    int right(int v) const {
        return 2 * v + 1;
    }
    template<typename T>
    void build(int v, int l, int r, const vector<T>& arr) {
        if (l == r) {
            _tree[v] = arr[l];
        } else {
            int mid = l + (r - l) / 2;
            build(left(v), l, mid, arr);
            build(right(v), mid + 1, r, arr);

            _tree[v] = max(_tree[left(v)], _tree[right(v)]);
        }
    }
    void update(int v, int l, int r, int pos, ll new_val) {
        if (l == r) {
            _tree[v] = new_val;
        } else {
            int mid = l + (r - l) / 2;

            if (pos <= mid)
                update(left(v), l, mid, pos, new_val);
            else
                update(right(v), mid + 1, r, pos, new_val);

            _tree[v] = max(_tree[left(v)], _tree[right(v)]);
        }
    }
    ll query(int v, int l, int r, int ql, int qr) const {
        if (ql > qr)
            return LLONG_MIN;
        if (l == ql && r == qr) return _tree[v];
        int mid = l + (r - l) / 2;
        return max(query(left(v), l, mid, ql, min(mid, qr)),
                   query(right(v), mid + 1, r, max(mid + 1, ql), qr));
    }
public:
    template<typename T>
    SegmentTree(const vector<T>& arr) {
        n = arr.size();
        _tree.resize(4 * n);
        build(1, 0, n - 1, arr);
    }
    SegmentTree(int _n, ll _init = 0) : SegmentTree(vector<ll>(_n, _init)) {}

    ll rmaxq(int l, int r) const {
        return query(1, 0, n - 1, l, r);
    }

    void update(int pos, ll new_val) {
        update(1, 0, n - 1, pos, new_val);
    }

    int size() const {
        return n;
    }
};
inline ostream& operator << (ostream& out, SegmentTree& SegTree) {
    vector<ll> vals;
    for (int i = 0; i < SegTree.size(); ++i) {
        vals.push_back(SegTree.rmaxq(i, i));
    }
    return out << vals;
}




/********************************************************************
* HASHING FOR STD::PAIR WITH UNORDERED_MAP @author : manishjoshi394
*********************************************************************/
template<typename T1, typename T2, typename... Args>
inline ostream& operator << (ostream& out, const unordered_map<T1, T2, Args...>& m) {
    return out << map<T1, T2>(ALL(m));
}
template<typename T, typename... Args>
inline ostream& operator << (ostream& out, const unordered_set<T, Args...>& s) {
    return out << set<T>(ALL(s));
}
struct pair_hash {
    template<typename T1, typename T2>
    inline size_t operator()(const pair<T1, T2>& p) const
    {
        return hash<T1>()(p.first) * 31 + hash<T2>()(p.second);
    }
};




/**
  ######################################################################
  #######################   THE   BIG   INT   ##########################
  @credit goes to original author, whom I don't know. and to arpa for adding pow and lcm,
*/
const int base = 1000000000;
const int base_digits = 9;
struct bigint {
	vector<int> a;
	int sign;
	/*<arpa>*/
	int size(){
		if(a.empty())return 0;
		int ans=((int)a.size()-1)*base_digits;
		int ca=a.back();
		while(ca)
			ans++,ca/=10;
		return ans;
	}
	bigint operator ^(const bigint &v){
		bigint ans=1,me=*this,b=v;
		while(!b.isZero()){
			if(b%2)
				ans*=me;
			me*=me,b/=2;
		}
		return ans;
	}
	string to_string(){
		stringstream ss;
		ss << *this;
		string s;
		ss >> s;
		return s;
	}
	int sumof(){
		string s = to_string();
		int ans = 0;
		for(auto c : s)  ans += c - '0';
		return ans;
	}
	/*</arpa>*/
	bigint() :
		sign(1) {
	}

	bigint(long long v) {
		*this = v;
	}

	bigint(const string &s) {
		read(s);
	}

	void operator=(const bigint &v) {
		sign = v.sign;
		a = v.a;
	}

	void operator=(long long v) {
		sign = 1;
		a.clear();
		if (v < 0)
			sign = -1, v = -v;
		for (; v > 0; v = v / base)
			a.push_back((int)(v % (ll)base));
	}

	bigint operator+(const bigint &v) const {
		if (sign == v.sign) {
			bigint res = v;

			for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
				if (i == (int) res.a.size())
					res.a.push_back(0);
				res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
				carry = res.a[i] >= base;
				if (carry)
					res.a[i] -= base;
			}
			return res;
		}
		return *this - (-v);
	}

	bigint operator-(const bigint &v) const {
		if (sign == v.sign) {
			if (abs() >= v.abs()) {
				bigint res = *this;
				for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
					res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
					carry = res.a[i] < 0;
					if (carry)
						res.a[i] += base;
				}
				res.trim();
				return res;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}

	void operator*=(int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}

	bigint operator*(int v) const {
		bigint res = *this;
		res *= v;
		return res;
	}

	void operator*=(long long v) {
		if (v < 0)
			sign = -sign, v = -v;
		if(v > base){
			*this = *this * (v / base) * base + *this * (v % base);
			return ;
		}
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}

	bigint operator*(long long v) const {
		bigint res = *this;
		res *= v;
		return res;
	}

	friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
		int norm = base / (b1.a.back() + 1);
		bigint a = a1.abs() * norm;
		bigint b = b1.abs() * norm;
		bigint q, r;
		q.a.resize(a.a.size());

		for (int i = (int)a.a.size() - 1; i >= 0; i--) {
			r *= base;
			r += a.a[i];
			int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
			int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
			int d = int(((long long) base * s1 + s2) / b.a.back());
			r -= b * d;
			while (r < 0)
				r += b, --d;
			q.a[i] = d;
		}

		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.trim();
		r.trim();
		return make_pair(q, r / norm);
	}

	bigint operator/(const bigint &v) const {
		return divmod(*this, v).first;
	}

	bigint operator%(const bigint &v) const {
		return divmod(*this, v).second;
	}

	void operator/=(int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
			long long cur = a[i] + rem * (long long) base;
			a[i] = (int) (cur / v);
			rem = (int) (cur % v);
		}
		trim();
	}

	bigint operator/(int v) const {
		bigint res = *this;
		res /= v;
		return res;
	}

	int operator%(int v) const {
		if (v < 0)
			v = -v;
		int m = 0;
		for (int i = (int)a.size() - 1; i >= 0; --i)
			m = int((a[i] + m * (long long) base) % v);
		return m * sign;
	}

	void operator+=(const bigint &v) {
		*this = *this + v;
	}
	void operator-=(const bigint &v) {
		*this = *this - v;
	}
	void operator*=(const bigint &v) {
		*this = *this * v;
	}
	void operator/=(const bigint &v) {
		*this = *this / v;
	}

	bool operator<(const bigint &v) const {
		if (sign != v.sign)
			return sign < v.sign;
		if (a.size() != v.a.size())
			return a.size() * sign < v.a.size() * v.sign;
		for (int i = int(a.size()) - 1; i >= 0; i--)
			if (a[i] != v.a[i])
				return a[i] * sign < v.a[i] * sign;
		return false;
	}

	bool operator>(const bigint &v) const {
		return v < *this;
	}
	bool operator<=(const bigint &v) const {
		return !(v < *this);
	}
	bool operator>=(const bigint &v) const {
		return !(*this < v);
	}
	bool operator==(const bigint &v) const {
		return !(*this < v) && !(v < *this);
	}
	bool operator!=(const bigint &v) const {
		return *this < v || v < *this;
	}

	void trim() {
		while (!a.empty() && !a.back())
			a.pop_back();
		if (a.empty())
			sign = 1;
	}

	bool isZero() const {
		return a.empty() || (a.size() == 1 && !a[0]);
	}

	bigint operator-() const {
		bigint res = *this;
		res.sign = -sign;
		return res;
	}

	bigint abs() const {
		bigint res = *this;
		res.sign *= res.sign;
		return res;
	}

	long long longValue() const {
		long long res = 0;
		for (int i = (int)a.size() - 1; i >= 0; i--)
			res = res * base + a[i];
		return res * sign;
	}

	friend bigint gcd(const bigint &a, const bigint &b) {
		return b.isZero() ? a : gcd(b, a % b);
	}
	friend bigint lcm(const bigint &a, const bigint &b) {
		return a / gcd(a, b) * b;
	}

	void read(const string &s) {
		sign = 1;
		a.clear();
		int pos = 0;
		while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-')
				sign = -sign;
			++pos;
		}
		for (int i = (int)s.size() - 1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = max(pos, i - base_digits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			a.push_back(x);
		}
		trim();
	}

	friend istream& operator>>(istream &stream, bigint &v) {
		string s;
		stream >> s;
		v.read(s);
		return stream;
	}

	friend ostream& operator<<(ostream &stream, const bigint &v) {
		if (v.sign == -1)
			stream << '-';
		stream << (v.a.empty() ? 0 : v.a.back());
		for (int i = (int) v.a.size() - 2; i >= 0; --i)
			stream << setw(base_digits) << setfill('0') << v.a[i];
		return stream;
	}

	static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
		vector<long long> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < (int) p.size(); i++)
			p[i] = p[i - 1] * 10;
		vector<int> res;
		long long cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < (int) a.size(); i++) {
			cur += a[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(int(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((int) cur);
		while (!res.empty() && !res.back())
			res.pop_back();
		return res;
	}

	typedef vector<long long> vll;

	static vll karatsubaMultiply(const vll &a, const vll &b) {
		int n = int(a.size());
		vll res(n + n);
		if (n <= 32) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					res[i + j] += a[i] * b[j];
			return res;
		}

		int k = n >> 1;
		vll a1(a.begin(), a.begin() + k);
		vll a2(a.begin() + k, a.end());
		vll b1(b.begin(), b.begin() + k);
		vll b2(b.begin() + k, b.end());

		vll a1b1 = karatsubaMultiply(a1, b1);
		vll a2b2 = karatsubaMultiply(a2, b2);

		for (int i = 0; i < k; i++)
			a2[i] += a1[i];
		for (int i = 0; i < k; i++)
			b2[i] += b1[i];

		vll r = karatsubaMultiply(a2, b2);
		for (int i = 0; i < (int) a1b1.size(); i++)
			r[i] -= a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			r[i] -= a2b2[i];

		for (int i = 0; i < (int) r.size(); i++)
			res[i + k] += r[i];
		for (int i = 0; i < (int) a1b1.size(); i++)
			res[i] += a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			res[i + n] += a2b2[i];
		return res;
	}

	bigint operator*(const bigint &v) const {
		vector<int> a6 = convert_base(this->a, base_digits, 6);
		vector<int> b6 = convert_base(v.a, base_digits, 6);
		vll A(a6.begin(), a6.end());
		vll b(b6.begin(), b6.end());
		while (A.size() < b.size())
			A.push_back(0);
		while (b.size() < A.size())
			b.push_back(0);
		while (A.size() & (A.size() - 1))
			A.push_back(0), b.push_back(0);
		vll c = karatsubaMultiply(A, b);
		bigint res;
		res.sign = sign * v.sign;
		for (int i = 0, carry = 0; i < (int) c.size(); i++) {
			long long cur = c[i] + carry;
			res.a.push_back((int) (cur % 1000000));
			carry = (int) (cur / 1000000);
		}
		res.a = convert_base(res.a, 6, base_digits);
		res.trim();
		return res;
	}
};
/*
  #######################   THE   BIG   INT   ##########################
  ######################################################################
*/
