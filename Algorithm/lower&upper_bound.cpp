#include <iostream>
using namespace std;

template<typename T>
int lower_bound(T *A, int l, int r, int val){
    while(l < r){
        int mid = (l + r) >> 1;
        if(A[mid] < val)    l = mid + 1;
        else r = mid;
    }
    return l;
}

template<typename T>
int upper_bound(T * A, int l, int r, int val){
    while(l < r){
        int mid = (l + r) >> 1;
        if(A[mid] <= val)    l = mid + 1;
        else r = mid;
    }
    return l;
}
const int N = 6;
const int A[] = {1, 3, 4, 7, 11, 14, (int)1e9};
/* Array의 마지막 원소에는 큰 값을 넣어주자. */

int main(){
    for(int i = 0; i < 15; i++){
        cout << "Value : " << i << endl;
        cout << "Lower bound is : " << A[lower_bound(A, 0, N, i)] << '\n';
        cout << "Upper bound is : " << A[upper_bound(A, 0, N, i)] << '\n';
    }
    return 0;
}
