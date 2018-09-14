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

int main()
{
   // freopen("input.txt", "r", stdin);
    SPEED
    ll n;
    cin >> n;
    vll a(n), sum(n, 0); ll grandTot = 0;
    FOR(i, 0, n)
    {
        cin >> a[i];
        grandTot += a[i];
    }
    if (grandTot % 3 != 0)
    {
        cout << 0;
        return 0;
    }
    ll tot = 0;
    RFOR(i, n - 1, 2)
    {
        tot += a[i];
        if (tot == grandTot / 3)
        {
            sum[i]++;
        }
        sum[i - 1] += sum[i];
        //cout << sum[i];
    }
    ll ss = a[0], ans= 0;
    FOR(i, 1, n - 1)
    {
        if (ss == grandTot / 3)
        {
            ans += sum[i + 1];
        }
        ss += a[i];
       // DEBUG()
    }
    cout << ans;
}

