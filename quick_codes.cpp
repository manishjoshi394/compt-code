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
* DFS
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
* Number theory utilities
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




/*************************************************************
* EDGE
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
            return w;
        }
        else if (v == this->w){
            return v;
        }
        else {
            cerr << "INVALID EDGE PASSED TO other(ll) IN CLASS Edge";
            return -1;
        }
    }
    ll weight() {
        return m_weight;
    }
};





/*************************************************************************
* UNION FIND - WITH RANK AND PATH-COMPRESSION
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
            x = id[x];
        }
        return x;
    }
    ll count()
    {
        return m_count;
    }
    void union(ll x, ll y)
    {
        ll xRoot = find(x);
        ll yRoot = find(y);
        if (xRoot == yRoot)
            return;
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
