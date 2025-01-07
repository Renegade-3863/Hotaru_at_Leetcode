#include "Solution.h"

int Leetcode401_500::Soltuion::isConvex(vector<vector<int>>& points)
{
    // 依然是数学题，验证一组点构成的多边形是否为凸多边形的方法是：
    // 计算每对相邻边的叉积，如果所有叉积都是同号的，那么这个多边形是凸多边形，否则是凹多边形
    // 至于两个向量的方向，我们采用 "同向法"，即从一个起点，向后按顺序延续两个结点形成的两条向量进行叉乘，检查两个向量形成的夹角是锐角还是钝角
    // 假设我们知道两个向量：a = <x1, y1, z1>, b = <x2, y2, z2>，那么两个向量叉积就是：
    /*
        | i  j  k  |
        | x1 y1 z1 |
        | x2 y2 z2 |
        = (y1z2-y2z1)i - (x1z2-x2z1)j + (x1y2-x2y1)k
        本题的两个向量都是二维的，那么可以当作是 z1 == 0, z2 == 0
        也就是 (0, 0, x1y2-x2y1)
        所以我们只需要考虑 x1y2-x2y1 的正负即可
        因为 a x b (叉积) = |a|*|b|*sin<a, b>
        那么 x1y2-x2y1 如果为正，那么说明 sin<a, b> 为正，也就是向量 a 到向量 b 是逆时针变换
        反之为顺时针变换
        只有所有变换方式均相同的多边形才是凸多边形
        这个结论稍微画一画图就明白了        
    */
    // 剩下的就是写代码遍历+计算了
    int n = points.size();
    // 这下 vector 类型终于回归原本的翻译了，代表的是真正的二维向量
    // 第一个向量
    vector<int> firstVector(2);
    // 第二个向量
    vector<int> secondVector(2);
    // 存储上面提到的 x1y2-x2y1，所有的 product 必须是同号的
    firstVector[0] = points[1][0]-points[0][0];
    firstVector[1] = points[1][1]-points[0][1];
    secondVector[0] = points[2][0]-points[1][0];
    secondVector[1] = points[2][1]-points[1][1];
    int product = firstVector[0]*secondVector[1]-secondVector[0]*firstVector[1];
    // 遍历，以每个顶点作为出发点往后走两步进行计算
    for(int i = 1; i < n; ++i)
    {
        firstVector[0] = points[(i+1)%n][0]-points[i][0];
        firstVector[1] = points[(i+1)%n][1]-points[i][1];
        secondVector[0] = points[(i+2)%n][0]-points[(i+1)%n][0];
        secondVector[1] = points[(i+2)%n][1]-points[(i+1)%n][1];
        // 修改完两个向量值后，就可以执行实际的计算了
        // x1y2-x2y1
        int tmpProduct = firstVector[0]*secondVector[1]-secondVector[0]*firstVector[1];
        // 检查 tmpProduct 和 product 是否同号
        if((long long)tmpProduct*product < 0)
        {   
            // 异号，说明这不是一个凸多边形，返回 false 即可
            return false;
        }
        // 否则，记录当前的 tmpProduct，继续下一轮计算即可
        // 注意：如果某一轮两个向量的叉乘结果是0，说明这两个向量同向，那么之后就会出现问题：后面符号即使发生了变换，也会被这个0给覆盖掉，我们的判断逻辑就会出现问题
        // 所以这里要跳过 tmpProduct 为 0 的情况
        if(tmpProduct != 0)
        {
            product = tmpProduct;
        }
    }   
    return true;
}