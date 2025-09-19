class Solution
{
public:
    int climbStairs(int n)
    {
        // 基础题，秒了
        vector<int> dp(n+1, 0);
        dp[0] = 1; dp[1] = 1;
        for(int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i-2]+dp[i-1];
        }
        return dp[n];
    }
};

/*
    n -> 2n -> 3n -> 4n
    n -> 2n -> 2n -> 4n
*/

/*
    k - k -> 2k
    2k - k -> 3k

*/