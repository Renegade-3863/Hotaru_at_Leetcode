#include "Solution.h"

Leetcode701_800::Soltuion::MyCalendarThree::MyCalendarThree()
{
    this->root = buildTree3();
}

int Leetcode701_800::Soltuion::MyCalendarThree::book(int startTime, int endTime)
{
    update(this->root, 0, 1e9+4, startTime, endTime-1, 1);
    return query(this->root, 0, 1e9+4, 0, 1e9+4);
}