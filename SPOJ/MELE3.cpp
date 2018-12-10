/***** MELE3 - MELE3 *****/
/**** https://www.spoj.com/problems/MELE3/ ****/

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
const int MAX = 1001;
const int TIME_PER_FLOOR = 5;

ll distTo[MAX];
ll edgeTo[MAX];
vll adj[MAX];
ll n, m;
priority_queue<pll, vpll, greater<pll>> pq;

ll weight(int v, int w, ll t)
{
    ll time_one_lap = (abs(v - w) * TIME_PER_FLOOR);
    ll laps = t / time_one_lap;
    bool odd_laps = laps & 1;
    bool going_up = v < w;

   // DEBUG(time_one_lap)

    if (odd_laps && going_up)
    {
        return time_one_lap - (t % time_one_lap) + time_one_lap;
    }
    else if (odd_laps)
    {
        return (2 * time_one_lap - (t % time_one_lap)) % (2 * time_one_lap) + time_one_lap;
    }
    else if (going_up)
    {
        return (2 * time_one_lap - (t % time_one_lap)) % (2 * time_one_lap) + time_one_lap;
    }
    else
    {
        return time_one_lap - (t % time_one_lap) + time_one_lap;
    }
}

void relax(int v)
{
    for (int w : adj[v])
    {
        if (distTo[w] > distTo[v] + weight(v, w, distTo[v]))
        {
            distTo[w] = distTo[v] + weight(v, w, distTo[v]);
            edgeTo[w] = v;
            pq.push(mp(distTo[w], w));
        }
    }
}

void dijkstra(int s)
{
    FOR(i, 0, n)
    {
        distTo[i] = 1e15;
    }
    pq.push(mp(0, s));
    distTo[s] = 0;
    while (!pq.empty())
    {
        int v = pq.top().S;
        pq.pop();
        relax(v);
    }
}

int main()
{
   // freopen("input.txt", "r", stdin);
    SPEED

    cin >> n >> m;
    FOR(i, 0, m)
    {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dijkstra(0);

    cout << distTo[n - 1] << endl;
}
/************************************** END OF PROGRAM ******************************************/

