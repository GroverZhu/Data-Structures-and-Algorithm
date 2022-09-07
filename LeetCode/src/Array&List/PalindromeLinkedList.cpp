#include <iostream>
#include <vector>

#include <cassert>

#include "List/ListNode.h"

using namespace std;

bool isPalindromeRecursive(ListNode* right, ListNode*& left) {
    if (!right) return true;
    bool result = isPalindromeRecursive(right->next, left);
    result = result && (left->val == right->val);
    if (!result) return false;
    left = left->next;
    return result;
}

// [head, tail)
ListNode* reverse(ListNode* head, ListNode* tail) {
    if (!head || head == tail || head->next == tail) return head;

    ListNode* prev = nullptr;
    ListNode* cur = head;
    ListNode* next;

    while (cur != tail) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

// 采用迭代的方法,会修改链表的结构
bool isPalindromeIteration(ListNode* head) {
    if (!head || !head->next) return true;

    auto slow = head;
    auto fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast) slow = slow->next;

    // 前半段的最后一个指针
    auto reserve = head;
    while (reserve->next != slow) reserve = reserve->next;

    // 反转后半部分链表
    auto cur = slow;
    ListNode* prev = nullptr;
    ListNode* next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    reserve->next = prev;  // 将链表拼接起来，避免内存泄露

    // 比较左右两部分
    auto left = head;
    auto right = prev;

    while (right) {
        if (left->val != right->val) return false;
        left = left->next;
        right = right->next;
    }

    return true;
}

// https://leetcode-cn.com/problems/palindrome-linked-list/
bool isPalindrome(ListNode* head) {
    ListNode* left = head;
    return isPalindromeRecursive(head, left);
}

int main(int argc, char* argv[]) {
    vector<int> nums = {1, 2, 2, 1};
    auto node = buildList(nums);
    auto head = node.first;
    assert(true == isPalindrome(head));
    assert(true == isPalindromeIteration(head));
    destoryList(head);

    nums = {1, 2};
    node = buildList(nums);
    head = node.first;
    // assert(false == isPalindrome(head));
    assert(false == isPalindromeIteration(head));
    destoryList(head);

    nums = {1, 2, 1, 2, 1};
    node = buildList(nums);
    head = node.first;
    // assert(true == isPalindrome(head));
    assert(true == isPalindromeIteration(head));
    destoryList(head);
    return 0;
}