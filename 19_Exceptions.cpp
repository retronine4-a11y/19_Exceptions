
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    List() : head(nullptr), tail(nullptr), count(0) {}

    ~List()
    {
        Clear();
    }

    List(const List& other) : head(nullptr), tail(nullptr), count(0)
    {
        Node* current = other.head;

        while (current != nullptr)
        {
            AddToTail(current->data);
            current = current->next;
        }
    }

    void AddToHead(T value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        count++;
    }

    void AddToTail(T value)
    {
        Node* newNode = new Node(value);

        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        count++;
    }

    void DeleteFromHead()
    {
        if (head == nullptr)
            throw underflow_error("List is empty!");

        Node* temp = head;
        head = head->next;

        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;

        delete temp;
        count--;
    }

    void DeleteFromTail()
    {
        if (tail == nullptr)
            throw underflow_error("List is empty!");

        Node* temp = tail;
        tail = tail->prev;

        if (tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;

        delete temp;
        count--;
    }

    void AddByPosition(T value, int position)
    {
        if (position < 0 || position > count)
            throw out_of_range("Invalid position!");

        if (position == 0)
        {
            AddToHead(value);
            return;
        }

        if (position == count)
        {
            AddToTail(value);
            return;
        }

        Node* current = head;

        for (int i = 0; i < position; i++)
            current = current->next;

        Node* newNode = new Node(value);

        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;

        count++;
    }

    void DeleteByPosition(int position)
    {
        if (head == nullptr)
            throw underflow_error("List is empty!");

        if (position < 0 || position >= count)
            throw out_of_range("Invalid position!");

        if (position == 0)
        {
            DeleteFromHead();
            return;
        }

        if (position == count - 1)
        {
            DeleteFromTail();
            return;
        }

        Node* current = head;

        for (int i = 0; i < position; i++)
            current = current->next;

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        count--;
    }

    T GetByPosition(int position) const
    {
        if (head == nullptr)
            throw underflow_error("List is empty!");

        if (position < 0 || position >= count)
            throw out_of_range("Invalid position!");

        Node* current = head;

        for (int i = 0; i < position; i++)
            current = current->next;

        return current->data;
    }

    int GetCount() const
    {
        return count;
    }

    bool IsEmpty() const
    {
        return count == 0;
    }

    void Clear()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        count = 0;
    }

    void Print() const
    {
        if (head == nullptr)
            throw underflow_error("List is empty!");

        Node* current = head;

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }
};

int main()
{
    List<int> list;

    try
    {
        list.AddToTail(10);
        list.AddToTail(20);
        list.AddToTail(30);
        list.AddToHead(5);

        cout << "List: ";
        list.Print();

        cout << "Element at position 2: ";
        cout << list.GetByPosition(2) << endl;

        list.AddByPosition(15, 2);

        cout << "After adding: ";
        list.Print();

        list.DeleteByPosition(1);

        cout << "After deleting: ";
        list.Print();

        cout << "Count: " << list.GetCount() << endl;

        list.DeleteFromHead();
        list.DeleteFromTail();

        cout << "Final list: ";
        list.Print();
    }
    catch (const exception& e)
    {
        cout << "Exception: " << e.what() << endl;
    }
}
