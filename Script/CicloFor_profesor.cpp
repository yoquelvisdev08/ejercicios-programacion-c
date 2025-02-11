#include <iostream>
using namespace std;

int Max(int p = 10) {
    int k = 0;
    int i = 0;
    
    do {
        if(i % 2 == 0) {
            k = i;
        }
        i++;
    } while(i <= p);
    
    return k;
}

int main() {
    cout << "Máximo número par: " << Max(10) << endl;
    return 0;
}