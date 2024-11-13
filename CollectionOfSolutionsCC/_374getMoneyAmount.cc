#include "Solution.h"

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

int Leetcode301_400::Solution::guessNumber(int n)
{
    // 轻松愉快的二分题目
    int left = 0, right = n;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        int res = guess(mid);
        switch (res)
        {
            case -1: 
                // num > pick
                // 需要往左猜
                right = mid-1;
                break;
            case 0:
                // num == pick
                // 猜中了，返回即可
                return mid;
            case 1:
                // num < pick
                // 需要往右猜
                left = mid+1;
                break;
        }
    }
    // 不会执行到这一行
    return -1;
}