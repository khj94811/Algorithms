#include <iostream>
using namespace std;

template<typename T>
void myswap(T &u, T &v){
    T t = u;
    u = v;
    v = t;
}

template<typename T>
struct Heap{
    T heap[100000];
    int heapindex;
    Heap(){
        heapindex = 1;
    }
    void clear(){
        heapindex = 1;
    }
    void Up(int cur){
        while(cur > 1){
            int par = cur / 2;
            if(heap[par] < heap[cur]){
                myswap(heap[par], heap[cur]);
                cur = par;
            }
            else break;
        }
    }
    void Down(int cur){
        while(cur < heapindex){
            int next = cur;
            if(cur * 2 <heapindex && heap[next] < heap[cur * 2])            next = cur * 2;
            if(cur * 2 + 1 < heapindex && heap[next] < heap[cur * 2 + 1])   next = cur * 2 + 1;
            if(cur != next){
                myswap(heap[cur], heap[next]);
                cur = next;
            }
            else break;
        }
    }
    void push(T val){
        heap[heapindex++] = val;
        Up(heapindex - 1);
    }
    void pop(){
        heap[1] = heap[heapindex - 1];
        --heapindex;
        Down(1);
    }
    T top(){
        return heap[1];
    }
    bool empty(){
        return heapindex == 1;
    }
};

int main(){
    Heap<int> pq;
    for(int i = 2; i <= 8; i += 2)  pq.push(i);
    for(int i = 9; i >= 1; i -= 2)  pq.push(i);
    while(!pq.empty()){
        cout << pq.top() << ' ';
        pq.pop();
    }
    return 0;
}
