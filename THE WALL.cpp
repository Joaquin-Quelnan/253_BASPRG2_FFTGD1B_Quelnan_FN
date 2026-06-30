#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct node
{
    string name;
    node* next;
};

node* list(int count);
node* get2ndtolast(node* head);
node* prev(node* head, node* current);
void chars(node* holder, int count);
node* deletetroop(node* head, node* remove, int& count);

int main()
{
    srand((unsigned)time(nullptr));

    int count;

    cout << "\nNumber of Members: ";
    cin >> count;
    cin.ignore();

    node* head = list(count);

    node* holder = get2ndtolast(head);

    bool clockwise = true;
    int round = 1;

    while (count > 1)
    {
        cout << "Round " << round++ << endl;

        chars(holder, count);

        int roll = rand() % (count * 2) + 1;

        cout << "\nResult: " << endl;
        cout << holder->name << " has drawn " << roll << endl;

        node* remove = holder;

        if (clockwise)
        {
            for (int i = 0; i < roll; i++)
                remove = remove->next;
        }
        else
        {
            for (int i = 0; i < roll; i++)
                remove = prev(head, remove);
        }

        cout << remove->name << " has died" << endl;

        node* nextholder = remove->next;

        head = deletetroop(head, remove, count);

        holder = nextholder;

        clockwise = !clockwise;
    }

    cout << "\nFinal Result:" << endl;
    cout << head->name << " will seek reinforcements." << endl;

    delete head;

    return 0;
}

node* list(int count)
{
    node* head = nullptr;
    node* tail = nullptr;

    for (int i = 1; i <= count; i++)
    {
        node* newnode = new node;

        cout << "Member #" << i << " name?: ";
        getline(cin, newnode->name);

        newnode->next = nullptr;

        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            tail->next = newnode;
            tail = newnode;
        }
    }

    tail->next = head;

    return head;
}

node* get2ndtolast(node* head)
{
    node* temp = head;

    while (temp->next->next != head)
        temp = temp->next;

    return temp;
}

node* prev(node* head, node* current)
{
    node* temp = head;

    while (temp->next != current)
        temp = temp->next;

    return temp;
}

void chars(node* holder, int count)
{
    cout << "\nRemaining Dudes:" << endl;

    node* temp = holder;

    for (int i = 0; i < count; i++)
    {
        cout << temp->name << endl;
        temp = temp->next;
    }
}

node* deletetroop(node* head, node* remove, int& count)
{
    node* previous = prev(head, remove);

    previous->next = remove->next;

    if (head == remove)
        head = remove->next;

    delete remove;

    count--;

    return head;
}