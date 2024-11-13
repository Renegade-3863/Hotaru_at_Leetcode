/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

// 数据结构题，我们在真正开始写代码之前，先要考虑实现思路
// 题目没有补充要求修改这个传入的嵌套列表，那么我们可以考虑在初始化阶段就把这整个列表完全展开压扁，这样后面的数据操作都会很简单
// 别忘了初始化指针
Leetcode301_400::Solution::NestedIterator::NestedIterator(vector<NestedInteger>& nestedList) : idx(0)
{
    // 这个函数中，我们会需要进行递归的数据处理
    // 定义一个递归函数，用于往 this->memo 中填充一个 NestedInteger 元素
    function<void(const NestedInteger&)> insert = [&](const NestedInteger& nestedInteger)
    {
        // 填充思路也很简单，我们先检查这个东西是不是一个一般的整数
        if(nestedInteger.isInteger())
        {
            // 如果是一个整数，那么直接添加到 memo 中即可，无需进一步深入递归
            this->memo.push_back(nestedInteger.getInteger());
        }
        // 否则，这是一个嵌套结构，我们需要对它存储到列表进行遍历
        else
        {
            const vector<NestedInteger>& nested = nestedInteger.getList();
            for(const auto& elem : nested)
            {
                insert(elem);
            }
        }
        // 逻辑流结束，返回即可
        return;
    };
    // 之后我们只需要对 nestedList 列表中的每一个元素调用一下这个函数即可
    for(const auto& nestedInteger : nestedList)
    {
        insert(nestedInteger);
    }
    // 构造函数不需要任何返回值
}

// 之后是返回列表中下一个元素的函数
// 我们在初始化函数中已经完成了嵌套列表元素的展开，所以这里可以直接返回保存的数组中的下一个元素
int Leetcode301_400::Solution::NestedIterator::next()
{
    // 直接返回 idx 处元素并更新 idx 值
    return this->memo[idx++];
}   

bool Leetcode301_400::Solution::NestedInteger::hasNext()
{
    // 判断逻辑也非常简单，只需要检查 idx 是否等于 this->memo.size()
    return idx < this->memo.size();
}