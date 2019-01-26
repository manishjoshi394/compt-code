/**************************************************************************
	USACO 2017 December Contest, Gold
	Problem 2. Barn Painting
	SOLUTION: REFER THE CODE
	Problem Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=766
	PRE-REQUISITES: DP on Trees

***************************************************************************/
	
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
const int MAX = 1e5 + 1;
ll n, k;
ll dp[MAX][4];
/// dp[i][j] ways to color the subtree rooted at vertex i with jth color
const int MOD = 1e9 + 7;
ll color[MAX];

vector<int> adj[MAX];

void dfs(int v, int u)
{
    for (int w : adj[v]) {
        if (w == u) continue;

        dfs(w, v);
    }

    for (int clrV : {1, 2, 3}) {
        if (color[v] && clrV != color[v]) {
            dp[v][clrV] = 0;
            continue;
        }

        dp[v][clrV] = 1;
        for (int w : adj[v]) {
            if (w == u) continue;

            ll sum = 0;
            for (int clrW : {1, 2, 3}) {
                if (clrV == clrW) continue;

                sum += dp[w][clrW];
                sum %= MOD;
            }
            dp[v][clrV] *= sum;
            dp[v][clrV] %= MOD;
        }
       // DEBUG(dp[v][clrV])
    }

}

int main()
{
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);
    SPEED
    cin >> n >> k;
    FOR(i, 0, n - 1)
    {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    FOR(i, 0, k)
    {
        ll b, c;
        cin >> b >> c;
        b--;
        color[b] = c;
    }
    ll ans = 0;
    dfs(0, 0);
    //DEBUG(vll(color, color + n))
    FOR(clr, 1, 4) {
        ans += dp[0][clr];
        ans %= MOD;
    }
    cout << ans;
}
/************************************** END OF PROGRAM ******************************************/

