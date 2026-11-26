#include <iostream>

class LinkedList {
    struct Node {
        int value;
        Node* next;
    };

    Node head_{0, nullptr};

    Node* nodeAt(int index) {
        Node* node = &head_;
        while (index-- > 0) node = node->next;
        return node;
    }

public:
    LinkedList() = default;
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    ~LinkedList() {
        while (head_.next != nullptr) {
            Node* removed = head_.next;
            head_.next = removed->next;
            delete removed;
        }
    }

    void initialize(int count) {
        Node* tail = &head_;
        while (count-- > 0) {
            int value;
            std::cin >> value;
            tail->next = new Node{value, nullptr};
            tail = tail->next;
        }
    }

    void insert(int index, int value) {
        Node* previous = nodeAt(index);
        previous->next = new Node{value, previous->next};
    }

    void erase(int index) {
        Node* previous = nodeAt(index - 1);
        Node* removed = previous->next;
        previous->next = removed->next;
        delete removed;
    }

    void swapPairs() {
        Node* previous = &head_;
        while (previous->next != nullptr && previous->next->next != nullptr) {
            Node* first = previous->next;
            Node* second = first->next;
            first->next = second->next;
            second->next = first;
            previous->next = second;
            previous = first;
        }
    }

    void moveBack(int count, int distance) {
        if (count == 0 || distance == 0) return;
        Node* prefixEnd = nodeAt(count);
        Node* destination = prefixEnd;
        for (int step = 0; step < distance; ++step) destination = destination->next;

        // Transform consecutive blocks A, B, C into B, A, C.
        Node* prefixStart = head_.next;
        head_.next = prefixEnd->next;
        prefixEnd->next = destination->next;
        destination->next = prefixStart;
    }

    int query(int index) { return nodeAt(index)->value; }

    void printAll() const {
        for (const Node* node = head_.next; node != nullptr; node = node->next) {
            if (node != head_.next) std::cout << ' ';
            std::cout << node->value;
        }
        std::cout << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;
    LinkedList list;
    list.initialize(n);
    int operations;
    std::cin >> operations;
    while (operations-- > 0) {
        int op, index, value;
        std::cin >> op;
        switch (op) {
            case 1:
                std::cin >> index >> value;
                list.insert(index, value);
                break;
            case 2:
                std::cin >> index;
                list.erase(index);
                break;
            case 3:
                list.swapPairs();
                break;
            case 4:
                std::cin >> index >> value;
                list.moveBack(index, value);
                break;
            case 5:
                std::cin >> index;
                std::cout << list.query(index) << '\n';
                break;
            case 6:
                list.printAll();
                break;
        }
    }
}
