/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution
{
public:
    Node* cloneGraph(Node* node)
    {
        // 这道题显然用 DFS 的方式来解决更好理解
        // 我们定义这样的函数：
        // dfs(node)，代表把 node 进行深拷贝这一操作
        // 那么我们可以这样进行递推：
        // 在 dfs(node) 之前，我们需要对它所有的 neighbor 进行 dfs
        // 而如果 node 所有的 neighbor 都已经 dfs 完成，那么我们就可以对 node 本身进行构造并返回了
        // memo 用于记录所有已经构造完成的结点
        if(!node)
        {
            return nullptr;
        }
        unordered_map<Node*, Node*> memo;
        function<Node*(Node*)> dfs = [&](Node* node) -> Node*
        {
            // 标记 node 为已经构造出来了，但是 neighbor 还未填充完毕（其实是否填充完毕，都是放到 memo 中的
            // 重点在于 node 对应的新结点已经被构造出来了
            if(memo.find(node) != memo.end())
            {
                return memo[node];
            }
            Node* newNode = new Node(node->val);
            memo[node] = newNode;
            for(auto& nextNode: node->neighbors)
            {
                dfs(nextNode);
            }
            for(auto& oldNode: node->neighbors)
            {
                newNode->neighbors.push_back(memo[oldNode]);
            }
            return newNode;
        };
        return dfs(node);
    }
};