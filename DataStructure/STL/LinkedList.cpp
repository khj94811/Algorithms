#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T value;
    Node *next;
    Node(){ next = 0; }
    Node(T value) : value(value){   next = 0; }
};

template<typename T>
struct List{
    Node<T> *head;
    Node<T> *tail;
    List(){
        head = tail = 0;
    }
    ~List(){
        Node<T> *cur = head;
        while(cur != 0){
            Node<T> *next = cur->next;
            delete cur;
            cur = next;
        }
    }
    void insert(T val){
        Node<T> *newnode = new Node<T>(val);
        if(head == 0){
            head = tail = newnode;
        }
        else{
            tail->next = newnode;
            tail = newnode;
        }
    }
    Node<T>* find(T val){
        Node<T> *cur = head;
        while(cur != 0){
            if(cur->value == val)   return cur;
            cur = cur->next;
        }
        return 0;
    }
};

int main(){
    List<int> lst;
    for(int i = 2; i <= 8; i++){
        lst.insert(i);
    }
    Node<int> *fnd = lst.find(4);
    while(fnd != 0){
        cout << fnd->value << ' ';
        fnd = fnd->next;
    }
    cout <<endl;
    return 0;
}
