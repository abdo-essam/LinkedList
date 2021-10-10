#include<iostream>

using namespace std;

template<typename T>
class doublyLinkedList {
private:

    struct Node {
        T data;
        Node *next;
        Node *previous;
    };

    Node *first;
    Node *last;
    int count;

public:

    class iterator {

    private:

        Node *CurrentNode;

    public:
        Node *getCurrentNode() {
            return CurrentNode;
        }

        void setCurrentNode(Node *currentNode) {
            CurrentNode = currentNode;
        }

        iterator(Node *node) : CurrentNode(node) {}

        int operator*() {
            return CurrentNode->data;
        }

        bool operator==(const iterator &it) {
            return CurrentNode == it.CurrentNode;
        }

        bool operator!=(const iterator &obj) {
            return CurrentNode != obj.CurrentNode;
        }

        // Postfix ++ overload
        iterator operator++(int) {
            iterator obj = CurrentNode;
            CurrentNode = CurrentNode->next;
            return obj;
        }

        // Prefix ++ overload
        iterator &operator++() {
            if (CurrentNode)
                CurrentNode = CurrentNode->next;
            return *this;
        }


        // Postfix -- overload
        iterator operator--(int) {
            iterator obj = CurrentNode;
            CurrentNode = CurrentNode->previous;
            return obj;
        }


        // Prefix ++ overload
        iterator &operator--() {
            if (CurrentNode)
                CurrentNode = CurrentNode->previous;
            return *this;
        }

        iterator &operator=(Node *node) {
            this->CurrentNode = node;
            return *this;
        }

    };




    // Root of LinkedList wrapped in Iterator type
    iterator begin() {
        return iterator(first);
    }

    // End of LInkedList wrapped in Iterator type
    iterator end() {
        return iterator(nullptr);
    }

    doublyLinkedList() {
        first = NULL;
        last = NULL;
        count = 0;
    }

    doublyLinkedList(T data, int size) {

        first = NULL;
        last = NULL;
        count = 0;

        if (size <= 0) {
            cout << "size can't be negative or zero " << endl;
        } else {
            for (int i = 0; i < size; ++i) {
                insertFirst(data);
            }

        }
    }


    bool isEmpty() {
        return (first == NULL);
    }


    void insertLast(T val) {
        Node *newNode = new Node;
        newNode->data = val;
        if (count == 0) {
            first = last = newNode;
            newNode->next = newNode->previous = NULL;
        } else {
            newNode->next = NULL;
            newNode->previous = last;
            last->next = newNode;
            last = newNode;
        }
        count++;
    }


    void insertFirst(T data) {
        Node *newNode = new Node;
        newNode->data = data;
        if (count == 0) {
            first = last = newNode;
            newNode->next = newNode->previous = NULL;
        } else {

            newNode->next = first;
            newNode->previous = NULL;

            first->previous = newNode;
            first = newNode;
        }
        count++;
    }

    void insert(T data, iterator position) {
        Node *newNode = new Node;
        newNode->data = data;
        if (position == nullptr) {
            insertLast(data);
        } else if (position == first) {
            insertFirst(data);
        } else {
            Node *current = position.getCurrentNode()->previous;

            newNode->next = current->next;
            newNode->previous = current;
            current->next->previous = newNode;
            current->next = newNode;

            count++;
        }

    }

    void insert(T data, int position) {
        if (position < 0 || position > count)
            cout << "Out Of Range ...!" << endl;
        else {
            Node *newNode = new Node;
            newNode->data = data;
            if (position == 0)
                insertFirst(data);
            else if (position == count)
                insertLast(data);
            else {
                Node *current = first;
                for (int i = 1; i < position; i++) {
                    current = current->next;
                }

                newNode->next = current->next;
                newNode->previous = current;
                current->next->previous = newNode;
                current->next = newNode;
                count++;
            }

        }
    }


    void removeFirst() {
        if (count == 0)
            cout << "Empty List" << endl;
        else if (count == 1)//first == last
        {
            delete first;
            last = first = NULL;
        } else {
            Node *current = first;
            first = first->next;
            first->previous = NULL;
            delete current;

        }

        count--;
    }


    iterator erase(iterator &position) {

        if (position.getCurrentNode() == nullptr) {
            cout << "can't delete " << endl;
            return nullptr;
        }

        if (position == first) {
            removeFirst();
            position.setCurrentNode(first);
            return first;
        } else if (position == last) {
            removeLast();
            position.setCurrentNode(nullptr);
            cout << "the last " << endl;
            return nullptr;
        } else {

            Node *current = position.getCurrentNode();
            position.setCurrentNode(current->next);

            current->previous->next = current->next;
            current->next->previous = current->previous;

            delete current;
            return position.getCurrentNode();
        }
    }

    void erase(int position) {
        if (position < 0 || position >= count) {
            cout << "Out Of Range" << endl;
            return;
        } else if (position == 0) {
            removeFirst();
        } else if (position == count - 1) {
            removeLast();
        } else {
            Node *current = first->next;


            for (int i = 1; i < position; i++) {
                current = current->next;
            }
            current->previous->next = current->next;
            current->next->previous = current->previous;
            delete current;
        }
        count--;
    }


    void removeLast() {
        if (count == 0)
            cout << "Empty List" << endl;
        else if (count == 1) {
            delete first;
            //		delete last;
            last = first = NULL;
            count--;
        } else {
            Node *current = last;
            last = last->previous;
            last->next = NULL;
            delete current;
            count--;
        }
    }


    void remove(T data) {
        if (isEmpty()) {
            cout << "Empty List Can't Remove ";
            return;
        }
        Node *current = first->next;

        if (first->data == data)//delete the first element, special case
        {
            removeFirst();
            return;
        } else {
            while (current != NULL)//current->data!=element
            {
                if (current->data == data)
                    break;
                current = current->next;
            }

            if (current == NULL) {
                cout << "The data is not there\n";
                return;
            } else if (current->next == NULL) {
                removeLast();
                return;
            } else {
                current->previous->next = current->next;
                current->next->previous = current->previous;
                delete current;
                count--;
            }

        }

    }

    void display() {
        if (isEmpty()) {
            cout << "Empty List Can't Display...!";
        } else {
            Node *temp = first;
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
        cout << endl;

    }

    void reverse_display() {
        if (isEmpty()) {
            cout << "Empty List Can't Display Reverse...!";
        } else {
            Node *temp = last;
            while (temp != NULL) {
                cout << temp->data << " ";
                temp = temp->previous;
            }
        }

    }

    int size() {
        return count;
    }


    doublyLinkedList<T> & operator= (doublyLinkedList<T> another_list) {

        doublyLinkedList<T>::iterator it = another_list.begin();
        for (int i = 0 ; i < another_list.size() ; ++i) {
            insert(*it ,i);
            it++ ;
        }

        return *this;
    }



    doublyLinkedList::~doublyLinkedList() {
        Node *temp;
        while (first != NULL) {
            temp = first;
            first = first->next;
            delete temp;
        }

        last = NULL ;
        count = 0;
    }
};

int main() {

    doublyLinkedList<int> List ,List2;

    List.insertFirst(1);
    List.insertLast(2);
    List.insertLast(3);
    List.insertLast(4);
    List.insertLast(5);
    List.insertLast(6);

    List2 = List;

    for (doublyLinkedList<int>::iterator iterator = List.begin();
         iterator != List.end(); iterator++) {
        cout << *iterator << " -> ";
    }

    cout << "null";
    cout <<endl;
    cout << "-------------------------------------" <<endl;

    for (doublyLinkedList<int>::iterator iterator = List2.begin();
         iterator != List2.end(); iterator++) {
        cout << *iterator << " -> ";
    }

    cout << "null";

}