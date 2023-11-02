#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

typedef long long ll;

inline ll read() {
    ll x = 0 , f = 1; char ch = getchar();
    for ( ; !isdigit(ch) ; ch = getchar()) if (ch == '-') f = -1;
    for ( ; isdigit(ch) ; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

const ll maxn = 20;

ll dis[maxn][maxn];

ll dp[maxn][(1 << maxn)] , pre[maxn][(1 << maxn)];

ll n;

stack <ll> S;

int main() {
    memset(dp , 0x3f , sizeof(dp));

    n = read();
    for (ll i =  0 ; i < n ; i ++) {
        for (ll j = 0 ; j < n ; j ++) {
            dis[i][j] = read();
        }
    }

    dp[0][1] = 0;

    for (ll i = 1 ; i < (1 << n) ; i ++) {
        for (ll j = 1 ; j < n ; j ++) {
            if (i & (1 << j) || !(1 & i)) {
                continue;
            }

            for (ll k = 0 ; k < n ; k ++) {
                if (i & (1 << k)) {
                    if (dp[j][(1 << j) | i] > dis[k][j] + dp[k][i]) {
                        dp[j][(1 << j) | i] = dis[k][j] + dp[k][i];
                        pre[j][(1 << j) | i] = k;
                    }
                }
            }
        }
    }

    ll ans = 2147483647;
    ll path = -1;

    for (ll i = 0 ; i < n ; i ++) {
        if (ans > dis[i][0] + dp[i][(1 << n) - 1]) {
            ans = dis[i][0] + dp[i][(1 << n) - 1];
            path = i;
        }
    }
    
    S.push(0); S.push(path);

    ll nowcon = (1 << n) - 1 - (1 << path);
    path = pre[path][(1 << n) - 1];

    while (path) {
        ll now = path;
        S.push(path);
        path = pre[path][nowcon];
        nowcon -= (1 << now);
    }

    putchar('1');

    while (S.size()) printf(" %lld" , S.top() + 1) , S.pop();

    printf("\n%lld\n" , ans);
}