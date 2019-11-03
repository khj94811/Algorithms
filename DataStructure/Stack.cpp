#include <iostream>
using namespace std;

template<typename T>
struct Stack{
    T arr[100000];
    int stackidx;
    Stack(){ stackidx = 0; }
    void push(T val){
        arr[stackidx++] = val;
    }
    void pop(){
        --stackidx;
    }
    T top(){
        return arr[stackidx - 1];
    }
    bool empty(){
        return stackidx == 0;
    }
    int size(){
        return stackidx;
    }
};

int main(){
    Stack<int> stk;
    for(int i = 1; i <= 5; i++){
        stk.push(i);
    }
    for(int i = 1; i <= 5; i++){
        cout << "Top of stack is : " << stk.top() << '\n';
        stk.pop();
    }
    return 0;
}
