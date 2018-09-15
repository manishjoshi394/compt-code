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

bool isPrime[int(10e6 + 13)];

void sieve()
{
    for (ll i = 2; i * i <= int(10e6); ++i)
    {
        if (isPrime[i])
        for (ll j = 2 * i; j <= int(10e6); j += i)
        {
            isPrime[j] = false;
        }
    }
}


int main()
{
    //freopen("input.txt", "r", stdin);
    SPEED
    memset(isPrime, true, sizeof(isPrime));
    sieve();

    ll n;
    cin >> n;

    vll a(n);
    FOR(i, 0, n)
    {
        cin >> a[i];
        if (a[i] == 1)
            cout << "NO" << endl;
        else  if (ceil(sqrt(a[i])) == floor(sqrt(a[i])) && isPrime[(int)sqrt(a[i])])
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}

