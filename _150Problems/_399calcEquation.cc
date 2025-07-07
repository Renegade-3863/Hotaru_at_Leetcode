class Solution
{
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries)
    {
        // 经典图论问题
        // 我们需要建图，然后查图求解
        // 简单来说，我们可以用一个哈希表来记录：
        // string -> {string, double}，也就是 '被除数' -> {除数， 商} 的集合 的映射关系
        unordered_map<string, unordered_map<string, double>> mapping;
        int n = equations.size();
        for(int i = 0; i < n; ++i)
        {
            if(mapping.find(equations[i][0]) == mapping.end())
            {
                mapping[equations[i][0]] = unordered_map<string, double>();
            }
            mapping[equations[i][0]][equations[i][1]] = values[i];
            mapping[equations[i][1]][equations[i][0]] = 1/values[i];
        }
        vector<double> res;
        // helper function，用于计算 a/b 的结果，使用 dfs 来进行处理
        // 用 memo 记录递归过程中已经检查过的字符
        function<double(string, string, unordered_set<string>&)> dfs = [&](string a, string b, unordered_set<string>& memo) -> double
        {
            // 简单来说，我们可以查找 mapping[a] 对应的列表，如果有 b 对应的项，那就直接返回结果，否则，我们就递归地检查 mapping[a] 中的每一个字符 c
            // 看哪一个 dfs(c, b) 有合法解
            // 而题目告诉我们不存在同一个式子等于两个值的情况，所以我们只要找到了一个非 -1 的解，我们就可以直接结束递归循环了
            // 而如果找遍了整个 mapping[a]，那么我们就可以认为 a/b 没有解，返回 -1 即可
            // 压根就没记录过 a，那么我们直接返回 -1 即可
            if(mapping.find(a) == mapping.end() || mapping.find(b) == mapping.end())
            {
                return -1.0;
            }
            // if(tmp.find(a) != tmp.end() && tmp[a].find(b) != tmp[a].end())
            // {
            //     return tmp[a][b];
            // }
            // if(tmp.find(b) != tmp.end() && tmp[b].find(a) != tmp[b].end())
            // {
            //     return 1/tmp[b][a];
            // }
            if(a == b)
            {
                return 1.0;
            }
            if(mapping[a].find(b) != mapping[a].end())
            {
                // 有记录好的结果，那么我们直接返回即可，也没什么要增量记录的
                return mapping[a][b];
            }
            if(mapping[b].find(a) != mapping[b].end())
            {
                return 1/mapping[b][a];
            }
            // 否则，没有记录好的结果，我们需要 dfs 遍历 mapping[a] 整个列表，检查 dfs(c, b)
            for(const auto& p: mapping[a])
            {
                // p 是 {string, double} 对
                // 检查每一个 c
                // 只要找到一个合法的解，我们就可以结束 dfs 了
                string c = p.first;
                if(memo.find(c) != memo.end())
                {
                    continue;
                }
                // 路径中进行记录，并深入递归
                memo.insert(c);
                double ret = dfs(c, b, memo);
                memo.erase(c);
                if(ret != -1)
                {
                    mapping[a][b] = mapping[a][c]*ret;
                    mapping[b][a] = 1/mapping[a][b];
                    return mapping[a][b];
                }
            }
            // 遍历完了，也没找到合法解，那么直接返回 -1.0 即可
            return -1.0;
        };
        // 处理完毕后，我们用这个 mapping 来进行图的遍历
        unordered_set<string> memo;
        for(auto& query: queries)
        {
            // 对每一条查询进行处理
            res.push_back(dfs(query[0], query[1], memo));           
        }
        return res;
    }
};

