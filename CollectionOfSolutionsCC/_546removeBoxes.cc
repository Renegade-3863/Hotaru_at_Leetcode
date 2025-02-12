#include "Solution.h"

// 没什么营养的一道 DP 困难题，想到了递推方程就很好做，想不到，那就是想不到了。。
// 不多评价，面试要是考这道题，你可以跟面试官说提前结束面试了。。
int Leetcode501_600::Soltuion::removeBoxes(vector<int>& boxes) {
    memset(dp, 0, sizeof dp);
    return calculatePoints(boxes, 0, boxes.size() - 1, 0);
}

int calculatePoints(vector<int>& boxes, int l, int r, int k) {
    if (l > r) {
        return 0;
    }
    if (dp[l][r][k] == 0) {
        dp[l][r][k] = calculatePoints(boxes, l, r - 1, 0) + (k + 1) * (k + 1);
        for (int i = l; i < r; i++) {
            if (boxes[i] == boxes[r]) {
                dp[l][r][k] = max(dp[l][r][k], calculatePoints(boxes, l, i, k + 1) + calculatePoints(boxes, i + 1, r - 1, 0));
            }
        }
    }
    return dp[l][r][k];
}
