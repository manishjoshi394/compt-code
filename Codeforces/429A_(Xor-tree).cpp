#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SPEED ios_base::sync_with_stdio(false); cin.tie(NULL);
#define FOR(i, a, b) for (ll i = a; i < b; ++i)
#define RFOR(i, b, a) for (ll i = b; i >= a; --i)
#define DEBUG(x) cout << ">> " << #x << " : " << x << endl;
#define endl "\n"
#define F first
#define S second
#define pb(x) push_back(x)
#define ALL(x) x.begin(), x.end()
#define mp(x, y) make_pair(x, y)

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef long double ld;
typedef vector<long long> vll;
typedef vector<int> vi;
typedef pair<ll, ll> pll;
typedef vector<pair<ll, ll>> vpll;
typedef unordered_map<ll, ll> STll;

vector<ll> *adj;
bool *marked;
vll init, goal;
ll ans = 0;
vll ansVec;
void dfs(ll v, ll even, ll odd, ll level)
{
    ll cur;
    if (level % 2 == 0)
        cur = (init[v] + even) % 2;
    else cur = (init[v] + odd) % 2;

    if (goal[v] != cur)
    {
        ans++;
        ansVec.pb(v + 1);
        cur = goal[v];
        if (level % 2 == 0)
            even++;
        else
            odd++;
    }

    marked[v] = true;
    for (auto& w : adj[v])
    {
        if (!marked[w])
        {
            dfs(w, even, odd, level + 1);
        }
    }
}

int main()
{
    //freopen("input.txt", "r", stdin);
    SPEED
    ll n;
    cin >> n;
    adj = new vll[n];
    marked = new bool[n];
    FOR(i, 0, n)
    {
        marked[i] = false;
        // damn this garbage value;
    }
    init = vll(n);
    goal = vll(n);
    FOR(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    FOR(i, 0, n)
    {
        cin >> init[i];
    }
    FOR(i, 0, n)
    {
        cin >> goal[i];
    }
    dfs(0, 0, 0, 0);
    cout << ans << endl;
    for (auto e : ansVec)
    {
        cout << e << endl;
    }
}

