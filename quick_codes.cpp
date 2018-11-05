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



/***********************************************************
* MODULAR ARITHMETIC                 @author: manishjoshi394
***********************************************************/
const ll MOD = 1e9 + 9;

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
    ll *id;
    ll *size;
    ll m_count;
public:
    UnionFind(ll n)
    {
        m_count = n;
        id = new ll[n];
        size = new ll[n];
        FOR(i, 0, n)
        {
            id[i] = i;
            size[i] = 1;
        }
    }
    ll find(ll x)
    {
        while(id[x] != x)
        {
            id[x] = id[id[x]];     // path compression
            x = id[x];
        }
        return x;
    }
    ll count()
    {
        return m_count;
    }
    void join(ll x, ll y)
    {
        ll xRoot = find(x);
        ll yRoot = find(y);
        if (xRoot == yRoot)
            return;

        // ranking the trees by sizes
        if (size[xRoot] < size[yRoot])
        {
            id[xRoot] = yRoot;
            size[yRoot] += size[xRoot];
        }
        else {
            id[yRoot] = xRoot;
            size[xRoot] += size[yRoot];
        }
        m_count--;
    }
    bool connected(ll v, ll w)
    {
        return find(v) == find(w);
    }
};




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
                FOR(r, 0, this->M)
                {
                    product[i][j] += this->arr[i][r] * that.arr[r][j];
                    product[i][j] %= Matrix::MOD;
                }
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
