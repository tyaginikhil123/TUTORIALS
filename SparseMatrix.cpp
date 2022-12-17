#include <bits/stdc++.h>
using namespace std;

int main()
{
    int arr[] = {11, 2, 101, 13, 21, 20, 41, 5, 4, 12, 34, 2, 3, 45, 67, 54, 12, 34, 23, 34, 53, 45, 12, 32};
    int n = 24;
    int c = ceil(log2(n));

    // 2*n= index size=ceil(log(2n))
    vector<vector<int>> dp(2 * n, vector<int>(c, INT_MAX));
    for (int j = 0; j < c; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (j == 0)
            {
                // i index aur j(size=1) ho to arr[i] khud hi value hogi
                dp[i][j] = arr[i];
            }
            else
            {
                // i index aur size j k liye 2 part m ho jaega(i se j-1 aur i+(1<<(j-1)) se j-1 tk) fir dono ka minimum le lenge
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    // printing of spartx matrix
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<c;j++){
    //         cout<<dp[i][j]<<"  ";
    //     }
    //     cout<<"/n";
    // }

    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;

        int x = r - l + 1;
        int ans = INT_MAX;
        int cur = l;

        for (int i = c - 1; i >= 0; i--)
        {
            // checking for bitset
            if (x & (1 << i) != 0)
            {
                ans = min(ans, dp[cur][i]);
                cur += (1 << i);
            }
        }
        cout << "minimum of range " << l << " to " << r << " is " << ans << "\n";
    }
    return 0;
}