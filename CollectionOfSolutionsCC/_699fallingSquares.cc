#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::fallingSquares(vector<vector<int>>& positions)
{
    // 树状数组不好维护这种没法差分的目标值 (不好不代表不能，用树状数组维护这种不可差分的信息的方法可以参见 OI wiki，里面有用两个树状数组维护不可差分信息的讲解)
    // 我们考虑用线段树
    // 回忆一下线段树的基本功能：
    // 首先，线段树可以动态维护下面的信息：
    // 区间 [l, r] 之间的某个结果 (例如 max, min, sum 等) 
    // 本题我们需要维护的肯定就是 max 值了
    // 因为要判断一个落到 [l, r] 区间内的正方形最高可以叠到多高，只需要检查这个范围内最高的那个点位的高度即可
    // 我们思考怎样用一个线段树来维护 [1, n] 区间中每一个可能查询到的坐标区间上的最大值
    // 首先，需要一个线段树数组来记录一些状态信息
    // 我们定义为 tree
    // 至于这个数组有多长，理论上说，我们需要根据 positions 数组中的元素最大值来决定
    // 但是这道题离谱的数据存储格式，让我们不得不对整个数组先进行一次遍历，算出所需的最长长度。。 
    int n = 0;
    for(const auto& position : positions)
    {
        // position[0] -> 坐标
        // position[1] -> 边长
        // 那么 坐标+边长 就是最右侧的坐标
        // 我们根据这个值来更新 n 即可
        n = max(n, position[0]+position[1]);
    }
    // 根据我们不完整的记忆，要维护一个长度为 n 的区间，我们需要一棵长度为 4*n 的线段树
    // 具体论证可以看一下 OI Wiki 的网站
    struct node
    {
        // 每一个结点，我们需要存储几样东西：
        // 1. 左孩子结点坐标
        int left;
        // 2. 右孩子结点坐标
        int right;
        // 3. 如果是维护诸如 sum 这样的元素，那么我们还需要一个懒更新标记，不过 max 实际上用不到
        // 4. 实际上维护的结果值，本题要求的是高度，我们命名为 height 即可
        int height;
    };
    vector<node> tree(4*n);
    // 最后，直接定义一个长度为 4*n 的结点数组作为树的存储结构即可
    // 我们首先需要一个建树的函数，可以在这里定义一下
    // 定义为 build(p, l, r) -> 即构建序号为 p，左边界为 l，右边界为 r 的树结点
    // 对于序号为 p 的结点，它左孩子应该是 2*p，右孩子应该是 2*p+1
    // 并且，p 对应的是 [l, r]，那么它左孩子对应的就是 [l, (l+r)/2]，右孩子对应的就是 [(l+r)/2+1, r]
    function<void(int, int, int)> build = [&](int p, int l, int r) -> void
    {
        // 给结点 p 赋值，表明它代表的区间是 [l, r]
        tree[p].left = l; tree[p].right = r;
        if(l == r)
        {
            // 如果 l == r，说明我们现在是在构造一个叶子结点，不用继续递归了
            return;
        }
        // 否则，我们需要递归地构造左右孩子结点
        int mid = ((r-l)>>1)+l;
        build(2*p, l, mid);
        build(2*p+1, mid+1, r);
    };  
    // 我们需要考虑如何实现上面的 lazyUpdate 函数
    // 对结点 p 进行处理，它内部保存的 height 值其实在这里就是 "懒" 信息了
    function<void(int)> lazyUpdate = [&](int p) -> void
    {
        // 我们把 p 的 "懒" 信息传递给它的两个孩子
        // 对于本题，"懒" 信息和实际的存储值重合了
        // 所以我们只保存并传递 height 值给孩子结点即可
        if(tree[p].height != 0)
        {
            tree[2*p].height = max(tree[p].height, tree[2*p].height);
            tree[2*p+1].height = max(tree[p].height, tree[2*p+1].height);
        }
        // 传递完成，返回即可
        return;
    };
    // 完成建树后，我们还需要一个更新函数 update，用于处理下面的功能：
    // 更新区间 [l, r] 中的值，修改为 val
    // 定义为 update(p, l, r, h)
    // 即修改结点 p 上，[l, r] 交叠出来的区间上的值为 h
    function<void(int, int, int, int)> update = [&](int p, int l, int r, int h) -> void
    {
        // 更新前，我们检查：
        // [l, r] 区间和 p 所代表的区间之间的重叠部分的情况
        // 1. [l, r] 区间就包含了 p 所代表的范围，那么我们直接把更新设置到当前结点即可，不用进一步深入了
        // 这里其实是 "懒" 的思想
        if(tree[p].left >= l && tree[p].right <= r)
        {
            tree[p].height = max(tree[p].height, h);
            return;
        }
        // 2. [l, r] 区间并不包含 p 整个范围，那么我们只更新那些交叠的区间即可
        // 不过，由于我们采用了上面的这种 "懒" 策略
        // 所以这里并不能马上对左右孩子进行更新
        // 我们需要先调用一个处理 "懒更新" 要求的函数，来预先告诉左右孩子之前被 "懒" 掉了的信息
        // 我们先假设我们实现了这个函数 （）
        lazyUpdate(p);
        // 此时两个孩子结点已经知道了 p 结点之前 "懒" 下来的数据，之后可以正常把 h 更新给左右孩子了
        // 先计算出两个孩子结点应该有的下标范围
        int mid = ((tree[p].right-tree[p].left)>>1)+tree[p].left;
        // 左结点的区间为：
        // [left, (left+right)/2]
        // 右结点的区间为：
        // [(left+right)/2+1, right]
        // 之后我们检查 [l, r] 是否接触到了这两个区间，只有接触到了，我们才对对应的区间进行更新
        if(l <= mid)
        {
            // 接触到了左孩子，我们对左孩子进行更新
            update(2*p, l, r, h);
        }
        if(r >= mid+1)
        {
            // 接触到了右孩子，我们对右孩子进行更新
            update(2*p+1, l, r, h);
        }
    };  
    // 完成了对树进行维护的操作函数后，我们最后还需要一个用于查询具体区间的 (最大) 值的函数
    // 命名为 query 即可
    // query(p, l, r) 代表，我们在结点 p 代表的区间中，查找 [l, r] 区间上的最大值
    function<int(int, int, int)> query = [&](int p, int l, int r) -> int
    {
        // 基本情况：
        // 如果 p 维护的区间长度为 1，那么我们直接返回这个结果即可
        // 注意：我们的假设是：[l, r] 区间至少与 p 代表的区间有交集，如果 p 本身区间长度就只有 1，那么我们就可以直接返回它存储的信息作为结果
        if(tree[p].left == tree[p].right)
        {
            return tree[p].height;
        }
        // 一般情况：p 维护的区间长度大于 1，那么我们考虑计算当前 [l, r] 和 p 代表的区间之间的关系
        // 别忘了先 lazyUpdate..
        lazyUpdate(p);
        // 我们只需要仿照上面 update 部分的代码，分别在 p 的两个子结点中查询 [l, r] 区间的最值
        int mid = ((tree[p].right-tree[p].left)>>1)+tree[p].left;
        // 检查 [left, mid] 和 [mid+1, right] 与 [l, r] 之间的关系
        int res = INT_MIN;
        if(mid >= l)
        {
            // 如果 p 的左孩子与 [l, r] 区间有交集，那么我们把它考虑进来
            res = max(res, query(2*p, l, r));
        }
        if(mid+1 <= r)
        {
            // 如果 p 的右孩子与 [l, r] 区间有交集，那么我们把它考虑进来
            res = max(res, query(2*p+1, l, r));
        }
        // 即使 [l, r] 与 p 没有任何交集，我们返回的也是 INT_MIN，不影响其它部分查询的结果
        return res;
    };
    // 全部完成后，我们就只需要进行调用了
    // 首先，建树
    // 构建根结点，它代表的区间是 [1, n]
    build(1, 1, n);
    vector<int> res;
    int totalMax = INT_MIN;
    // 建树完成后，我们就可以开始对每一个 position 进行处理了
    for(const auto& position : positions)
    {
        // 对于每一个 position，我们首先根据它更新线段树中对应区间的最大值
        // 但是基于这道题的定义，我们可能需要先查询对应区间的最大值，再把这个最大值加上当前方块的边长作为新的最大值再更新一次
        int curMax = query(1, position[0], position[0]+position[1]);
        int newMax = curMax+position[1];
        update(1, position[0], position[0]+position[1], newMax);
        res.push_back(max(newMax, totalMax));
        totalMax = max(newMax, totalMax);
        // 更新完成，继续下一个方块的处理
    }
    return res;
}

// 注意，我们上面的代码是有问题的，忽略了题目的一个限制条件：
// 互相擦过的方块不能堆叠
// 思考一下如何避免这种擦过情况可能导致的错误解答
// 第一想法：
// 得出一个覆盖 [l1, r1] 的矩形的时候，只记录区间 [l1, r1) 的最值，在检查 [l2, r2] 的时候，我们也只检查 [l2, r2) 区间中的元素
// 这样，我们就可以避免在检查 [l2, r2) 的时候，遇到只出现在 l2 的最大值 (由 [l1, r1) 的更新策略避免)，或者遇到只出现在 r2 的最大值 (由[l2, r2) 的检查策略避免)了
vector<int> fallingSquares(vector<vector<int>>& positions)
{
    // 树状数组不好维护这种没法差分的目标值 (不好不代表不能，用树状数组维护这种不可差分的信息的方法可以参见 OI wiki，里面有用两个树状数组维护不可差分信息的讲解)
    // 我们考虑用线段树
    // 回忆一下线段树的基本功能：
    // 首先，线段树可以动态维护下面的信息：
    // 区间 [l, r] 之间的某个结果 (例如 max, min, sum 等) 
    // 本题我们需要维护的肯定就是 max 值了
    // 因为要判断一个落到 [l, r] 区间内的正方形最高可以叠到多高，只需要检查这个范围内最高的那个点位的高度即可
    // 我们思考怎样用一个线段树来维护 [1, n] 区间中每一个可能查询到的坐标区间上的最大值
    // 首先，需要一个线段树数组来记录一些状态信息
    // 我们定义为 tree
    // 至于这个数组有多长，理论上说，我们需要根据 positions 数组中的元素最大值来决定
    // 但是这道题离谱的数据存储格式，让我们不得不对整个数组先进行一次遍历，算出所需的最长长度。。 
    int n = 0;
    for(const auto& position : positions)
    {
        // position[0] -> 坐标
        // position[1] -> 边长
        // 那么 坐标+边长 就是最右侧的坐标
        // 我们根据这个值来更新 n 即可
        n = max(n, position[0]+position[1]);
    }
    // 根据我们不完整的记忆，要维护一个长度为 n 的区间，我们需要一棵长度为 4*n 的线段树
    // 具体论证可以看一下 OI Wiki 的网站
    struct node
    {
        // 每一个结点，我们需要存储几样东西：
        // 1. 左孩子结点坐标
        int left;
        // 2. 右孩子结点坐标
        int right;
        // 3. 如果是维护诸如 sum 这样的元素，那么我们还需要一个懒更新标记，不过 max 实际上用不到
        // 4. 实际上维护的结果值，本题要求的是高度，我们命名为 height 即可
        int height;
    };
    vector<node> tree(4*n);
    // 最后，直接定义一个长度为 4*n 的结点数组作为树的存储结构即可
    // 我们首先需要一个建树的函数，可以在这里定义一下
    // 定义为 build(p, l, r) -> 即构建序号为 p，左边界为 l，右边界为 r 的树结点
    // 对于序号为 p 的结点，它左孩子应该是 2*p，右孩子应该是 2*p+1
    // 并且，p 对应的是 [l, r]，那么它左孩子对应的就是 [l, (l+r)/2]，右孩子对应的就是 [(l+r)/2+1, r]
    function<void(int, int, int)> build = [&](int p, int l, int r) -> void
    {
        // 给结点 p 赋值，表明它代表的区间是 [l, r]
        tree[p].left = l; tree[p].right = r;
        if(l == r)
        {
            // 如果 l == r，说明我们现在是在构造一个叶子结点，不用继续递归了
            return;
        }
        // 否则，我们需要递归地构造左右孩子结点
        int mid = ((r-l)>>1)+l;
        build(2*p, l, mid);
        build(2*p+1, mid+1, r);
    };  
    // 我们需要考虑如何实现上面的 lazyUpdate 函数
    // 对结点 p 进行处理，它内部保存的 height 值其实在这里就是 "懒" 信息了
    function<void(int)> lazyUpdate = [&](int p) -> void
    {
        // 我们把 p 的 "懒" 信息传递给它的两个孩子
        // 对于本题，"懒" 信息和实际的存储值重合了
        // 所以我们只保存并传递 height 值给孩子结点即可
        if(tree[p].height != 0)
        {
            tree[2*p].height = max(tree[p].height, tree[2*p].height);
            tree[2*p+1].height = max(tree[p].height, tree[2*p+1].height);
        }
        // 传递完成，返回即可
        return;
    };
    // 完成建树后，我们还需要一个更新函数 update，用于处理下面的功能：
    // 更新区间 [l, r] 中的值，修改为 val
    // 定义为 update(p, l, r, h)
    // 即修改结点 p 上，[l, r] 交叠出来的区间上的值为 h
    function<void(int, int, int, int)> update = [&](int p, int l, int r, int h) -> void
    {
        // 更新前，我们检查：
        // [l, r] 区间和 p 所代表的区间之间的重叠部分的情况
        // 1. [l, r] 区间就包含了 p 所代表的范围，那么我们直接把更新设置到当前结点即可，不用进一步深入了
        // 这里其实是 "懒" 的思想
        if(tree[p].left >= l && tree[p].right <= r)
        {
            tree[p].height = max(tree[p].height, h);
            return;
        }
        // 2. [l, r] 区间并不包含 p 整个范围，那么我们只更新那些交叠的区间即可
        // 不过，由于我们采用了上面的这种 "懒" 策略
        // 所以这里并不能马上对左右孩子进行更新
        // 我们需要先调用一个处理 "懒更新" 要求的函数，来预先告诉左右孩子之前被 "懒" 掉了的信息
        // 我们先假设我们实现了这个函数 （）
        lazyUpdate(p);
        // 此时两个孩子结点已经知道了 p 结点之前 "懒" 下来的数据，之后可以正常把 h 更新给左右孩子了
        // 先计算出两个孩子结点应该有的下标范围
        int mid = ((tree[p].right-tree[p].left)>>1)+tree[p].left;
        // 左结点的区间为：
        // [left, (left+right)/2]
        // 右结点的区间为：
        // [(left+right)/2+1, right]
        // 之后我们检查 [l, r] 是否接触到了这两个区间，只有接触到了，我们才对对应的区间进行更新
        if(l <= mid)
        {
            // 接触到了左孩子，我们对左孩子进行更新
            update(2*p, l, r, h);
        }
        if(r >= mid+1)
        {
            // 接触到了右孩子，我们对右孩子进行更新
            update(2*p+1, l, r, h);
        }
    };  
    // 完成了对树进行维护的操作函数后，我们最后还需要一个用于查询具体区间的 (最大) 值的函数
    // 命名为 query 即可
    // query(p, l, r) 代表，我们在结点 p 代表的区间中，查找 [l, r] 区间上的最大值
    function<int(int, int, int)> query = [&](int p, int l, int r) -> int
    {
        // 基本情况：
        // 如果 p 维护的区间长度为 1，那么我们直接返回这个结果即可
        // 注意：我们的假设是：[l, r] 区间至少与 p 代表的区间有交集，如果 p 本身区间长度就只有 1，那么我们就可以直接返回它存储的信息作为结果
        if(tree[p].left == tree[p].right)
        {
            return tree[p].height;
        }
        // 一般情况：p 维护的区间长度大于 1，那么我们考虑计算当前 [l, r] 和 p 代表的区间之间的关系
        // 别忘了先 lazyUpdate..
        lazyUpdate(p);
        // 我们只需要仿照上面 update 部分的代码，分别在 p 的两个子结点中查询 [l, r] 区间的最值
        int mid = ((tree[p].right-tree[p].left)>>1)+tree[p].left;
        // 检查 [left, mid] 和 [mid+1, right] 与 [l, r] 之间的关系
        int res = INT_MIN;
        if(mid >= l)
        {
            // 如果 p 的左孩子与 [l, r] 区间有交集，那么我们把它考虑进来
            res = max(res, query(2*p, l, r));
        }
        if(mid+1 <= r)
        {
            // 如果 p 的右孩子与 [l, r] 区间有交集，那么我们把它考虑进来
            res = max(res, query(2*p+1, l, r));
        }
        // 即使 [l, r] 与 p 没有任何交集，我们返回的也是 INT_MIN，不影响其它部分查询的结果
        return res;
    };
    // 全部完成后，我们就只需要进行调用了
    // 首先，建树
    // 构建根结点，它代表的区间是 [1, n]
    build(1, 1, n);
    vector<int> res;
    int totalMax = INT_MIN;
    // 建树完成后，我们就可以开始对每一个 position 进行处理了
    for(const auto& position : positions)
    {
        // 对于每一个 position，我们首先根据它更新线段树中对应区间的最大值
        // 但是基于这道题的定义，我们可能需要先查询对应区间的最大值，再把这个最大值加上当前方块的边长作为新的最大值再更新一次
        int curMax = query(1, position[0], position[0]+position[1]-1);
        int newMax = curMax+position[1];
        update(1, position[0], position[0]+position[1]-1, newMax);
        res.push_back(max(newMax, totalMax));
        totalMax = max(newMax, totalMax);
        // 更新完成，继续下一个方块的处理
    }
    return res;
}

// 总结：上面的基本静态的线段树解法使用的内存空间较大，在 position[0]+position[1] 较大时会导致内存不足 (也就是开了太多无意义的内存空间)
// 我们需要考虑优化成动态开点的线段树结构
// 具体来说，其实就是把上面数组形式表示的线段树数组，改成用类似二叉树的那种指针表示方法
// 我们思考一下怎么处理
vector<int> fallingSquares(vector<vector<int>>& positions)
{
    // 首先，肯定还是需要一个 node 结构体
    struct node
    {
        // 依然是一个保存的高度值，这个不用变
        int height;
        // 一样保存两个数值，代表当前结点保存的信息对应的区间范围
        int lv;
        int rv;
        // 额外保存两个指针，指向当前 node 的左右孩子结点
        node* left;
        node* right;
        // 懒更新信息是需要的，原因后面会细说
        int lazy;
        // 这里手写一个具体化的构造函数，供后面的函数调用
        node(int _lv, int _rv) : height(0), lv(_lv), rv(_rv), left(nullptr), right(nullptr), lazy(0) {}
        // 默认构造函数
        node() : height(0), lv(0), rv(0), left(nullptr), right(nullptr), lazy(0) {}
    };
    // 考虑如何建树
    // 如果是动态开点，说白了，我们 "只在有必要的时候才新建树结点"
    // 所以 build 函数实际上不再需要了，但是可以把对 root 构建的函数封装一下，意思意思。。
    // build(l, r) 代表我们要构建一个代表区间为 [l, r] 的线段树
    function<node*(int, int)> build = [&](int l, int r) -> node*
    {
        return new node(l, r);
    };
    // 注意，因为用到了 new，所以我们理所应当编写一个 delete 相关的函数，来处理内存分配回收问题
    function<void(node*)> destroy = [&](node* p) -> void
    {
        // 递归删除，先删除 p 的左右孩子，最后删除它自己
        if(!p)
        {
            // 递归终点
            return;
        }
        if(p->left)
        {
            destroy(p->left);
        }
        if(p->right)
        {
            destroy(p->right);
        }
        // 最后删除自己
        delete p;
        p = nullptr;
    };
    // 我们反而需要把这个构建功能融入到 update 函数和 lazyUpdate 函数里面去
    function<void(node*)> lazyUpdate = [&](node* p) -> void
    {
        // 懒更新函数，我们是要把 p 结点中的信息下放更新给它的两个孩子
        // 这里根据 p 左右孩子的存在性进行具体处理即可
        if(!p->left)
        {
            // 左孩子不存在，那么我们新建一个左孩子
            // 用默认构造函数即可
            // 注意告诉这个孩子它代表的区间左右界
            // 左孩子对应 [lv, (lv+rv)/2]
            p->left = new node(p->lv, ((p->rv-p->lv)>>1)+p->lv);
        }
        if(!p->right)
        {
            // 注意告诉这个孩子它代表的区间左右界
            // 右孩子对应 [(lv+rv)/2+1, rv]
            p->right = new node(((p->rv-p->lv)>>1)+p->lv+1, p->rv);
        }
        if(p->lazy == 0)
        {
            // 没有懒信息，我们可以不用进一步下放数据了
            return;
        }
        // 进行信息传递即可
        p->left->height = max(p->height, p->left->height);
        p->right->height = max(p->height, p->right->height);
        // 别忘了把懒信息也告诉孩子！
        p->left->lazy = p->lazy;
        p->right->lazy = p->lazy;
        // 清空懒信息，防止出现错误更新
        p->lazy = 0;
    };
    // 考虑具体化一下 update 函数
    // update(p, l, r, h) 代表把 p 结点中对应与 [l, r] 有重叠的部分，更新成 h
    function<void(node*, int, int, int)> update = [&](node* p, int l, int r, int h) -> void
    {
        // 思路基本一致
        // 首先检查 p 的范围是否已经包含在了 [l, r] 中
        if(p->lv >= l && p->rv <= r)
        {
            // 那么我们直接把 p 的值进行更新即可
            // 同时别忘了记录懒信息！
            p->height = max(p->height, h);
            p->lazy = h;
            return;
        }
        // 否则，我们只需要修改 p 代表的区间和 [l, r] 有交集的那部分即可
        int mid = ((p->rv-p->lv)>>1)+p->lv;
        // cout << mid << "to update " << endl;
        // 但注意，更新前，我们需要先 lazyUpdate 我们之前没下放的信息，这一步也同时在有必要的时候新建了子结点
        lazyUpdate(p);
        // 检查左区间
        if(l <= mid)
        {
            // 此时说明 [l, r] 和 [left, mid] 有交集
            update(p->left, l, r, h);
        }
        // 检查右区间
        if(mid+1 <= r)
        {
            // 此时说明 [l, r] 和 [mid+1, right] 有交集
            update(p->right, l, r, h);
        }
        // 处理完成，最后用 p 左右孩子的结果再更新一次 p 的结果
        p->height = max(p->left->height, p->right->height);
    };
    // 最后是查询函数
    // 我们需要查询 [l, r] 区间中的最大值
    function<int(node*, int, int)> query = [&](node* p, int l, int r) -> int
    {
        // 基本情况：如果 p 代表的范围包含在了 [l, r] 中，那么我们直接返回结果即可
        if(l <= p->lv && r >= p->rv)
        {
            return p->height;
        }
        // 其它情况下，p 代表的区间长度不是 1，那么我们需要判断 p 代表的区间中那些和 [l, r] 有交集的部分
        // 注意，依然需要先对 p 进行懒更新，同时也新建了不存在的结点
        lazyUpdate(p);
        // 之后根据 p 左右孩子的区间范围进行后续处理
        int mid = ((p->rv-p->lv)>>1)+p->lv;
        // cout << "mid is " << mid << endl;
        int res = INT_MIN;
        if(l <= mid)
        {
            // [l, r] 与 [left, mid] 有交集
            // 我们查询左孩子中对应在 [l, r] 区间中的范围上的最大值
            res = max(res, query(p->left, l, r));
        }
        if(mid+1 <= r)
        {
            // [l, r] 与 [mid+1, right] 有交集
            // 我们查询右孩子中对应在 [l, r] 区间中的范围上的最大值
            res = max(res, query(p->right, l, r));
        }
        // 返回结果即可
        return res;
    };
    // 用这样的定义，我们就只需要初始化一个根结点就可以了
    // 依旧是先计算一下 n 的值，然后构建整棵树
    int n = 1;
    for(const auto& position : positions)
    {
        n = max(n, position[0]+position[1]);
    }
    // 构建根结点，赋值给 root
    node* root = build(1, n);
    vector<int> res;
    int totalMax = 0;
    // 用这个 root 来处理后面的问题
    for(const auto& position : positions)
    {
        // 针对每一个方块，我们检查它代表的 [position[0], position[0]+position[1]-1] 区间上的最大值
        int curMax = query(root, position[0], position[0]+position[1]-1);
        int newMax = curMax+position[1];
        totalMax = max(totalMax, newMax);
        res.push_back(totalMax);
        update(root, position[0], position[0]+position[1]-1, newMax);
    }
    destroy(root);
    return res;
}