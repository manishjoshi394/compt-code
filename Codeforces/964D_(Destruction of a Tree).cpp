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

int main()
{
    //freopen("input.txt", "r", stdin);
    SPEED
    ll n;
    cin >> n;
    if (!(n & 1))
    {
        cout << "NO";
        return 0;
    }

    vll* adj;
    bool* marked;
    vll sz;

    sz = vll(n);
    marked = new bool[n];
    adj = new vll[n];
    FOR(i, 0, n)
    {
        marked[i] = false;
    }
    FOR(i, 0, n)
    {
        ll j;
        cin >> j;
        if (j == 0) continue;
        j--;
        adj[i].pb(j);
        adj[j].pb(i);
    }

    function<void(ll)> dfs = [&](ll v)-> void {
        marked[v] = true;
        for(ll w : adj[v])
        {
            if (!marked[w] && !(sz[w] & 1))
            {
                dfs(w);
            }
        }
        cout << v + 1   << endl;
        for (ll w : adj[v])
        {
            if (!marked[w] && (sz[w] & 1))
            {
                dfs(w);
            }
        }
    };

    function<void(ll, ll)> setSZ = [&](ll v, ll prev)
    {
        sz[v] = 1;
        for (ll w : adj[v])
        {
            if (prev != w)
            {
                setSZ(w, v);
                sz[v] += sz[w];
            }
        }
    };

    setSZ(0, 0);
    cout << "YES" << endl;
    dfs(0);
}

