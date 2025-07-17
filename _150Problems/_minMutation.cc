class Solution
{
public:
    int minMutation(string startGene, string endGene, vector<string>& bank)
    {
        // 经典的 BFS 类问题
        // 我们可以存储一些 bank 内部字符串之间的 '一步转换' 关系映射
        // 之后再根据持有的转换关系图进行 BFS 遍历
        // 不过正向处理 bank 中的每一个字符串，复杂度可能会很高
        // 我们需要仔细思考一下如何实现
        // 可以这样做：
        // 我们保存一组哈希结构：
        // {模板, {对应的原基因值列表}}
        // 其中 "模板" 代表的是某一个字符被替换成 "通用字符" 的字符串
        unordered_map<string, unordered_set<string>> mapping;
        for(const auto& dna: bank)
        {
            // 对于 bank 中的每一个 dna 字符串，把每一个位置上的字符修改成特殊字符 '*'（这不可能出现在任何实际的 DNA 序列中
            // 并保存对应的 dna 到模板 key 对应的列表中
            int n = dna.size();
            string tmp = dna;
            for(int i = 0; i < n; ++i)
            {
                char memo = tmp[i];
                tmp[i] = '*';
                mapping[tmp].insert(dna);
                tmp[i] = memo;
            }
        }
        // 之后从 startGene 开始处理
        // 注意，为了防止 BFS 特有的重复添加路径结点的问题，我们需要一个表来记录已经遍历过的结点
        unordered_set<string> s_memory;
        queue<string> q;
        q.push(startGene);
        int steps = 0;
        while(!q.empty())
        {
            int n = q.size();
            for(int i = 0; i < n; ++i)
            {
                // 从 q 中取出一个路径结点，尝试进行扩散
                string node = q.front();
                // 注意：如果 node 本身就是 endGene，那么我们就可以直接返回步骤数了
                if(node == endGene)
                {
                    return steps;
                }
                int m = node.size();
                for(int j = 0; j < m; ++j)
                {
                    // 尝试把 node[j] 修改为 '*'，之后检查 mapping 中是否存在对应的模板结点
                    // 如果存在，并且之前没有遍历过，那么我们就把这个路径结点对应的所有可行的下一步实际结点添加到 q 中，以备下一步使用
                    char tmp = node[j];
                    node[j] = '*';
                    if(mapping.find(node) != mapping.end() && s_memory.find(node) == s_memory.end())
                    {
                        // 记录当前结点
                        s_memory.insert(node);
                        // 添加所有可能的下一跳结点
                        for(const auto& nextNode: mapping[node])
                        {
                            // 注意，如果对应的实际结点也遍历过了，我们也不重复添加
                            if(s_memory.find(nextNode) != s_memory.end())
                            {
                                continue;
                            }
                            s_memory.insert(nextNode);
                            q.push(nextNode);
                        }
                    }
                    node[j] = tmp;
                }
                // 弹出队头结点
                q.pop();
            }
            // 一步走完，steps 增加 1
            ++steps;
        }
        // 无法到达指定的 endGene，返回 -1 即可
        return -1;
    }
};