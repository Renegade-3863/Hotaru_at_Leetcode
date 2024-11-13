#include "Solution.h"

struct Point 
{
public:
    Point(int _x, int _y) : x(_x), y(_y) {}
    int x;
    int y;
};
struct hashFunc
{
    size_t operator() (const Point& p) const
    {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};
struct equalFunc 
{
    bool operator() (const Point& a, const Point& b) const
    {
        return a.x == b.x && a.y == b.y;
    }
};
bool Leetcode301_400::Solution::isReflected(vector<vector<int>>& points)
{
    // 数学题，考虑我们是否可以 "猜出来" 这条可能的对称轴，之后再进行验证
    // 首先，我们可以确认下面的事实
    // 这个对称轴如果存在，那么一定是这一组点中 minX 和 maxX 中点对应的那条平行于 Y 轴的直线
    // 除了他没有其它直线可以成为最终结果
    // 其实这个性质对于其它任何内部的点都是成立的，不过不难想到，一旦满足了一对点之间的关系
    // 那么这只能隐含地囊括到那些在这对点内部的点
    // 而外部的点囊括不到
    // 所以我们选择这对横坐标值最大和最小的结点是最合适的
    int minX = INT_MAX, maxX = INT_MIN;
    for(const auto& point : points)
    {
        minX = min(point[0], minX);
        maxX = max(point[0], maxX);
    }
    // 之后我们计算这两个值的中点，就确定了这条唯一可能的直线
    // 之后，我们只需要检查：对于每个结点，points 集合中是否存在这个点关于这条直线对称的结点
    // 这可以通过任何一种合适的索引结构实现：哈希表/红黑树均可
    // 我们采用哈希集合 unordered_set 来实现
    unordered_set<Point, hashFunc, equalFunc> exist;
    for(const auto& point : points)
    {
        exist.emplace(point[0], point[1]);
    }
    // 再遍历一遍，检查对称点是否存在即可
    for(const auto& point : points)
    {
        // (point[0] + x) / 2 == (minX+maxX) / 2
        int mirX = minX+maxX-point[0];
        // 关于一条平行于 y 轴的直线对称，纵坐标应该是不变的
        // 在哈希表中检索即可
        if(exist.find(Point(mirX, point[1])) == exist.end())
        {
            return false;
        }
    }
    return true;
}