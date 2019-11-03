#include <iostream>
using namespace std;

const int Q_SIZE = 5;

template<typename T>
struct Queue{
    T arr[Q_SIZE];
    int qfront, qback, qsize;
    Stack(){ qfront = qback = 0; }
    void push(T val){
        arr[qback] = val;
        qback = (qback + 1) % Q_SIZE;
        ++qsize;
    }
    void pop(){
        qfront = (qfront + 1) % Q_SIZE;
        --qsize;
    }
    T front(){
        return arr[qfront];
    }
    bool empty(){
        return qfront == qback;
    }
    int size(){
        return qsize;
    }
};

int main(){
    Queue<int> q;
    for(int i = 1; i <= 14; i++){
        if(i >= 6)  q.pop();
        q.push(i);
    }
    for(int i = 1; i <= 5; i++){
        cout << "Front of Q is : " << q.front() << '\n';
        q.pop();
    }
    return 0;
}
