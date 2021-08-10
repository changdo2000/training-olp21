#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+5;

int n, m;
double ans[201][10001], cost[201][201];

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    cin >> n >> m;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)
            cin >> cost[i][j];
    for (int i=1; i<=n; i++)
        ans[i][1] = cost[1][i];
    for (int step = 2; step <=m; step++)
        for (int cur_post = 1; cur_post <=n; cur_post++)
            for (int pass_post = 1; pass_post <= n; pass_post++)
                ans[cur_post][step] += ans[pass_post][step-1] * cost[pass_post][cur_post];
    for (int post=1; post<=n; post++)
        cout << fixed << setprecision(4) <<ans[post][m] << '\n';
}

