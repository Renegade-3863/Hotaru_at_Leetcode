#include "Solution.h"

Leetcode101_200::Solution::Node* Leetcode101_200::Solution::cloneGraph(Leetcode101_200::Solution::Node* node)
{
    // 简单的图的 DFS 即可完成图的深拷贝操作
    // 定义一个 DFS 函数
    // 用于复制原 node 对应结点中的所有相关信息到这个 node 中
    // 用一个哈希表记录所有访问过的结点
    unordered_set<Node*> visited;
    unordered_map<Node*, Node*> mapping;
    // original 记录的是原图上和 node 同位置的结点
    function<void(Node*, Node*)> dfs = [&](Node* node, Node* original)
    {
        // 外层遍历这个结点的所有邻接结点
        for(const auto& neighbor: original->neighbors)
        {
            // 如果这个邻接结点之前没有访问过，那么把它标记为已访问，并深入进行访问
            // 注意要先新建一个对应邻接结点的拷贝，再把原来对应结点的信息复制到这个新结点
            // 之后再进行访问
            if(visited.find(neighbor) == visited.end())
            {
                // 新建邻接结点的拷贝
                Node* newNode = new Node(neighbor->val);
                mapping[neighbor] = newNode; 
                // 记录到新结点的邻接列表中
                node->neighbors.push_back(newNode);
                // 对这个邻居进行访问
                visited.insert(neighbor);
                dfs(newNode, neighbor);
            }
            // 否则，遍历到的是一个已经复制过的结点，此时我们只需要记录这个新结点到这个邻接结点的关系即可，不需要做其他处理
            else
            {
                // 新结点的邻接链表中也要反向添加这个路径上的父结点
                node->neighbors.push_back(mapping[neighbor]);
            }
        }
        // 深入检查完本结点的所有邻居之后，由于给定原图是连通的，因此我们可以通过对这一个结点的一次深搜复制完成整张图
        // 就可以直接退出函数了
    };
    // 新建复制图中 node 的同位置新结点，然后调用上面的 DFS 函数即可
    if(!node)
    {
        return nullptr;
    }
    Node* res = new Node(node->val);
    visited.insert(node);
    mapping[node] = res;
    dfs(res, node);
    return res;
}

// 参照答案的思路对冗余的哈希表信息进行了一些优化：
Leetcode101_200::Solution::Node* cloneGraph(Leetcode101_200::Solution::Node* node)
{
    // 简单的图的 DFS 即可完成图的深拷贝操作
    // 定义一个 DFS 函数
    // 用于复制原 node 对应结点中的所有相关信息到这个 node 中
    // 这里实际上只需要记录一个旧结点到新结点之间的映射关系
    unordered_map<Node*, Node*> mapping;
    // original 记录的是原图上的结点
    // 这里只需要记录一个 original 就可以了，至于新结点信息可以通过上面的 mapping 哈希表来获取
    function<void(Node*)> dfs = [&](Node* original)
    {
        // 外层遍历这个结点的所有邻接结点
        for(const auto& neighbor: original->neighbors)
        {
            // 如果这个邻接结点之前没有访问过，那么把它标记为已访问，并深入进行访问
            // 注意要先新建一个对应邻接结点的拷贝，再把原来对应结点的信息复制到这个新结点
            // 之后再进行访问
            if(mapping.find(neighbor) == mapping.end())
            {
                // 新建邻接结点的拷贝
                Node* newNode = new Node(neighbor->val);
                mapping[neighbor] = newNode; 
                // 记录到新结点的邻接列表中
                mapping[original]->neighbors.push_back(newNode);
                // 对这个邻居进行访问
                dfs(neighbor);
            }
            // 否则，遍历到的是一个已经复制过的结点，此时我们只需要记录这个新结点到这个邻接结点的关系即可，不需要做其他处理
            else
            {
                // 新结点的邻接链表中也要反向添加这个路径上的父结点
                mapping[original]->neighbors.push_back(mapping[neighbor]);
            }
        }
        // 深入检查完本结点的所有邻居之后，由于给定原图是连通的，因此我们可以通过对这一个结点的一次深搜复制完成整张图
        // 就可以直接退出函数了
    };
    // 新建复制图中 node 的同位置新结点，然后调用上面的 DFS 函数即可
    if(!node)
    {
        return nullptr;
    }
    Node* res = new Node(node->val);
    mapping[node] = res;
    dfs(node);
    return res;
}
