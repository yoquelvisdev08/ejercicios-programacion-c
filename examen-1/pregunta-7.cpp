#include <iostream> 
#include <list> 
using namespace std; 
  
int main() 
{ 
    list<int> mylist{ 1, 5, 3, 2, 4 }; 

    mylist.sort(); 
  
    for (auto it = mylist.begin(); it != mylist.end(); ++it) 
        cout << ' ' << *it; 
    return 0; 
}