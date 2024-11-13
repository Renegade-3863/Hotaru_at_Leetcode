#include "Solution.h"

// 这题一看就是数学/找规律题。。比较计算机的解法也是线段树/扫描线，而且本题用这种高级数据结构感觉有点弄巧成拙。。反而变麻烦了
// 不难发现，要是想一堆小矩形能够完美覆盖一个大的矩形，那么必然要求所有小矩形的面积和等于它们所有顶点中筛选出来的最靠外侧的那四个顶点圈出来的大矩形的面积
// 之后，分析一些规律
// 不难发现，如果是严丝合缝的构成矩形，那么这个拼出来的矩形最后会有以下两类结点：
// 1. 大矩形的四角顶点，这些顶点只能出现一次，否则就是出现了重叠
// 2. 内部的贴合顶点，这些顶点要么出现两次，要么出现四次，不可能出现一次或三次
// 性质1很好理解
// 性质2需要一些思考：为什么不能出现一次或三次？
// 假设有一个内部结点出现了一次，那么这个点只有两种可能
// 2.1 这个点在某个小矩形内部，此时很明显重叠了
// 2.2 这个点不在任何一个小矩形内部，但这又是个 "内部结点" 那么此时很明显不满足 "小矩形面积之和等于大矩形" 的条件
// 综上，不可能出现一次
// 假设有一个内部结点出现了三次，那么不难想象这三个点一定是由三个矩形贡献的，并且三个矩形分别占据三个90度
// 那么一定会剩一个90度没人占，此时这个矩形就缺了一角
// 任何一个内部结点都不应该缺角，不是吗？
// 而对于出现多于四次的情况，更明显的重叠，因为一个顶点最多只能有四个90度分别被四个矩形占据，多出来的顶点一定会重叠
// 综上，性质得证
typedef pair<int, int> Point;
bool Leetcode301_400::Solution::isRectangleCover(vector<vector<int>>& rectangles)
{
        long area = 0;
        int minX = rectangles[0][0], minY = rectangles[0][1], maxX = rectangles[0][2], maxY = rectangles[0][3];
        map<Point, int> cnt;
        for (auto & rect : rectangles) {
            int x = rect[0], y = rect[1], a = rect[2], b = rect[3];
            area += (long) (a - x) * (b - y);

            minX = min(minX, x);
            minY = min(minY, y);
            maxX = max(maxX, a);
            maxY = max(maxY, b);

            Point point1({x, y});
            Point point2({x, b});
            Point point3({a, y});
            Point point4({a, b});

            cnt[point1] += 1;
            cnt[point2] += 1;
            cnt[point3] += 1;
            cnt[point4] += 1;
        }

        Point pointMinMin({minX, minY});
        Point pointMinMax({minX, maxY});
        Point pointMaxMin({maxX, minY});
        Point pointMaxMax({maxX, maxY});
        if (area != (long long) (maxX - minX) * (maxY - minY) || !cnt.count(pointMinMin) || !cnt.count(pointMinMax) || !cnt.count(pointMaxMin) || !cnt.count(pointMaxMax)) {
            return false;
        }

        cnt.erase(pointMinMin);
        cnt.erase(pointMinMax);
        cnt.erase(pointMaxMin);
        cnt.erase(pointMaxMax);

        for (auto & entry : cnt) {
            int value = entry.second;
            if (value != 2 && value != 4) {
                return false;
            }
        }
        return true;
}