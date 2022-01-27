#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

#ifndef __ListNode__
#define __ListNode__

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

#endif

// [begin, end]
pair<ListNode*, ListNode*> buildList(vector<int>& nums) {
    ListNode dummy;
    auto cur = &dummy;
    ListNode* node = nullptr;
    for (auto num : nums) {
        node = new ListNode(num);
        cur->next = node;
        cur = cur->next;
    }
    return {dummy.next, node};
}

void makeCycle(ListNode* cycleBegin, ListNode* cycleEnd) {
    if (!cycleBegin || !cycleEnd) return;
    cycleEnd->next = cycleBegin;
}

void clearCycle(ListNode* cycleEnd) {
    cycleEnd->next = nullptr;
}

void destoryList(ListNode* head) {
    auto cur = head;
    while (cur) {
        auto del = cur;
        cur = cur->next;
        delete del;
        del = nullptr;
    }
}

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