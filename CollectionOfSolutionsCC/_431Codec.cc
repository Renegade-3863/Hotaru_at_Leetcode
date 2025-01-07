#include "Solution.h"

// BFS 版本来自 Leetcode 官方题解，非本人解法
Leetcode401_500::TreeNode* Leetcode401_500::Solution::encode(Node* root)
{
    // 我们使用 BFS 的方式来对 N 叉树进行二叉化
    if(!root)
    {
        return nullptr;
    }
    TreeNode* newRoot = new TreeNode(root->val);
    queue<pair<TreeNode*, Node*>> q;
    q.emplace(newRoot, root);
    while(!q.empty())
    {
        auto [bNode, nNode] = q.front();
        q.pop();
        TreeNode* prevBNode = nullptr;
        TreeNode* headBNode = nullptr;
        for(auto nChild : nNode->children)
        {
            TreeNode* newBNode = new TreeNode(nChild->val);
            if(!prevBNode)
            {
                headBNode = newBNode;
            }
            else
            {
                prevBNode->right = newBNode;
            }
            prevBNode = newBNode;
            q.emplace(newBNode, nChild);
        }
        bNode->left = headBNode;
    }
    return newRoot;
}

Node* Leetcode401_500::Solution::decode(Leetcode401_500::TreeNode* root)
{
    if(!root)
    {
        return nullptr;
    }
    Node* newRoot = new Node(root->val);
    queue<pair<Node*, TreeNode*>> q;
    q.emplace(newRoot, root);

    while(!q.empty())
    {
        auto [nNode, bNode] = q.front();
        q.pop();
        TreeNode* firstChild = bNode->left;
        TreeNode* sibling = firstChild;
        while(sibling)
        {
            Node* nChild = new Node(sibling->val);
            nNode->children.push_back(nChild);
            q.emplace(nChild, sibling);
            sibling = sibling->right;
        }
    }
    return newRoot;
}

// 尝试使用更好理解的 DFS 写法完成本题
Leetcode401_500::TreeNode* Leetcode401_500::Soltuion::encode(Node* root)
{
    // 对一个 N 叉树进行二叉化的操作，我们可以定义一个基本的递归函数 subEncode
    function<TreeNode*(Node*)> subEncode = [&](Node* subRoot) -> TreeNode*
    {   
        // 基本情况：如果 subRoot 为空，那么我们直接返回空结点即可
        if(!subRoot)
        {
            return nullptr;
        }
        // 否则，我们按逻辑进行处理即可
        // 首先把根结点进行转换
        TreeNode* newNode = new TreeNode(subRoot->val);
        // 之后是对 subRoot 的所有孩子进行转换
        // 如果 subRoot 没有孩子结点，那么直接返回即可
        if(subRoot->children.size() == 0)
        {
            return newNode;
        }
        // subRoot 有孩子结点，那么我们需要对这些孩子结点进行转换
        // 第一个孩子结点放到 newNode 的左孩子上，我们需要先对它进行转换
        TreeNode* nxtNode = encode(subRoot->children[0]);
        newNode->left = nxtNode;
        // 剩下的结点按次序接到 newNode 的左孩子的右孩子链上即可
        for(int i = 1; i < subRoot->children.size(); ++i)
        {
            // 对每一个孩子进行转化，注意结点之间的关系
            nxtNode->right = encode(subRoot->children[i]);
            // 往右深入一层
            nxtNode = nxtNode->right;
        }
        // 处理完成，返回即可
        return newNode;
    };
    return subEncode(root);
}

Node* Leetcode401_500::Soltuion::decode(Leetcode401_500::TreeNode* root)
{
    // 反序列化是类似的过程，我们也是定义一个递归回调函数
    function<Node*(TreeNode*)> subDecode = [&](TreeNode* subRoot) -> Node*
    {
        // 如果根结点是空的，那么直接返回 nullptr 即可
        if(!subRoot)
        {
            return nullptr;
        }
        // 否则，我们先转换根结点
        Node* newNode = new Node(subRoot->val);
        // 如果左孩子没有结点，那么说明原来的 N 叉树也没有孩子结点，直接返回 newNode 即可
        if(!subRoot->left)
        {
            return newNode;
        }
        // 否则，我们从左结点中递归对原来的所有子树进行反序列化即可
        TreeNode* nxtNode = subRoot->left;
        while(nxtNode)
        {
            newNode->children.push_back(decode(nxtNode));
            nxtNode = nxtNode->right;
        }
        return newNode;
    };
    // 调用即可
    return subDecode(root);
}