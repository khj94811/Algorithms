#include <iostream>
using namespace std;

template<typename T, typename Iter>
bool binary_search(Iter l, Iter r, T value){
    --r;
    while(l <= r){
        Iter mid = l + (r - l) / 2;
        if(*mid == value)   return true;
        else if(*mid < value)   l = mid + 1;
        else if(*mid > value)   r = mid - 1;
    }
    return false;
}

int A[123] = {1, 2, 3, 4, 6, 7, 11};

int main(){
    for(int i = 0; i <= 12; i++){
        cout << "Value " << i << " is : " << binary_search(A, A + 7, i) << endl;
    }
    return 0;
}
