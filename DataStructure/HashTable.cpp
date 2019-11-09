#include <iostream>
using namespace std;
template<typename K, typename T>
struct Node{
    K key;
    T value;
    Node *next;
    Node(){ next = 0;   value = 0; }
    Node(K key, T value) : key(key), value(value){   next = 0; }
};

template<typename K, typename T>
struct List{
    Node<K, T> *head;
    Node<K, T> *tail;
    List(){
        head = tail = 0;
    }
    ~List(){
        Node<K, T> *cur = head;
        while(cur != 0){
            Node<K, T> *next = cur->next;
            delete cur;
            cur = next;
        }
    }
    void insert(K key, T val){
        Node<K, T> *newnode = new Node<K, T>(key, val);
        if(head == 0){
            head = tail = newnode;
        }
        else{
            tail->next = newnode;
            tail = newnode;
        }
    }
    Node<K, T>* find(K key){
        Node<K, T> *cur = head;
        while(cur != 0){
            if(cur->key == key)   return cur;
            cur = cur->next;
        }
        return 0;
    }
};

template<typename K, typename V>
struct HashTable{
    List<K, V> chain[100003];
    HashTable(){}
    int hashfunction(int x){
        if(x < 0)   return -x % 100003;
        return x % 100003;
    }
    int hashfunction(string s){
        int H = 0;
        for(int i = 0; i < s.length(); i++){
            H = (H * 131 + s[i]) % 100003;
        }
        return H;
    }
    void insert(int H, K key, V val){
        Node<K, V> *cur = chain[H].head;
        while(cur != 0){
            if(cur->key == key){
                cur->value += val;
                return;
            }
        }
        chain[H].insert(key, val);
    }
    V& operator [](K key){
        int H = hashfunction(key);
        Node<K, V> *f = chain[H].find(key);
        if(f != 0)  return f->value;
        insert(H, key, V(0));
        return chain[H].tail->value;
    }
};

int main(){
    HashTable<string, int> tb;
    HashTable<long long, int> tb2;
    tb["Hello World"] = 369;
    tb["World"] = 123;
    tb2[987654321234LL] = 999;
    tb["Hello World"] += 1;
    cout <<  tb["Hello World"] << endl;
    cout <<  tb["World"] << endl;
    cout << tb2[987654321234LL] << endl;
    return 0;
}
