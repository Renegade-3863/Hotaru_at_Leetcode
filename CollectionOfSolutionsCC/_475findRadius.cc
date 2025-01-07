#include "Solution.h"

int Leetcode401_500::Soltuion::findRadius(vector<int>& houses, vector<int>& heaters)
{
    // 不难的二分暴力搜索题，我们只需要二分半径即可
    // 我们定义最后的答案半径范围为，最小为 0，最大设定为一个较大值，这里设为 1e9-1
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());
    int right = 1e9-1;
    int left = 0;
    // 定义好左右边界后，我们就可以二分这个区间
    // 假设现在我们考虑的中点半径为 mid
    // 那么如果 mid 不能覆盖所有的房屋，那么说明 [left, mid] 中所有的半径就都不可行了
    // 如果 mid 可以覆盖所有的房屋，那么说明 [mid, right] 中所有的半径就都可行了，但是我们要的是最短半径，所以仍然需要进一步二分左侧区间
    // 最后剩下的就是找出一个判断 mid 是否能够覆盖所有房屋的算法了
    // 我们封装一下这个子过程
    function<bool(int)> coverable = [&](int mid) -> bool
    {
        // 给定一组供暖器的位置，以及对应的辐射半径 mid，如何判断它们是否能够覆盖所有的 house ？
        // 我们可以拿两个指针来分别进行遍历，按照下面的逻辑来挪动指针
        // house 指向从左到右第一个还未被判定为 "可被辐射到" 的房屋
        // heater 指向从左到右第一个还未超出辐射范围的供暖器的下标
        // 当 house 指向的房屋被计算得到 "可被辐射到"，那么就右移 house
        // 当 heater 辐射不到 house 的时候，就右移 heater 指针即可
        // 所有循环结束于 heater == heaters.size()，或者 house == houses.size()，或者 house 无法被任何一个 heater 辐射到
        // 后者的判断条件比较特殊，可以把这个条件放到循环体内进行判断
        int house = 0, heater = 0;
        while(heater < heaters.size() && house < houses.size())
        {
            // 检查当前 heater
            // [heaters[heater]-mid, heaters[heater]+mid] 为这个供暖器可以覆盖到的范围
            // 如果 house 属于 [heaters[heater]-mid, heaters[heater]+mid] 的范围，那么我们可以右移 house 指针
            // heaters[heater]-mid <= houses[house] <= heaters[heater]+mid
            if(heaters[heater]-mid <= houses[house] && houses[house]-mid <= heaters[heater])
            {
                // 右移 house
                ++house;
            }
            // 其它情况
            // house < heater-mid 或者 house > heater+mid
            // 左边，我们直接退出即可，这个半径不可行
            else if(houses[house] < heaters[heater]-mid)
            {
                // 可以直接返回 false
                return false;
            }
            // house > heater+mid，那么这个供暖器已经可以结束检查了，我们继续检查下一个供暖器
            else
            {
                ++heater;
            }
        }
        // 返回 true 的唯一情况是：house == houses.size()，也就是说所有的房屋都被成功辐射到了
        return house == houses.size();
    };  
    // 我们利用上面写好的判断逻辑即可完成本题的二分
    // res 记录最终的结果，初始化为 right
    int res = right;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        if(coverable(mid))
        {
            // 可以覆盖，我们记录这个半径，修改 right，继续二分
            res = mid;
            right = mid-1;
        }
        else
        {
            // 不可以覆盖，我们修改 left，继续二分
            left = mid+1;
        }
    }
    // 结束检查，返回结果即可
    return res;
}