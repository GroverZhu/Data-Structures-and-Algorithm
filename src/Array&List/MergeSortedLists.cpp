#include <iostream>
#include <queue>
#include <vector>

#include <cassert>

#include "List/ListNode.h"

using namespace std;

// https://leetcode-cn.com/problems/merge-two-sorted-lists/
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    ListNode dummy;
    auto cur = &dummy;

    while (list1 && list2) {
        if (list1->val < list2->val) {
            cur->next = list1;
            list1 = list1->next;
        } else {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }

    if (list1) cur->next = list1;
    if (list2) cur->next = list2;

    return dummy.next;
}

// https://leetcode-cn.com/problems/merge-k-sorted-lists/
ListNode* mergeKLists(vector<ListNode*>& lists) {
#if 1
    int size = static_cast<int>(lists.size());
    if (size == 0) return nullptr;
    if (size == 1) return lists[0];

    auto cmp = [](const ListNode* lhs, const ListNode* rhs) {
        if (!lhs || !rhs) return false;
        return lhs->val > rhs->val;
    };

    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);

    ListNode dummy;
    auto cur = &dummy;

    for (auto node : lists) {
        if (node) q.push(node);
    }

    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        cur->next = node;
        cur = cur->next;
        if (node->next) {
            q.push(node->next);
        }
    }

    cur->next = nullptr;

    return dummy.next;
#endif

#if 0

    int size = static_cast<int>(lists.size());
    if (size == 0) return nullptr;
    if (size == 1) return lists[0];

    vector<ListNode*> left = vector<ListNode*>(lists.begin(), lists.begin() + (size / 2));
    vector<ListNode*> right = vector<ListNode*>(lists.begin() + (size / 2), lists.end());

    auto leftHead = mergeKLists(left);
    auto rightHead = mergeKLists(right);

    return mergeTwoLists(leftHead, rightHead);

#endif
}

int main(int argc, char* argv[]) {
    vector<int> nums1, nums2, ans;
    nums1 = {1, 2, 4};
    nums2 = {1, 3, 4};
    ans = {1, 1, 2, 3, 4, 4};
    auto list1 = buildList(nums1).first;
    auto list2 = buildList(nums2).first;
    auto merge = mergeTwoLists(list1, list2);
    auto cur = merge;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(cur->val == num);
        cur = cur->next;
    }
    destoryList(merge);

    nums1 = {1, 4, 5};
    nums2 = {1, 3, 4};
    vector<int> nums3 = {2, 6};
    ans = {1, 1, 2, 3, 4, 4, 5, 6};
    list1 = buildList(nums1).first;
    list2 = buildList(nums2).first;
    auto list3 = buildList(nums3).first;
    vector<ListNode*> lists = {list1, list2, list3};
    merge = mergeKLists(lists);
    cur = merge;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(cur->val == num);
        cur = cur->next;
    }
    destoryList(merge);

    return 0;
}