#include "Solution.h"

vector<double> Leetcode401_500::Soltuion::medianSlidingWindow(vector<int>& nums, int k)
{
    int n = nums.size();
    // 一道很不错的细节类题目，考察了很多高级算法使用的数据结构和思想
    // 我们要实现的东西，本质上说，是两个优先队列
    // 具体来讲：是一个大顶堆和一个小顶堆
    // 保证在每次计算滑动窗口中的中位数的时候，都有下面的事实成立：
    // 大顶堆和小顶堆中有效元素的个数差距不超过一个，并且大顶堆中的元素个数不小于小顶堆中的元素个数，同时保证大小顶堆中的堆顶元素都是有效的
    // 只要保证了这个条件成立，那么我们就只需要用下面的方法来计算每个时刻的窗口中位数：
    // 如果 k 为偶数，那么中位数就是两堆顶元素的平均值，如果 k 为奇数，那么中位数就是大顶堆堆顶的元素值
    // 那么我们剩下要做的就是保证在窗口滑动的时候，能够维持上面的这个事实成立
    // 窗口滑动无非两件事：
    // (我们下面假设进行任何操作时：大顶堆堆顶的元素是 small, 小顶堆堆顶的元素是 large)
    // 1. 向原来的窗口中添加一个右侧的新元素
    // 假设要添加的新元素是 nums[i]
    // 那么我们可以把这个元素和大顶堆堆顶的元素进行比较，如果 nums[i] <= small，那么我们应该把这个元素添加到大顶堆中去，因为它的值在左半范围内
    // 否则，我们这里把 nums[i] 添加到小顶堆中去
    // 不过注意，任何的添加和删除操作都可能会导致两个队列中的元素个数不符合上面的事实假设
    // 所以我们可能会需要进行 "平衡维护" 操作，这一点在后面统一进行
    // 2. 从原来的窗口中删除一个最左侧的旧元素
    // 假设我们要删除的旧元素是 nums[j]
    // 注意到这样一个事实：除非 nums[j] 是大顶堆或者小顶堆的堆顶元素，否则我们没法实时地对 nums[j] 进行出队删除操作
    // 所以我们这里使用线段树中常用的技巧：懒删除
    // 具体做法是：我们使用一个哈希表结构：map，记录所有现在被我们 "认为" 已经被删除的元素
    // 如果现在两个堆顶的元素都不是 nums[j]，那么我们就把这个要删除的元素记录到 map 哈希表中，直到堆顶的元素变成了 nums[j] 的时候，我们才实际进行删除 (这实际上就是前面提到的 "平衡维护" 操作)
    // 最后，我们总结一下上述两种情况下可能导致的 "不平衡情况"
    // 观察到这样的事实：因为我们一次只添加或删除一个元素，那么无非下面几种不平衡情况：
    // 1) 大顶堆比小顶堆多了两个元素 (由大顶堆添加一个新元素，或者小顶堆删除一个元素导致)
    // 2) 大顶堆比小顶堆少了一个元素 (由小顶堆添加一个新元素，或者大顶堆删除一个元素导致)
    // 那么我们只需要考虑上面两种情况下如何进行维护即可
    // 情况1) 此时我们只需要把大顶堆堆顶的元素挪到小顶堆中即可
    // 情况2) 此时我们只需要把小顶堆堆顶的元素挪到大顶堆中即可
    // 这样，基本的模块我们就思考完毕了，剩下的就是具体的实现
    // 一步一步来：
    // 首先，我们需要两个整型变量，countMin 和 countMax，分别记录两侧堆中有效元素的数目，也是两个堆实际拥有的元素数目
    int countMin = 0, countMax = 0;
    // 之后，初始化两个优先队列，一个大顶堆，一个小顶堆
    priority_queue<int, vector<int>, less<int>> bigQ;
    priority_queue<int, vector<int>, greater<int>> smallQ;
    // 最后是一个哈希表 mapping，用来记录所有元素 "欠债"，也就是应该被删除的次数 (当它们变成任意一个堆堆顶元素的时候)
    unordered_map<int, int> mapping;
    // 需要的变量声明完毕，剩下的就是方法函数了
    // 根据下面需要的操作，我们这里定义一个 prune() 函数和一个 makeBalance() 函数
    function<void()> prune = [&]()
    {
        // 分别对 bigQ 和 smallQ 的顶部元素进行检查，有可能的时候进行删除
        // bigQ:
        while(!bigQ.empty())
        {
            int num = bigQ.top();
            if(mapping.count(num))
            {
                // 可能且有必要，那么我们进行删除
                if(--mapping[num] == 0)
                {
                    mapping.erase(num);
                }
                // 删除
                bigQ.pop();
            }
            // 否则，没法删除，退出循环
            else
            {
                break;
            }
        }
        // smallQ:
        while(!smallQ.empty())
        {
            int num = smallQ.top();
            if(mapping.count(num))
            {
                // 可能且有必要，那么我们进行删除
                if(--mapping[num] == 0)
                {
                    mapping.erase(num);
                }
                // 删除
                smallQ.pop();
            }
            // 否则，退出循环
            else
            {
                break;
            }
        }
    };
    // makeBalance() 函数
    function<void()> makeBalance = [&]()
    {
        // 通过 countMin 和 countMax 之间的关系来决定要怎样维护平衡
        // 1. countMin 比 countMax 大 2
        if(countMin > countMax+1)
        {
            smallQ.push(bigQ.top());
            bigQ.pop();
            --countMin;
            ++countMax;
            // 堆顶元素发生了变化，我们进行 prune() 操作
            prune();
        }
        // 2. countMin 比 countMax 小 1
        else if(countMin < countMax)
        {
            bigQ.push(smallQ.top());
            smallQ.pop();
            --countMax;
            ++countMin;
            prune();
        }
    };
    // 首先实现一个 getMedian() 函数，基于基本的假设以及 k 值，我们获取当前窗口的中位数
    // 注意中位数有可能含有小数部分
    function<double()> getMedian = [&]() -> double 
    {
        // k 是奇数，返回 (double)bigQ.top(), 否则返回 (double(bigQ.top())+smallQ.top())>>1
        return k % 2 ? (double)bigQ.top() : (((double)(bigQ.top())+smallQ.top()) / 2);
    };
    // 之后是实现 insert 函数和 erase 函数，分别用于向结构中添加一个新元素和删除一个旧元素
    // 添加 nums[i] 元素
    function<void(int)> insert = [&](int i) 
    {
        // 如果 nums[i] <= bigQ.top()，那么把 nums[i] 添加到 bigQ 中，否则添加到 smallQ 中
        if(bigQ.empty() || nums[i] <= bigQ.top())
        {
            // countMin 记录的是左半的有效元素个数，所以这里加一
            ++countMin;
            bigQ.push(nums[i]);
        }
        else
        {
            // countMax 记录的是右半的有效元素个数，所以这里加一
            ++countMax;
            smallQ.push(nums[i]);
        }
        // 之后如我们上面所说，可能会出现不平衡的情况，我们假设已经定义了一个 makeBalance 函数来对结构进行平衡操作
        makeBalance();
    };  
    // 删除 nums[j] 元素
    function<void(int)> erase = [&](int j)
    {
        // 如果这个元素是两个堆中任意一个堆顶部的元素，那么直接进行删除即可，否则需要在 mapping 表中记录后进行懒删除
        if(bigQ.top() == nums[j])
        {
            // countMin 记录的是左半的有效元素个数，所以这里减一
            --countMin;
            bigQ.pop();
            // 删除了这一个顶部元素，我们可以进行一轮 prune()，尝试删掉一些之前的懒信息
            prune();
        }
        else if(smallQ.top() == nums[j])
        {
            // countMax 记录的是右半的有效元素个数，所以这里减一
            --countMax;
            smallQ.pop();
            prune();
        }
        else
        {
            // 没有堆顶的元素是 nums[j]，那么我们需要进行懒标记
            // 给对应元素的 "待删除" 次数加一
            ++mapping[nums[j]];
            // 注意，由于我们是精神上对 nums[j] 进行了删除，但是现在还没有体现在 countMin 或者 countMax 上
            // 所以我们根据 nums[j] 和 bigQ.top(), smallQ.top() 的关系来进行相应的修改
            // 1. nums[j] < bigQ.top()
            // 此时需要对 countMin 减一
            if(nums[j] < bigQ.top())
            {
                --countMin;
            }
            // 2. nums[j] > smallQ.top()
            // 此时需要对 countMax 减一
            if(nums[j] > smallQ.top())
            {
                --countMax;
            }
            // 实际上，必须为 1，2 两种情况中的一种，这是由结构本身的定义决定的
            // bigQ.top() 和 smallQ.top() 这两个元素一定是数值上相邻的
            // 这里不需要 prune()，因为我们的假设中，执行删除操作前，堆顶部的元素都是有效的，这一点和获取中位数时的假设是统一的
        }
        // 依然需要进行平衡操作
        makeBalance();
    };
    // 写到这里，我们不难发现，还少了一样东西：对元素实际的删除操作，我们可以把这个操作使用在每次获取中位数的函数中，也可以分别使用在添加和删除元素的操作
    // 我们这里使用添加和删除之前进行维护，假设这个函数声明为 prune()

    // 上面的方法全部定义完成，最后剩下的就是实现基本逻辑了
    // 第一步：初始化窗口，我们把前 k 个元素全部添加到 bigQ 中，之后从 bigQ 中弹出 k/2 次顶部元素放到 smallQ 中，之后就是中位数求解+窗口滚动了
    for(int i = 0; i < k; ++i)
    {
        bigQ.push(nums[i]);
    }
    for(int i = 0; i < k/2; ++i)
    {
        smallQ.push(bigQ.top());
        bigQ.pop();
    }
    vector<double> res;
    // 定义 i 为当前窗口的结尾下标
    int i = k-1;
    while(i < n)
    {
        // 获取当前窗口的中位数
        res.push_back(getMedian());
        // 滚动窗口，并修改 i 值
        ++i;
        if(i < n)
        {
            insert(i);
            erase(i-k);
        }
    }
    return res;
}