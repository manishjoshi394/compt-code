/***    ALLIZWEL - ALL IZZ WELL Solution
**  https://www.spoj.com/problems/ALLIZWEL/ ***/
/****
* Try this case if you get WA:
* 	
*       3
*	
*	3 4
*	AEW.
*	LLIZ
*	LL.Z
*       	
*       3 0
*       0 1
*/

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

const int MAX = 102;

string grid[MAX];
char path[10] = {'A', 'L', 'L', 'I', 'Z', 'Z', 'W', 'E', 'L', 'L'};

bool marked[MAX][MAX];

int dR[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dC[] = {-1, 0, 1, 1, -1, -1, 0, 1};
ll n, m;


bool dfs(int r, int c, int idx)
{
    assert(path[idx] == grid[r][c]);
   //DEBUG(grid[r][c], idx)
    marked[r][c] = true;
    if (idx == 9) {
        return 1;
    }

    bool isSuccessful = false;
    FOR(k, 0, 8)
    {
        int x = r + dR[k];
        int y = c + dC[k];
        if (!(x < n && x >= 0 && y < m && y >= 0))
        {
            continue;
        }
        if (marked[x][y]) continue;

        if (grid[x][y] != path[idx + 1])    continue;

        isSuccessful |= dfs(x, y, idx + 1);
    }
    if (!isSuccessful) marked[r][c] = false;
    return isSuccessful;
}

int main()
{
   // freopen("input.txt", "r", stdin);
    SPEED
    ll t;
    cin >> t;
    FOR(_, 0, t)
    {
        memset(marked, false, sizeof(marked));
        cin >> n >> m;
        if (n == 0 || m == 0)
        {
            cout << "NO" << endl;
            continue;
        }
        FOR(i, 0, n)
        {
            cin >> grid[i];
        }
        bool ok = false;
        FOR(i, 0, n)
        {
            FOR(j, 0, m)
            {
                if (grid[i][j] == 'A')
                {
                    ok = dfs(i, j, 0);
                    if (ok) break;
                }
            }
            if (ok) break;
        }
        if (ok) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
/************************************** END OF PROGRAM ******************************************/

