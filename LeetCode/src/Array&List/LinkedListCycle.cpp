#include <iostream>
#include <cassert>
#include <vector>

#include "../../include/List/ListNode.h"

using namespace std;


// https://leetcode-cn.com/problems/linked-list-cycle/
bool hasCycle(ListNode* head) {
    if (!head || !head->next) return false;
    auto slow = head;
    auto fast = head;

    do {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    } while (fast && fast->next);

    return false;
}

// https://leetcode-cn.com/problems/linked-list-cycle-ii/
ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;

    auto slow = head;
    auto fast = head;

    do {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    } while (fast && fast->next);

    return nullptr;
}

// 环的个数
int cycleNums(ListNode* head) {
    if (!head || !head->next) return 0;

    auto slow = head;
    auto fast = head;

    do {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            int nums = 0;
            do {
                slow = slow->next;
                ++nums;
            } while (slow != fast);
            return nums;
        }
    } while (fast && fast->next);

    return 0;
}

int main(int argc, char* argv[]) {
    vector<int> nums = {3, 2, 0, -4};
    auto pairs = buildList(nums);
    auto head = pairs.first;
    auto tail = pairs.second;
    makeCycle(head->next, tail);
    assert(hasCycle(head));
    assert(2 == detectCycle(head)->val);
    assert(3 == cycleNums(head));
    clearCycle(tail);
    destoryList(head);

    nums = {1, 2};
    pairs = buildList(nums);
    head = pairs.first;
    tail = pairs.second;
    makeCycle(head, tail);
    assert(hasCycle(head));
    assert(1 == detectCycle(head)->val);
    assert(2 == cycleNums(head));
    clearCycle(tail);
    destoryList(head);


    nums = {1, 2};
    pairs = buildList(nums);
    head = pairs.first;
    tail = pairs.second;
    assert(!hasCycle(head));
    assert(nullptr == detectCycle(head));
    assert(0 == cycleNums(head));
    clearCycle(tail);
    destoryList(head);

    return 0;
}