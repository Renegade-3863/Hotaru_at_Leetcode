#include "Solution.h"

bool Leetcode501_600::Soltuion::isSubtree(Leetcode501_600::TreeNode* root, Leetcode501_600::TreeNode* subRoot)
{
    // 简单来说，几乎所有二叉树类的题目都可以用递归的方式来处理
    // 我们定义下面的函数：
    // subCheck(root1, root2)
    // 代表 root1 树中是否存在 root2 这棵子树
    // 根据内部的推理，再写一个 isSame(root1, root2) 函数来判断两棵树是否相等
    function<bool(TreeNode*, TreeNode*)> isSame = [&](TreeNode* root1, TreeNode* root2) -> bool
    {
        // 如果 root1 和 root2 均为 nullptr，那么直接返回 true
        if(!root1 && !root2)
        {
            return true;
        }
        if(!root1 || !root2)
        {
            return false;
        }
        // 其它情况下，两个结点均非空
        return root1->val == root2->val && isSame(root1->left, root2->left) && isSame(root1->right, root2->right);
    };
    function<bool(TreeNode*, TreeNode*)> subCheck = [&](TreeNode* root1, TreeNode* root2) -> bool
    {
        // 如果 root2 为空，那么肯定包含
        if(!root2)
        {
            return true;
        }        
        // root2 != nullptr
        // 那么如果 root1 非空，我们直接返回 false 即可，一个空树中不可能包含一棵非空树
        if(!root1)
        {
            return false;
        }
        // 此时 root1 和 root2 均非空，那么我们检查 root1->val 是否等于 root2->val
        if(root1->val == root2->val)
        {
            // 当前根结点数值相等，那么我们进一步检查：root1 的左子树是否等于 root2 的左子树
            // 同时，是否有：root1 的右子树等于 root2 的右子树
            // 注意，不能用求子树的方法！！
            // 我们还需要定义一个 isSame(root1, root2) 来判断两棵树是否全等
            if(isSame(root1->left, root2->left) && isSame(root1->right, root2->right))
            {
                return true;
            }
            else
            {
                // 否则，我们继续检查左右子树
                return subCheck(root1->left, root2) || subCheck(root1->right, root2);
            }
        }
        return subCheck(root1->left, root2) || subCheck(root1->right, root2);
    };
    return subCheck(root, subRoot);
}

// 添加一个记忆化表加速搜索
bool isSubtree(TreeNode* root, TreeNode* subRoot)
{
    // 添加一个二维哈希表，用于记录 "某对结点确定的树对是否相等" 这一信息
    unordered_map<TreeNode*, unordered_map<TreeNode*, bool>> memo;
    // 如果 memo[root1].find(root2) != memo[root1].end()
    function<bool(TreeNode*, TreeNode*)> isSame = [&](TreeNode* root1, TreeNode* root2) -> bool
    {
        if(memo.find(root1) != memo.end() && memo[root1].find(root2) != memo[root1].end())
        {
            return memo[root1][root2];
        }
        // 如果 root1 和 root2 均为 nullptr，那么直接返回 true
        if(!root1 && !root2)
        {
            return true;
        }
        if(!root1 || !root2)
        {
            return false;
        }
        // 其它情况下，两个结点均非空
        memo[root1][root2] = root1->val == root2->val && isSame(root1->left, root2->left) && isSame(root1->right, root2->right);
        return memo[root1][root2];
    };
    function<bool(TreeNode*, TreeNode*)> subCheck = [&](TreeNode* root1, TreeNode* root2) -> bool
    {
        // 如果 root2 为空，那么肯定包含
        if(!root2)
        {
            return true;
        }        
        // root2 != nullptr
        // 那么如果 root1 非空，我们直接返回 false 即可，一个空树中不可能包含一棵非空树
        if(!root1)
        {
            return false;
        }
        // 此时 root1 和 root2 均非空，那么我们检查 root1->val 是否等于 root2->val
        if(root1->val == root2->val)
        {
            // 当前根结点数值相等，那么我们进一步检查：root1 的左子树是否等于 root2 的左子树
            // 同时，是否有：root1 的右子树等于 root2 的右子树
            // 注意，不能用求子树的方法！！
            // 我们还需要定义一个 isSame(root1, root2) 来判断两棵树是否全等
            if(isSame(root1->left, root2->left) && isSame(root1->right, root2->right))
            {
                return true;
            }
            else
            {
                // 否则，我们继续检查左右子树
                return subCheck(root1->left, root2) || subCheck(root1->right, root2);
            }
        }
        return subCheck(root1->left, root2) || subCheck(root1->right, root2);
    };
    return subCheck(root, subRoot);
}

// 第二版
// 尝试一下 KMP 算法
// 想尝试这个算法的原因在于：
// 题目要求我们从一个大的子集 (树) 中，找出一个较小的子集 (树) 的存在
// 这个性质和 KMP 从功能上不谋而合 (KMP 的作用是从一串母串中找出一个子串的存在)
bool isSubtree(TreeNode* root, TreeNode* subRoot)
{
    // 我们可以分别对两棵树进行遍历，把整棵树转化成两个字符串的形式，之后对两个字符串应用 KMP 算法，就能判断出结果是否满足包含关系了
    // 不过有一个细节问题，二叉树本身有左右偏性，所以我们直接比较二者的纯遍历序列不一定是正确的：
    // 比如下面的例子：
    /*
        7           7
       /             \
      8               8
    */
    // 这两棵树的遍历结果 (以先序为例)
    // 都是 [7, 8]
    // 然而，从实际结构上说，二者并不相等
    // 所以，我们还需要引入 "Null" 这个子串，用来标识一个空的结点间隔
    // 总结一下基本的操作方法：
    // 按照相同的方式遍历两棵树，把包括空结点在内的所有结点遍历信息组织成一个字符串
    // 我们假设称其为 str1 和 str2，至此，问题就变成了：
    // str1 中是否包含了 str2 这个子串
    // 我们可以用 Morris 遍历的架构模式来遍历两棵树
    // 先判断一些比较简单的情况：如果 root 为空结点，那么返回 !subRoot (只有 subRoot 也为空结点时，才能返回 true)
    // 如果 subRoot 为空结点，那么返回 false
    if(!root)
    {
        return !subRoot;
    }
    if(!subRoot)
    {
        return true;
    }
    // 对 root 进行遍历，存储结果到 str1 中
    string str1 = "", str2 = "";
    // 写到这里，发现处理 root 和 subRoot 的函数代码几乎一致，故考虑后续进行封装 (称为 dfs)
    function<void(string&, TreeNode*)> dfs = [&](string& str, TreeNode* root)
    {
        if(!root)
        {
            str += "NULL,";
            return;
        }
        str += to_string(root->val);
        str += ",";
        // 递归合并两棵子树
        dfs(str, root->left);
        dfs(str, root->right);
    };
    // 分别对 root 和 subRoot 进行处理
    dfs(str1, root);
    dfs(str2, subRoot);
    // 处理完成，我们需要考虑使用 KMP 算法来检查 str1 是否包含 str2 这个子串
    // 回顾：KMP 算法需要有一个 getNext 函数和一个 KMP 本体函数，分别用于计算前缀函数和进行实际的 子串匹配操作
    function<void(const string&, vector<int>&)> getNext = [&](const string& str, vector<int>& next) -> void
    {
        // 通过 str 计算出它对应的前缀数组
        int n = str.size();
        next.resize(n, 0);
        int k = -1, j = 0;
        // next[0] 赋值为 -1，代表：如果母串当前字符不能和 str[0] 进行匹配，那么这个字符就不是合法的位置了，我们需要后移处理，故赋值为 -1
        next[0] = -1;
        while(j < n)
        {
            // 两种情况可以进行下一个下标的填写
            // 1. k == -1
            // 此时说明
            if(k == -1 || str[k] == str[j])
            {
                // 同步后移 k 和 j，此时 next[j+1] 这个下标上的前缀值已经可以填写了
                ++k; ++j;
                if(j == n)
                {
                    break;
                }
                // 按理来说，我们应该可以把递增后的 k 赋值给 next[j+1]，但是我们可以进行一步剪枝
                // 如果 str[k] == str[j]，那么我们即使在匹配的时候，把 str 这个子串的下标前移到了现在这个 k 处，那么也一定是没法匹配的，因为两个位置上的字符是完全一样的
                if(str[k] == str[j])
                {
                    // 递归赋值，跳过这个重复的下标即可
                    next[j] = next[k];
                }
                else
                {
                    // 否则，这是一个不同的字符，那么我们就可以直接赋值
                    next[j] = k;
                }
            }
            // 其它情况：
            // k != -1 && str[k] != str[j]
            // 此时说明这个 k 没法和 str[j] 字符进行前后缀匹配，我们需要进一步前移 k 值
            else
            {
                k = next[k];
            }
        }
    };
    // getNext 函数处理完成，剩下的就是 KMP 函数本体了
    // 函数用于实际判断：str1 字符串中是否包含了 str2 函数
    function<int(const string&, const string&, const vector<int>&)> KMP = [&](const string& str1, const string& str2, const vector<int>& next) -> int
    {
        // next 前缀数组是我们处理问题的核心构件
        int i = 0, j = 0, m = str1.size(), n = str2.size();
        // i == m，即整个 str1 被检查完成，是整个函数结束的条件
        while(i < m)
        {   
            if(j == -1 || str1[i] == str2[j])
            {
                // cout << i << ": " << j << endl;
                ++i; ++j;
                if(j == n)
                {
                    // 匹配完了整个 str2，那么我们就可以结束循环了，因为本题只要求检查 "存在性"，所以我们没必要返回实际的子串起点坐标
                    return i-n;
                }
                // 否则，继续后续匹配
            }
            else
            {
                // 当前字符没法匹配，我们需要回溯 j，利用的就是 next 数组
                j = next[j];
            }
        }
        // 循环完成，没有找到合适的子串，那么返回 false 即可
        return -1;
    };
    // 我们创建一个长度为 n 的 next 数组，就可以开始使用上面的两个函数了
    vector<int> next;
    getNext(str2, next);
    int pos = KMP(str1, str2, next);
    // 使用 KMP 函数即可
    // 最后这步是面向测试用例编程，下面这个用例会出现问题：
    // root -> 12
    // subRoot -> 2
    // 上面 dfs 方法生成的两个字符串是
    // 12,NULL,NULL
    // 2,NULL,NULL
    // KMP 会判断二者都有 "2,NULL,NULL" 这个部分
    // 所以我们额外添加一步检查，判断匹配部分是不是一个完整的树结构即可
    return (pos != -1) && (pos == 0 || str1[pos-1] == ',');
}
    
// 第三版：
// 第三种，个人认为是理解难度最大的算法
// 即树形哈希算法
// 这种算法，最难的一步往往是：设计树的哈希函数
// 一般来讲，考虑的无关算子越多，哈希函数的冲突概率就越小
// 所以这里我们考虑多种算子：
// 1. 考虑引入当前根结点的左子树的哈希值
// 2. 考虑引入当前根结点的右子树的哈希值
// 3. 考虑引入左右子树的大小 (结点个数)
// 故官解给出了那个包含了上述条件，甚至还套了一层 "第 n 个素数" 的壳的哈希函数：
// h(node) = node->val + 31xh(lNode)xp(slNode) + 179xh(rNode)p(srNode)
// 其中，h(x) 代表 x 的哈希值，p(x) 代表第 x 个素数值
// 写到这里，我们就明白，还需要一种算法来高效地找出从 2 开始的所有素数值
// 如果记忆力比较好的，会想起来，这就是 "埃氏筛法"
// 这个算法的本质思想就是一句话：
// 一个本身是素数的数，它的所有倍数一定都不是素数
bool isSubtree(TreeNode* root, TreeNode* subRoot)
{
    // 由于子二叉树本身大小被限定为了 [1, 1000]，我们这里取前 15000 个数，大概就能找够需要用的素数
    static constexpr int MAX_N = 15000+5;
    // 选一个比较大的外部模数作为整个哈希的取值范围
    static constexpr int MOD = 1e9+7;
    // 先用 "埃氏筛法" 取出前 1005 个素数
    int idx = 0;
    vector<int> primes(1005, 0);
    // visited 数组，用于标记某个数是否为合法的素数，如果在下面的 for 循环遍历到某个位置 i 时，visited[i] 为 false，那么我们就断定 i 是个素数
    bool visited[MAX_N];
    // 初始化为全 false
    // 循环直到填满整个 "素数" 数组为止
    for(int i = 2; i < MAX_N && idx < 1005; ++i)
    {
        if(!visited[i])
        {
            // i 是一个素数，把它放到 idx 下标上
            primes[idx++] = i;
            // 同时，根据这个素数，不断往后乘，直到乘积超出了可表示的范围 (INT_MAX 或 MAX_N)
            if(i < INT_MAX / i)
            {
                for(int j = i*i; j < MAX_N; j += i)
                {
                    // 把这些能乘出来的数都标记为 "非素数"
                    visited[j] = true;
                }
            }
        }
        // 否则，i 是一个合数，我们跳过它即可
    }
    // 找出了所有素数，剩下的就只有对树进行哈希映射了
    // 定义两个新的哈希表，记录每个结点为根的子树对应的 (哈希值，子树大小) 状态值
    struct Status
    {
        // f 代表子树的哈希值，s 代表子树的大小
        int f, s;
        Status(int _f = 0, int _s = 0) : f(_f), s(_s) {}
    };
    // 一个哈希表负责原树：root，另一个负责子树：subRoot
    unordered_map<TreeNode*, Status> hS, hT;
    // 我们需要一种递归函数，来对一棵以 node 为根的子树的哈希值进行计算
    function<void(TreeNode*, unordered_map<TreeNode*, Status>&)> dfs = [&](TreeNode* node, unordered_map<TreeNode*, Status>& h) 
    {
        // 初始化状态值，哈希值赋为 node->val，子树大小赋为 1
        h[node] = Status(node->val, 1);
        // 否则，我们根据递归计算的左右子树哈希值进行当前结点的哈希值计算
        // 如果左子树非空，那么我们先递归计算出它的哈希值，再套入上面的公式
        if(node->left)
        {
            dfs(node->left, h);
            // 计算完成，结果现在保存在了 h 表中，我们提取进行使用即可
            h[node].s += h[node->left].s;
            h[node].f = (h[node].f+(31LL*h[node->left].f*primes[h[node->left].s])%MOD)%MOD;
        }
        if(node->right)
        {
            dfs(node->right, h);
            h[node].s += h[node->right].s;
            h[node].f = (h[node].f+(179LL*h[node->right].f*primes[h[node->right].s])%MOD)%MOD;
        }
        // 计算完成，函数结束
    };
    // 我们调用上面的函数，对 hS 和 hT 表进行填充即可
    dfs(root, hS);
    dfs(subRoot, hT);
    // 最后，就是检查：hS 表中是否存在 hT[subRoot] 这个哈希值
    int target = hT[subRoot].f;
    for(const auto& [k, v] : hS)
    {
        if(v.f == target)
        {
            return true;
        }
    }
    // 不存在，返回 false 即可
    return false;
}