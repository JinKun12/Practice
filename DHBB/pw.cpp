/// Created by Zylenox
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define Task "task"
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define bit(i, x) ((x >> i) & 1)
#define sz(x) (int)(x).size()
#define ntest int t; cin >> t; while (t--) solve()
#define __lcm(a, b) (1ll * ((a) / __gcd((a), (b))) * (b))
#define yes cout << "yes\n"
#define no cout << "no\n"
#define int ll
// x << y : x * (2 ^ y)
// x >> y : x / (2 ^ y)
// __builtin_clz(n)) : count the number of first zeros
// __builtin_ctz(n)) : count the number of final zeros
// __builtin_popcount(n) : count the number of digits 1
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vii;
// Hashing
#define NMOD 4
const int BASE = 311;
const int MOD[] = {(int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277};
#define MAX 200010
int pw[NMOD][MAX];
struct Hash {
    int len, value[NMOD];
    Hash() {
        len = 0;
        memset(value, 0, sizeof value);
    }
    Hash(char c) {
        len = 1;
        for (int i = 0; i < NMOD; i++)
            value[i] = c;
    }
    Hash operator + (const Hash &h) const {
        Hash res;
        res.len = len + h.len;
        for (int i = 0; i < NMOD; i++)
            res.value[i] = (value[i] * pw[i][h.len] + h.value[i]) % MOD[i];
        return res;
    }
    bool operator == (const Hash &h) const {
        if (len != h.len) return false;
        for (int i = 0; i < NMOD; i++) if (value[i] != h.value[i])
            return false;
        return true;
    }
};
int k, m, n;
char s[MAX], revS[MAX];
Hash hs[MAX], revHS[MAX];
pair<Hash, Hash> hashSegment[MAX];
void calcHash(char s[], Hash hs[]) {
    for (int i = 1; i <= n; i++)
        hs[i] = hs[i - 1] + Hash(s[i]);
}
Hash getHash(Hash hs[], int l, int r) {
    Hash res;
    res.len = r - l + 1;
    for (int i = 0; i < NMOD; i++) {
        res.value[i] = (hs[r].value[i] - hs[l - 1].value[i] * pw[i][r - l + 1]) % MOD[i];
        if (res.value[i] < 0) res.value[i] += MOD[i];
    }
    return res;
}
main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    //freopen(Task".inp", "r", stdin);
    cin >> k >> m >> (s + 1); // Read the string starting from index 1
    n = strlen(s + 1); // Calculate length from index 1
    for (int j = 0; j < NMOD; j++) {
        pw[j][0] = 1;
        for (int i = 1; i <= n; i++)
            pw[j][i] = pw[j][i - 1] * BASE % MOD[j];
    }
    for (int i = 1; i <= n; i++) revS[i] = s[i];
    reverse(revS + 1, revS + n + 1);
    calcHash(s, hs);
    calcHash(revS, revHS);
    for (int i = 1, l, r; i < k; i++) {
        cin >> l >> r;
        hashSegment[i].fi = getHash(hs, l, r);
        hashSegment[i].se = getHash(revHS, n - r + 1, n - l + 1);
    }
    auto check = [&](int pos) {
        int l = pos, r = pos + m - 1;
        hashSegment[k].fi = getHash(hs, l, r);
        hashSegment[k].se = getHash(revHS, n - r + 1, n - l + 1);
        vi perm(k);
        iota(all(perm), 1);
        do {
            pair<Hash, Hash> all = hashSegment[perm[0]];
            for (int i = 1; i < k; i++) {
                all.fi = all.fi + hashSegment[perm[i]].fi;
                all.se = hashSegment[perm[i]].se + all.se;
            }
            if (all.fi == all.se) return true;
        } while (next_permutation(all(perm)));
        return false;
    };
    int ans = 0;
    for (int i = 1; i <= n - m + 1; i++) if (check(i))
        ans++;
    cout << ans;
    return 0;
}
// I wish I was a cat, no school, no work, just meow meow.
