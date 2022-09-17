#include <iostream>
#include <list>
#include <map>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/lru-cache/
#if 0  // 使用内部数据结构
class LRUCache {
public:
    LRUCache(int capacity) {
        size = 0;
        this->capacity = capacity;
        chain = {};
        cache = {};
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;
        auto node = cache[key];
        int result = (*node).second;
        chain.splice(chain.begin(), chain, node);
        return result;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {  // 已经存在，更新值并移动至chain头节点
            auto node = cache[key];
            chain.erase(node);
            cache.erase(key);
            chain.push_front({key, value});
            cache[key] = chain.begin();
        } else {  // 不存在，chain是否满，如果满，则先移除在添加，否则直接添加
            if (size < capacity) {  // 直接添加
                chain.push_front({key, value});
                cache[key] = chain.begin();
                size++;
            } else {
                auto node = chain.back();
                cache.erase(node.first);
                chain.pop_back();
                chain.push_front({key, value});
                cache[key] = chain.begin();
            }
        }
    }

private:
    list<pair<int, int>> chain;
    map<int, list<pair<int, int>>::iterator> cache;
    int size;
    int capacity;
};

#endif

#if 1  // 自定义双向链表

struct BiListNode {
    int key;
    int val;
    BiListNode* prev;
    BiListNode* next;

    BiListNode() : key(-1), val(-1), prev(nullptr), next(nullptr) {}

    BiListNode(int _key, int _val) : key(_key), val(_val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        head = new BiListNode();
        tail = new BiListNode();
        head->next = tail;
        tail->prev = head;
    }

    LRUCache& operator=(LRUCache& rhs) = delete;

    ~LRUCache() {
        BiListNode* cur = head;
        while (cur != nullptr) {
            BiListNode* del = cur;
            cur = cur->next;
            delete del;
            del = nullptr;
        }
    }

    int get(int key) {
        auto iter = cache.find(key);
        if (iter == cache.end()) {
            return -1;
        }

        BiListNode* node = iter->second;
        moveIntoHead(node);
        return node->val;
    }

    void put(int key, int value) {
        auto iter = cache.find(key);

        if (iter != cache.end()) {
            BiListNode* node = iter->second;
            node->val = value;
            moveIntoHead(node);
        } else {
            if (size < capacity) {
                ++size;
            } else {
                removeTail();
            }
            insertIntoHead(key, value);
        }
    }

private:
    // 要保证存在节点，才能删除
    bool removeTail() {
        BiListNode* del = tail->prev;
        if (del == head) {  // 保证在没有节点的情况下删除
            return false;
        }

        del->prev->next = tail;
        tail->prev = del->prev;

        cache.erase(del->key);
        delete del;
        del = nullptr;
        return true;
    }

    // 将已有的节点移至头部
    void moveIntoHead(BiListNode* node) {
        // 先将原先的节点调整
        node->prev->next = node->next;
        node->next->prev = node->prev;

        // 移到头节点
        node->next = head->next;
        node->next->prev = node;
        node->prev = head;
        head->next = node;
    }

    // 新节点插入
    void insertIntoHead(int key, int val) {
        BiListNode* node = new BiListNode(key, val);

        node->next = head->next;
        node->next->prev = node;
        node->prev = head;
        head->next = node;

        cache[key] = node;
    }

private:
    int capacity;
    int size;
    BiListNode* head = nullptr;
    BiListNode* tail = nullptr;
    map<int, BiListNode*> cache = {};
};

#endif

int main(int argc, char* argv[]) {
    LRUCache lru = LRUCache(2);
    lru.put(1, 1);
    lru.put(2, 2);
    assert(lru.get(1) == 1);
    lru.put(3, 3);
    assert(lru.get(2) == -1);
    lru.put(4, 4);
    assert(lru.get(1) == -1);
    assert(lru.get(3) == 3);
    assert(lru.get(4) == 4);

    LRUCache lru2 = LRUCache(2);
    lru2.put(2, 1);
    lru2.put(1, 1);
    lru2.put(2, 3);
    lru2.put(4, 1);
    assert(lru2.get(1) == -1);
    assert(lru2.get(2) == 3);

    return 0;
}