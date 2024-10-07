#include "Solution.h"

TwoSum::TwoSum() {}

void TwoSum::add(int number)
{
    // 使用顺序遍历的方式检查 number 应该插入的位置
    // 执行有序插入操作
    int idx = 0;
    while(idx < values.size())
    {
        // 找到第一个大于 number 的元素的下标
        if(values[idx] > number)
        {
            break;
        }
    }
    // 把元素插入对应的位置上
    values.insert(values.begin()+idx, number);
    // 返回即可
    return;
}

bool TwoSum::find(int value)
{
    if(memo.find(value) != memo.end())
    {
        return true;
    }
    // 否则我们只需要进行双指针查找即可
    int left = 0, right = values.size()-1;
    while(left < right)
    {
        if(values[left]+values[right] == value)
        {
            memo[value] = true;
            return true;
        }
        else if(values[left]+values[right] < value)
        {
            ++left;
        }
        else
        {
            --right;
        }
    }
    return false;
}