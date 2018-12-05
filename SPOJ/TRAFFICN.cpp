/*******https://www.spoj.com/problems/TRAFFICN/*********/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SPEED ios_base::sync_with_stdio(false); cin.tie(NULL);
#define FOR(i, a, b) for (ll i = a; i < b; ++i)
#define RFOR(i, b, a) for (ll i = b; i >= a; --i)
#define ALL(x) x.begin(), x.end()
#define DEBUG(args...) { string _s = #args; replace(ALL(_s), ' ', '\0');\
replace(ALL(_s), ',', ' ');\
stringstream _ss(_s); istream_iterator<string> _it(_ss); _debug(_it, args);}
#define endl "\n"
#define F first
#define S second
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void _debug(istream_iterator<string>) {}
template<typename T, typename... Args>
void _debug(istream_iterator<string> it, T first, Args... args) {
    cerr << ">> " << *it << " : " << first << endl; _debug(++it, args...);
}
template <typename T1, typename T2>
inline ostream& operator << (ostream& out, const pair<T1, T2>& p) {
    return out << "(" << p.F << ", " << p.S << ")";
}
template<typename T>
inline ostream& operator << (ostream& out, const vector<T>& v) {
    if (v.empty()) return out << "[]";
    else { out << '['; for (auto& e : v) { out << e << ", "; } return out << "\b\b]"; }
}
template<typename T>
inline ostream& operator << (ostream& out, const set<T>& s) {
    if (s.empty()) return out << "{}";
    else { out << '{'; for (auto& e : s) { out << e << ", "; } return out << "\b\b}"; }
}
template<typename T>
inline ostream& operator << (ostream& out, const unordered_set<T>& s) {
    return out << set<T>(ALL(s));
}
template<typename T1, typename T2>
inline ostream& operator << (ostream& out, const map<T1, T2>& m) {
    if (m.empty()) return out << "{}";
    out << '{'; for (auto& p : m) { out << p << ", "; } return out << "\b\b}";
}
template<typename T1, typename T2>
inline ostream& operator << (ostream& out, const unordered_map<T1, T2>& m) {
    return out << map<T1, T2>(ALL(m));
}
template<typename T>
inline ostream& operator << (ostream& out, const ordered_set<T>& s) {
    return out << set<T>(ALL(s));
}

typedef long long ll;
typedef long double ld;
typedef vector<long long> vll;
typedef pair<ll, ll> pll;
typedef vector<pair<ll, ll>> vpll;
typedef unordered_map<ll, ll> STll;
/************************************** MAIN PROGRAM ********************************************/
const int MAX = 200005;
const ll INF = 1e18;

vpll adj[MAX];
ll distTo[MAX];

priority_queue<pll, vpll, greater<pll>> pq;

/// returns corresponding vertex in the second layer
int f(int v)
{
    return v + MAX / 2;
}

int weightOf(int v, int w)
{
    for (auto y : adj[v])
    {
        if (y.F == w)
        {
            return y.S;
        }
    }
}

void relax(int v)
{
    for (auto p : adj[v])
    {
        int w = p.F;
        int weight = p.S;

        if (distTo[w] > distTo[v] + weight)
        {
            distTo[w] = distTo[v] + weight;

            pq.push(mp(distTo[w], w));
        }
    }
}

void dijkstra(int s)
{
    FOR(i, 0, MAX)
    {
        distTo[i] = INF;
    }

    distTo[s] = 0;
    pq.push(mp(0, s));

    while (!pq.empty())
    {
        relax(pq.top().S);
        pq.pop();
    }
}

int main()
{
    //freopen("input.txt", "r", stdin);
    SPEED
    ll t;
    cin >> t;
    FOR(_, 0, t)
    {
        FOR(i, 0, MAX)
        {
            adj[i].clear();
        }
        ll n, m, k, s, t;
        cin >> n >> m >> k >> s >> t;
        s--, t--;
        FOR(i, 0, m)
        {
            ll u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            adj[u].pb(mp(v, w));
            adj[f(u)].pb(mp(f(v), w));
        }
        FOR(i, 0, k)
        {
            ll u, v, weight;
            cin >> u >> v >> weight;
            u--, v--;
            adj[u].pb(mp(f(v), weight));
            adj[v].pb(mp(f(u), weight));
        }
        dijkstra(s);
        if (distTo[f(t)] == distTo[t] && distTo[t] == INF)
        {
            cout << -1 << endl;
            continue;
        }

        if (distTo[t] < distTo[f(t)])
        {
            cout << distTo[t] << endl;
        }
        else
        {
            cout << distTo[f(t)] << endl;
        }
    }
}
/************************************** END OF PROGRAM ******************************************/

