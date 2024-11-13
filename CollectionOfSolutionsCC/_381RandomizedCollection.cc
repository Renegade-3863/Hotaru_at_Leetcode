#include "Solution.h"

// 本题和上一题没有本质区别，无非就是哈希表保存的映射关系从 "对应的元素下标"
// 变成了 "对应的某种元素的所有下标"

// 我们修改一下上一题的哈希表定义即可，其它的基本没有区别
Leetcode301_400::Solution::RandomizedCollection::RandomizedCollection() {}

Leetcode301_400::Solution::RandomizedCollection::insert(int val)
{
    // 插入操作很简单，本题允许重复，我们只需要直接在 memo 末尾添加一个元素，以及记录对应的下标映射到 remapping 中即可
    bool ret = true;
    if(this->remapping.find(val) != this->remapping.end())
    {
        ret = false;
    }
    this->remapping[val].insert(this->memo.size());
    this->memo.push_back(val);
    return ret;
}

Leetcode301_400::Solution::RandomizedCollection::remove(int val)
{
    // 如果这个元素压根不存在，我们直接返回 false
    if(this->remapping.find(val) == this->remapping.end())
    {
        return false;
    }
    // 删除操作和上一题方法类似，我们把 val 对应的某一个元素和数组结尾的元素互换，并修改对应值的映射集合，最后删掉对应记录即可
    // 首先修改映射记录
    int i = *(this->remapping[val].begin());
    this->memo[i] = this->memo.back();
    this->remapping[val].erase(i);
    this->remapping[this->memo[i]].erase(this->memo.size()-1);
    if(i < this->memo.size()-1)
    {
        this->remapping[this->memo[i]].insert(i);
    }    
    if(this->remapping[val].size() == 0)
    {
        this->remapping.erase(val);
    }
    // 之后进行数组元素交换
    this->memo.pop_back();
    return true;   
}

int Leetcode301_400::Solution::RandomizedCollection::getRandom()
{
    return this->memo[rand()%(this->memo.size())];
}