#include <bits/stdc++.h>
#define SPEED ios_base::sync_with_stdio(false); cin.tie(NULL);
#define FOR(i, a, b) for (ll i = a; i < b; ++i)
#define RFOR(i, b, a) for (ll i = b; i >= a; --i)
#define DEBUG(x) cout << ">> " << #x << " : " << x << endl;
#define pb(x) push_back(x)
#define ALL(x) x.begin(), x.end()
#define mp(x, y) make_pair(x, y)
#define F first
#define S second

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<long long> vll;
typedef vector<int> vi;
typedef vector<pair<ll, ll>> vpll;
typedef unordered_map<ll, ll> STll;

int main()
{
   // freopen("input.txt", "r", stdin);
    SPEED

    ll n, h;
    cin >> n >> h;
    vpll a(n);          // vector of pairs
    vll down(n);
    FOR(i, 0, n)
    {
        cin >> a[i].F >> a[i].S;    // F is first, S means second
    }
    down[0] = 0;
    FOR(i, 1, n)
    {
        down[i] = down[i - 1] + a[i].F - a[i - 1].S;
    }
    ll ans = INT_MIN;
    ll val = -1;

    ll l = 0, r = 0;
    while (l < n)
    {
        while (r < n && (down[r] - down[l]) < h)
        {
            r++;
        }
        val = h - (down[r - 1] - down[l]);
        ans = max(ans, a[r - 1].S - a[l].F + val);
        l++;
    }

    cout << ans;
}
