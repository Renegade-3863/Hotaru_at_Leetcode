#include "Solution.h"

string Leetcode601_700::Soltuion::nextClosestTime(string time)
{
    // 具体题目具体分析
    // 最笨的办法：我们可以从 time+1 时刻开始，不断向后遍历每一个时刻，直到这个时刻可以用 time 中的数据组合出来为止
    // 那么我们就需要一个函数来判断一个数字是否可以用 time 中的数据通过重复来构成
    // elems 存储 time 中所有的数据
    unordered_set<int> elems;
    for(const auto& elem : time)
    {
        // unordered_set 自带去重功能
        if(elem != ':')
        {
            elems.insert(elem);
        }
    }
    function<bool(string&)> composable = [&](string board) -> bool
    {
        // 检查 board 中的每一个元素是否都存在于 elems 中
        for(const auto& elem : board)
        {
            if(elem != ':' && elems.count(elem) == 0)
            {
                return false;
            }
        }
        return true;
    };
    // 还需要一个对一个时间字符串进行递增的函数，我们来简单写一下
    // 这里我们假设 cur 总满足 "HH:MM" 的格式
    function<void(string&)> increment = [&](string& cur) 
    {
        // 第一步：对分钟部分加一
        int minute = stoi(cur.substr(3, 2));
        int hour = stoi(cur.substr(0, 2));
        if(++minute == 60)
        {
            // 如果加一后，组合出来一个 60 min，那么我们就需要进一位
            minute = 0;
            // 我们同样需要逢 24 进一
            if(++hour == 24)
            {
                hour = 0;
            }
        }
        if(minute == 0)
        {
            cur[3] = '0';
            cur[4] = '0';
        }
        else
        {
            cur[3] = '0'+minute/10;
            cur[4] = '0'+minute%10;
        }
        if(hour == 0)
        {
            cur[0] = '0';
            cur[1] = '0';
        }
        else
        {
            cur[0] = '0'+hour/10;
            cur[1] = '0'+hour%10;
        }
    };
    // 函数编写完成，剩下的就是调用处理数据了
    increment(time);
    while(!composable(time))
    {
        // cout << time << endl;
        increment(time);
    }
    return time;
}