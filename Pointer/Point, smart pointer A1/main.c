#include<iostream>
using namespace std;
class Ptr {  
    int* ptr;
public:
    explicit Ptr(int* p = NULL) { ptr = p; }  // Save pointer
    ~Ptr() { delete(ptr); }  // recycle pointer
    int& operator *() { return *ptr; }  // override operator
};
int main() 
{
    Ptr ptr(new int());
    *ptr = 4;
    cout << *ptr<<endl;
    // Recycle pointer automatically
    return 0;
}