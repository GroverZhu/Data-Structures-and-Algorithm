#include <cassert>
#include <iostream>
using namespace std;

struct Node {
    int value;
    struct Node* prev;
    struct Node* next;

    Node() {
        value = 0;
        prev = nullptr;
        next = nullptr;
    }

    Node(int val) {
        this->value = val;
        prev = nullptr;
        next = nullptr;
    }

    Node(Node&) = delete;
    Node& operator=(Node& rhs) = delete;
};

// https://leetcode-cn.com/problems/design-circular-deque/
class MyCircularDeque {
public:
    MyCircularDeque(int k) {
        this->size = 0;
        this->capacity = k;
        this->head = new Node();
        this->tail = new Node();

        head->next = tail;
        head->prev = tail;
        tail->next = head;
        tail->prev = head;
    }

    ~MyCircularDeque() {
        Node* cur = head;
        while (cur != tail) {
            auto del = cur;
            cur = cur->next;
            delete del;
            del = nullptr;
        }
        delete tail;
    }

    MyCircularDeque(MyCircularDeque&) = delete;
    MyCircularDeque& operator=(MyCircularDeque& rhs) = delete;

    bool insertFront(int value) {
        if (this->size >= capacity) return false;
        auto add = new Node(value);

        add->next = head->next;
        head->next->prev = add;
        add->prev = head;
        head->next = add;

        ++this->size;

        return true;
    }

    bool insertLast(int value) {
        if (this->size >= this->capacity) return false;

        auto add = new Node(value);

        tail->prev->next = add;
        add->prev = tail->prev;
        add->next = tail;
        tail->prev = add;

        ++this->size;
        return true;
    }

    bool deleteFront() {
        if (this->size <= 0) return false;

        auto del = head->next;
        head->next = del->next;
        del->next->prev = head;
        delete del;
        del = nullptr;

        --this->size;
        return true;
    }

    bool deleteLast() {
        if (this->size <= 0) return false;

        auto del = tail->prev;
        del->prev->next = tail;
        tail->prev = del->prev;
        delete del;
        del = nullptr;

        --this->size;
        return true;
    }

    int getFront() {
        if (this->size <= 0) return -1;
        return this->head->next->value;
    }

    int getRear() {
        if (this->size <= 0) return -1;
        return this->tail->prev->value;
    }

    bool isEmpty() { return this->size <= 0; }

    bool isFull() { return this->size >= this->capacity; }

private:
    int size;
    int capacity;
    Node* head;
    Node* tail;
};

int main(int argc, char* argv[]) {
    MyCircularDeque circularDeque(3);
    assert(true == circularDeque.insertLast(1));
    assert(true == circularDeque.insertLast(2));
    assert(true == circularDeque.insertFront(3));
    assert(false == circularDeque.insertFront(4));
    assert(2 == circularDeque.getRear());
    assert(true == circularDeque.isFull());
    assert(true == circularDeque.deleteLast());
    assert(true == circularDeque.insertFront(4));
    assert(4 == circularDeque.getFront());
}