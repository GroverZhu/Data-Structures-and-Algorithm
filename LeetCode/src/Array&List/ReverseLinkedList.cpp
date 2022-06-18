#include <iostream>
#include <vector>

#include <cassert>

#include "List/ListNode.h"

using namespace std;

// https://leetcode-cn.com/problems/reverse-linked-list/

ListNode* reverseList(ListNode* head) {
#if 0
    // 迭代
    if (!head || !head->next) return head;

    ListNode* prev = nullptr;
    ListNode* cur = head;
    ListNode* next;

    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
#endif

#if 1
    // 递归
    if (!head || !head->next) return head;
    auto last = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return last;

#endif
}

// https://leetcode-cn.com/problems/swap-nodes-in-pairs/

ListNode* swapPair(ListNode* head) {
    if (!head || !head->next) return head;

    auto next = swapPair(head->next->next);

    auto first = head;
    auto second = head->next;
    second->next = first;
    first->next = next;

    return second;
}

// https://leetcode-cn.com/problems/reverse-nodes-in-k-group/

// [begin, end)
ListNode* reverseList(ListNode* begin, ListNode* end) {
    ListNode* cur = begin;
    ListNode* prev = nullptr;
    ListNode* next = nullptr;

    while (cur != end) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || !head->next || k == 1) return head;

    auto begin = head;
    auto end = begin;

    for (int i = 0; i < k; i++) {
        if (!end) return begin;
        end = end->next;
    }

    auto next = reverseKGroup(end, k);

    auto left = reverseList(begin, end);
    auto right = begin;
    right->next = next;

    return left;
}

int main(int argc, char* argv[]) {
    vector<int> nums = {1, 2, 3, 4, 5};
    vector<int> ans = {5, 4, 3, 2, 1};
    auto head = buildList(nums).first;
    head = reverseList(head);
    auto cur = head;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(num == cur->val);
        cur = cur->next;
    }
    destoryList(head);

    nums = {1, 2};
    ans = {2, 1};
    head = buildList(nums).first;
    head = reverseList(head);
    cur = head;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(num == cur->val);
        cur = cur->next;
    }
    destoryList(head);

    // swap pairs
    nums = {1, 2, 3, 4};
    ans = {2, 1, 4, 3};
    head = buildList(nums).first;
    head = swapPair(head);
    cur = head;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(num == cur->val);
        cur = cur->next;
    }
    destoryList(head);

    // reverse k group
    nums = {1, 2, 3, 4, 5};
    ans = {2, 1, 4, 3, 5};
    int k = 2;
    head = buildList(nums).first;
    head = reverseKGroup(head, k);
    cur = head;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(num == cur->val);
        cur = cur->next;
    }
    destoryList(head);

    nums = {1, 2, 3, 4, 5};
    ans = {3, 2, 1, 4, 5};
    k = 3;
    head = buildList(nums).first;
    head = reverseKGroup(head, k);
    cur = head;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(num == cur->val);
        cur = cur->next;
    }
    destoryList(head);

    return 0;
}