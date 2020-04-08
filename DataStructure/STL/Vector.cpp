#include <iostream>
using namespace std;

template<typename T>
struct Vector{
    T *arr;
    int _size, _capacity;
    Vector(){
        _size = 0;
        _capacity = 16;
        arr = new T[_capacity];
    }
    Vector(int sz){
        _size = _capacity = sz;
        arr = new T[_size];
    }
    Vector(int sz, T val){
        _size = _capacity = sz;
        arr = new T[_size];
        for(register int i = 0; i < _size; i++){
            arr[i] = val;
        }
    }
    ~Vector(){
        delete[] arr;
    }
    void resize(int sz){
        T *temp = new T[sz];
        for(register int i = 0; i < _size; i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        _capacity = sz;
    }
    void clear(){
        delete[] arr;
        _size = 0;
        _capacity = 16;
        arr = new T[_capacity];
    }
    void push_back(T val){
        if(_size == _capacity){
            resize(_size * 2);
        }
        arr[_size++] = val;
    }

    void pop_back(){
        --_size;
    }
    int size() const {
        return _size;
    }
    T* begin() const {
        return &arr[0];
    }
    T* end() const {
        return &arr[0] + _size;
    }
    T& operator [](int index){
        return arr[index];
    }
    T operator [](int index) const{
        return arr[index];
    }
};

int main(){
    Vector<int> vt;
    for(int i = 0; i < 64; i++){
        vt.push_back(i);
    }
    for(int i = 16; i < 48; i++){
        cout <<vt[i] << '\n';
    }
    cout << endl;
    return 0;
}
