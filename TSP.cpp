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

const ll maxn = 15;

ll dis[maxn][maxn];

ll dp[maxn][(1 << maxn)] , pre[maxn][(1 << maxn)][5];

ll n;

ll ansseq[maxn];

ll seq[maxn];

void dfs(ll now , ll con , ll id) {
    if (!now) {
        bool anstag = false;
        for (ll i = 1 ; i <= n ; i ++) {
            if (seq[i] < ansseq[i]) {
                anstag = true;
                break;
            }
        }

        if (anstag) {
            for (ll i = 1 ; i <= n ; i ++) {
                ansseq[i] = seq[i];
            }
        }

        return ;
    }

    //printf("now = %lld ; con = %lld\n" , now , con);

    for (ll i = 1 ; i <= pre[now][con][0] ; i ++) {
        ll nowcon = con - (1 << now);

        seq[id] = now;
        dfs(pre[now][con][i] , nowcon , id - 1);
        seq[id] = 0;
    }
}

int main() {
    //freopen("input.in" , "r" , stdin);
    //freopen("dp.out" , "w" , stdout);

    memset(dp , 0x3f , sizeof(dp));
    memset(pre , 0x3f , sizeof(pre));
    memset(ansseq , 0x3f , sizeof(ansseq));

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
                        pre[j][(1 << j) | i][0] = 0;
                        pre[j][(1 << j) | i][++ pre[j][(1 << j) | i][0]] = k;
                    }
                    else if (dp[j][(1 << j) | i] == dis[k][j] + dp[k][i]) {
                        pre[j][(1 << j) | i][++ pre[j][(1 << j) | i][0]] = k;
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

    
    for (ll i = 0 ; i < n ; i ++) {
        if (ans == dis[i][0] + dp[i][(1 << n) - 1]) {
            ll nowcon = (1 << n) - 1;
            seq[n] = 0;
            dfs(path , nowcon ,  n - 1);
        }
    }

    putchar('1');
    for (ll i = 1 ; i <= n ; i ++) {
        printf(" %lld" , ansseq[i] + 1);
    }
    printf("\n%lld\n" , ans);
}