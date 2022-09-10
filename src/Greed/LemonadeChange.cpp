#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/lemonade-change/description/
bool lemonadeChange(vector<int>& bills) {
    int five = 0;
    int ten = 0;
    for (auto& bill : bills) {
        if (bill == 5) {
            ++five;
        } else if (bill == 10) {
            if (five <= 0) return false;
            ++ten;
            --five;
        } else if (bill == 20) {
            if (ten > 0 && five > 0) {
                --ten;
                --five;
            } else if (five >= 3) {
                five -= 3;
            } else {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    vector<int> bills;

    bills = {5, 5, 5, 10, 20};
    assert(true == lemonadeChange(bills));

    bills = {5, 5, 10, 10, 20};
    assert(false == lemonadeChange(bills));

    bills = {5, 5, 10};
    assert(true == lemonadeChange(bills));

    bills = {10, 10};
    assert(false == lemonadeChange(bills));

    bills = {5, 5, 10, 20, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10, 5, 5, 20, 5, 20, 5};
    assert(true == lemonadeChange(bills));
    return 0;
}