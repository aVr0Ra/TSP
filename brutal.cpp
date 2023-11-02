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

const ll maxn = 25;

ll n;
ll a[maxn][maxn];

bool vis[maxn];

ll ans = 1e9 + 7;
ll ord[maxn];

void dfs(ll now , ll noword[] , ll cnt , ll depth) {
    if (depth == n) {
        noword[depth] = now;

        if (cnt + a[now][1] < ans) {
            ans = cnt + a[now][1];
            for (ll i = 1 ; i <= n ; i ++) {
                ord[i] = noword[i];
                //cout << ord[i] << " ";
            }
            //printf("\nans = %d\n" , ans);
        }

        return ;
    }


    vis[now] = true;
    noword[depth] = now;

    for (ll i = 1 ; i <= n ; i ++) {
        if (!vis[i]) {
            dfs(i , noword , cnt + a[now][i] , depth + 1);
        }
    }

    vis[now] = false;

    return ;
}

int main() {
    freopen("input.in" , "r" , stdin);
    freopen("brutal.out" , "w" , stdout);
    n = read();
    for (ll i = 1 ; i <= n ; i ++) {
        for (ll j = 1 ; j <= n ; j ++) {
            a[i][j] = read();
        }
    }

    ll noword[maxn];
    memset(noword , 0 , sizeof(noword));

    dfs(1 , noword , 0 , 1);

    for (ll i = 1 ; i <= n ; i ++) {
        cout << ord[i] << " ";
    }cout << 1 << endl;
    cout << ans << endl;
}