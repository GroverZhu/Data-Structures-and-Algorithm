#include <iostream>
#include <vector>
#include <cassert>

#include "../include/List/ListNode.h"

using namespace std;

bool isPalindromeRecursive(ListNode* right, ListNode*& left) {
    if (!right) return true;
    bool result = isPalindromeRecursive(right->next, left);
    result = result && (left->val == right->val);
    if (!result) return false;
    left = left->next;
    return result;

}

bool isPalindromeInteration(ListNode* head) {
    if (!head || !head->next) return true;

    auto slow = head;
    auto fast = head;

    do {
        slow = slow->next;
        fast = fast->next->next;
    } while (fast && fast->next);

    if (fast) slow = slow->next;

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
    assert(true == isPalindromeInteration(head));
    destoryList(head);

    nums = {1, 2};
    node = buildList(nums);
    head = node.first;
    assert(false == isPalindrome(head));
    assert(false == isPalindromeInteration(head));
    destoryList(head);

    nums = {1, 2, 1, 2, 1};
    node = buildList(nums);
    head = node.first;
    assert(true == isPalindrome(head));
    assert(true == isPalindromeInteration(head));
    destoryList(head);
    return 0;
}