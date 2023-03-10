#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//Сериализация двусвязного списка с ссылкой на рандомный элемент
//Принимает и отдаёт два файла - один с данными, другой - с индексами рандомных элементов

class ListNode {
public:
    string data;
    ListNode* Prev, * Next, * Rand;

public:
    ListNode(string data) {
        this->data = data;
        this->Prev = this->Next = this->Rand = NULL;
    }
};



class ListRand
{
public:
    ListNode* Head, * Tail;
    int Count;

public:
    ListRand() {
        Head = Tail = NULL;
        Count = 0;
    }

    ListNode* push_front(string data) {
        ListNode* ptr = new ListNode(data);
        ptr->Next = Head;
        if (Head != NULL)
            Head->Prev = ptr;
        if (Tail == NULL)
            Tail = ptr;
        Head = ptr;
        Count += 1;

        return ptr;
    }

    ListNode* push_back(string data) {
        ListNode* ptr = new ListNode(data);
        ptr->Prev = Tail;
        if (Tail != NULL)
            Tail->Next = ptr;
        if (Head == NULL)
            Head = ptr;
        Tail = ptr;
        Count += 1;
        
        return ptr;
    }


    void Serialize(fstream& s, fstream& rand)
    {
        ListNode* tmp = this->Head;
        while (tmp) {
            s << tmp->data << "\n";
            tmp = tmp->Next;
        }

        ListNode* newtmp = this->Head;
        int i = 0, x;
        while (newtmp) {
            x = getIndex(newtmp->Rand);
            rand << x << "\n";
            newtmp = newtmp->Next;
            i++;
        }

    }

    void Deserialize(fstream& s, fstream& rand)
    {
        string line;
        while (getline(s, line)) {
            push_back(line);
        }

        ListNode* tmp = this->Head;
        ListNode* ptr;
        while (getline(rand, line)) {
            ptr = getFromIndex(stoi(line));
            tmp->Rand = ptr;
            tmp = tmp->Next;
        }
    }

    int getIndex(ListNode* node) {

        int i = 0;
        while (node) {
            node = node->Prev;
            i++;
        }

        return i - 1;
    }

    ListNode* getFromIndex(int index) {
        ListNode* node = this->Head;
        while (index > 0) {
            node = node->Next;
            index--;
        }

        return node;
    }
};


/*
int main() {
    fstream s, t, rand1, rand2;
    s.open("FileTest.txt");
    rand1.open("FileRandTest.txt");
    t.open("OutputTest.txt");
    rand2.open("OutputRandTest.txt");
    ListRand lst;
    lst.Deserialize(s, rand1);
    lst.Serialize(t, rand2);
    //cout << lst << endl;

    s.close();
    return 0;
}*/
    