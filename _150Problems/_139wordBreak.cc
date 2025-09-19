class Solution
{
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        // DP 类问题，只有一个单词 s 需要用来查，所以不用字典树这么麻烦
        // 我们规定一个这样的 DP 子问题：
        // dp[i][j] 代表用 wordDict 中的前 i 种单词，拼凑出 s.substr(0, j) 是否可能
        int n = s.size(), m = wordDict.size();
        // 处理边界条件
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        // 边界情况为：
        dp[0][0] = true;
        // 1. 不使用任何单词，那么对于所有 j 值大于等于 1，结果都应该为 false
        // 不用处理
        // 2. 要拼凑的字符串长度为 0，那么我们也可以拼出来，全部设定为 true
        for(int i = 1; i <= m; ++i)
        {
            dp[i][0] = true;
        }
        // 之后是正常的递推流程
        for(int i = 1; i <= m; ++i)
        {
            int len = wordDict[i-1].size();
            for(int j = 1; j <= n; ++j)
            {
                dp[i][j] = dp[i-1][j];
                for(int k = 0; k < i; ++k)
                {
                    int len = wordDict[k].size();
                    // 使用一次第 k 个单词进行拼接（但是需要确保最后这些字符足够，且能够匹配
                    // abcd 
                    if(j >= len && s.substr(j-len, len) == wordDict[k])
                    {
                        // 可以切出一块，我们切出去试试看
                        dp[i][j] = dp[i][j] | dp[i][j-len];
                    }                    
                }

            }
        }
        return dp[m][n];
    }
};