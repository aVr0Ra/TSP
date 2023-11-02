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

inline int read() {
    int x = 0 , f = 1; char ch = getchar();
    for ( ; !isdigit(ch) ; ch = getchar()) if (ch == '-') f = -1;
    for ( ; isdigit(ch) ; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

const int maxn = 20;

int dis[maxn][maxn];

int dp[maxn][(1 << maxn)] , pre[maxn][(1 << maxn)];

int n;

stack <int> S;

int main() {
    memset(dp , 0x3f , sizeof(dp));

    n = read();
    for (int i =  0 ; i < n ; i ++) {
        for (int j = 0 ; j < n ; j ++) {
            dis[i][j] = read();
        }
    }

    dp[0][1] = 0;

    for (int i = 1 ; i < (1 << n) ; i ++) {
        for (int j = 1 ; j < n ; j ++) {
            if (i & (1 << j) || !(1 & i)) {
                continue;
            }

            for (int k = 0 ; k < n ; k ++) {
                if (i & (1 << k)) {
                    if (dp[j][(1 << j) | i] > dis[k][j] + dp[k][i]) {
                        dp[j][(1 << j) | i] = dis[k][j] + dp[k][i];
                        pre[j][(1 << j) | i] = k;
                    }
                }
            }
        }
    }
    /*
     for (int i = 0 ; i < n ; i ++) {
        for (int j = 0 ; j <= (1 << n) - 1 ; j ++) {
            if (dp[i][j] != 1061109567) {
                cout << dp[i][j] << " ";
            }
            else cout << "inf ";
        }cout << endl;
    }cout << endl << endl;

    for (int i = 0 ; i < n ; i ++) {
        for (int j = 0 ; j <= (1 << n) - 1 ; j ++) {
            cout << pre[i][j] << " ";
        }cout << endl;
    }cout << endl;
    */

    int ans = 2147483647;
    int path = -1;

    for (int i = 0 ; i < n ; i ++) {
        if (ans > dis[i][0] + dp[i][(1 << n) - 1]) {
            ans = dis[i][0] + dp[i][(1 << n) - 1];
            path = i;
        }
    }
    
    S.push(0); S.push(path);

    int nowcon = (1 << n) - 1 - (1 << path);
    path = pre[path][(1 << n) - 1];

    while (path) {
        int now = path;
        S.push(path);
        path = pre[path][nowcon];
        nowcon -= (1 << now);
    }

    S.push(0);

    while (S.size()) printf("%d " , S.top() + 1) , S.pop();

    printf("\n%d\n" , ans);
}