#include <iostream>
#include <random>
using namespace std;

template<typename T>
void myswap(T &u, T &v){
    T t = u;
    u = v;
    v = t;
}

template<typename T, typename Comp>
void partition(T *A, int l, int r, Comp comp){
    T sorted[r - l + 1];
    int mid = (l + r) >> 1;
    int le = l, ri = mid + 1, k = 0;
    while(le <= mid && ri <= r){
        if(A[le] < A[ri])   sorted[k++] = A[le++];
        else                sorted[k++] = A[ri++];
    }
    while(le <= mid)    sorted[k++] = A[le++];
    while(ri <= r)      sorted[k++] = A[ri++];
    for(int i = 0; i < k; i++)  A[l + i] = sorted[i];
}

template<typename T, typename Comp>
void sort(T *A, int l, int r, Comp comp){
    if(l >= r)    return;
    int mid = (l + r) >> 1;
    sort(A, l, mid, comp);
    sort(A, mid + 1, r, comp);
    partition(A, l, r, comp);
}

template<typename T>
bool comp(T &u, T &v){
    return u < v;
}


template<typename T>
void sort(T *A, int l, int r){
    sort(A, l, r, comp<T>);
}

int A[12345];

int main(){
    for(int i = 0; i < 33; i++)     A[i] = rand() % 1234;
    sort(A, 0, 32);
    for(int i = 0; i < 33; i++)     cout <<A[i] << ' ';
    return 0;
}
