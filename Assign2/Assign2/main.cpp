#include <iostream>

using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Function to insert at the beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // Function to insert at the end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Function to insert at a given location in the sorted list
    void insertAtLocation(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr || head->data >= val) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data < val) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Function to delete first node
    void deleteFirst() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Function to delete last node
    void deleteLast() {
        if (head == nullptr) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    // Function to delete node at given index in the sorted list
    void deleteAtIndex(int index) {
        if (head == nullptr) return;
        if (index == 0) {
            deleteFirst();
            return;
        }
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < index - 1; ++i) {
            temp = temp->next;
        }
        if (temp == nullptr || temp->next == nullptr) return;
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }

    // Function to split the list into two halves
    pair<LinkedList, LinkedList> frontBackSplit() {
        LinkedList front;
        LinkedList back;
        if (head == nullptr) return { front, back };

        Node* slow = head;
        Node* fast = head->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        front.head = head;
        back.head = slow->next;
        slow->next = nullptr;

        return { front, back };
    }
    void sortList() {
        if (head == nullptr || head->next == nullptr) return;

        Node* current = head;
        Node* index = nullptr;
        int temp;

        while (current != nullptr) {
            index = current->next;

            while (index != nullptr) {
                if (current->data > index->data) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    // Function to merge two lists
    void mergeList(const LinkedList& list1, const LinkedList& list2) {
        Node* ptr1 = list1.head;
        Node* ptr2 = list2.head;

        while (ptr1 != nullptr) {
            insertAtEnd(ptr1->data);
            ptr1 = ptr1->next;
        }

        while (ptr2 != nullptr) {
            insertAtEnd(ptr2->data);
            ptr2 = ptr2->next;
        }
    }

    // Function to print the list
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    // Example usage
    LinkedList list;
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(5);
    list.insertAtEnd(7);
    list.insertAtEnd(11);

    // Insertion
    list.insertAtBeginning(1);
    list.insertAtEnd(13);
    list.insertAtLocation(4);

    // Deletion
    list.deleteFirst();
    list.deleteLast();
    list.deleteAtIndex(2);

    cout << "Original list: ";
    list.printList();

    // Front-back split
    pair<LinkedList, LinkedList> splitResult = list.frontBackSplit();
    LinkedList front = splitResult.first;
    LinkedList back = splitResult.second;
    cout << "Front half: ";
    front.printList();
    cout << "Back half: ";
    back.printList();

    // Merge sorted lists
    LinkedList listA, listB;
    listA.insertAtEnd(1);
    listA.insertAtEnd(2);
    listA.insertAtEnd(7);

    listB.insertAtEnd(2);
    listB.insertAtEnd(3);
    listB.insertAtEnd(6);

    // Sort each list
    listA.sortList();
    listB.sortList();

    cout << "Sorted List A: ";
    listA.printList();
    cout << "Sorted List B: ";
    listB.printList();

    LinkedList mergedList;
    mergedList.mergeList(listA, listB); // Merge listA and listB into mergedList
    cout << "Merged lists: ";
    mergedList.printList();

    return 0;
}
