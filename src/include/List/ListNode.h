#ifndef __ListNode__
#define __ListNode__

#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

// [begin, end]
std::pair<ListNode*, ListNode*> buildList(std::vector<int>& nums) {
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

void clearCycle(ListNode* cycleEnd) { cycleEnd->next = nullptr; }

void destoryList(ListNode* head) {
    auto cur = head;
    while (cur) {
        auto del = cur;
        cur = cur->next;
        delete del;
        del = nullptr;
    }
}

#endif