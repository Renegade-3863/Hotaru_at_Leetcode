class Solution
{
public:
    string longestPalindrome(string s)
    {
        // 经典 DP 类问题
        // 可以用二维 DP 来解决
        int n = s.size();
        // dp[i][j] 代表 s[i..j] 是否为回文串
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        // 递推关系为：
        // s[i] == s[j]，那么 dp[i][j] = dp[i+1][j-1]
        // 否则，dp[i][j] = false
        // 我们可以按子串长度来遍历
        // 默认结果为第一个字符构成的字符串
        string res = s.substr(0, 1);
        // 初始状态
        for(int i = 0; i < n; ++i)
        {
            dp[i][i] = true;
        }
        // 初始化长度为 2 的子串
        for(int i = 0; i < n-1; ++i)
        {
            dp[i][i+1] = (s[i] == s[i+1]);
            if(dp[i][i+1])
            {
                res = s.substr(i, 2);
            }
        }
        // 正常的递推
        for(int l = 3; l <= n; ++l)
        {
            for(int i = 0; i < n-l+1; ++i)
            {
                // 计算出子串结尾下标
                int j = i+l-1;
                // 判断 s[i] 是否等于 s[j]
                if(s[i] == s[j])
                {
                    dp[i][j] = dp[i+1][j-1];
                    // 尝试更新结果
                    if(dp[i][j] && res.size() < l)
                    {
                        res = s.substr(i, l);
                    }
                }
                // 否则 s[i] != s[j] 我们就不能进行更新了
            }
        }
        return res;
    }
};