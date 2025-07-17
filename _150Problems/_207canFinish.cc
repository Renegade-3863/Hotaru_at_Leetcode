class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        // 这道题抽象出模型，就是要我们找 prerequisites 形成的图中是否有环
        // 而找环的方法无非拓扑排序
        // 我们先用 BFS 的方法来写
        // 具体流程为：
        // 用一个队列存储有向图中所有的入度为 0 的结点
        // 之后每次从队列中取出一个结点，对它所有连接到的其它节点的入度减 1
        // 之后如果有新的入度为 0 的结点，那么就继续入队
        // 直到队列中没有任何入度为 0 的结点为止
        // 最后，如果我们的排序已经覆盖了所有的结点，那么我们就找到了一个合法的完全拓扑排序
        // 也就是说，我们有一种可以完成所有课程学习的方法
        queue<int> q;
        // seq 用于记录所有我们拓扑排序遍历过的课程序号
        // 如果最后 (int)seq.size() == numCourses，那么我们就可以返回 true；否则我们返回 false 
        vector<int> seq;
        // 先要建图
        unordered_map<int, unordered_set<int>> mapping;
        // 哈希表记录所有结点的入度，不存在的结点默认入度为 0
        unordered_map<int, int> indegree;
        for(const auto& prerequisite: prerequisites)
        {
            // 对于每一个 prerequisite，我们记录一个 prerequisite[1] -> prerequisite[0] 的映射关系
            if(mapping.find(prerequisite[1]) == mapping.end())
            {
                mapping[prerequisite[1]] = unordered_set<int>();
            }
            // 进行映射
            mapping[prerequisite[1]].insert(prerequisite[0]);
            // 把 indegree 中对应结点的入度 + 1
            ++indegree[prerequisite[0]];
        }
        // 映射完成，之后我们执行拓扑排序即可
        // 先检查所有入度为 0 的结点，并加入到队列 q 中
        for(int i = 0; i < numCourses; ++i)
        {
            if(indegree.find(i) == indegree.end() || indegree[i] == 0)
            {
                q.push(i);
            }
        }
        // 当队列 q 非空的时候，我们持续执行下面的循环
        while(!q.empty())
        {
            int n = q.size();
            for(int i = 0; i < n; ++i)
            {
                int course = q.front();
                // 把 course 所有相连的后续结点的入度减 1
                for(const auto& sub: mapping[course])
                {
                    if(--indegree[sub] == 0)
                    {
                        q.push(sub);
                    }
                }
                // 把 course 记录到 seq 中
                seq.push_back(course);
                // 弹出结点
                q.pop();
            }
        }
        return (int)seq.size() == numCourses;
    }
};