#include <bits/stdc++.h>
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

typedef long long ll;
typedef long double ld;
typedef vector<long long> vll;
typedef vector<int> vi;
typedef pair<ll, ll> pll;
typedef vector<pair<ll, ll>> vpll;
typedef unordered_map<ll, ll> STll;

int main()
{
  // freopen("input.txt", "r", stdin);
    SPEED
    ll n, m;
    cin >> n;
    vll a(n);
    FOR(i,0 , n)
    {
        cin >> a[i];
    }
    cin >> m;
    vll b(m);
    FOR(i, 0, m)
    {
        cin >> b[i];
    }
    ll x = 0, y = 0;
    ll ans = 0;
    while (x < n && y < m)
    {
        while (a[x] != b[y])
        {
            if (a[x] < b[y])
            {
                if (x == n - 1) break;
                a[x + 1] += a[x];
                x++;
            }
            else if (a[x] > b[y])
            {
                if (y == m - 1) break;
                b[y + 1] += b[y];
                y++;
            }
        }
        if (a[x] == b[y])
        {
             ans++;
            x++;y++;
        }
        else {
            cout << -1;
            return 0;
        }
    }
    if (ans != 0 && x > n - 1 && y > m - 1)
        cout << ans;
    else cout << -1;
}

