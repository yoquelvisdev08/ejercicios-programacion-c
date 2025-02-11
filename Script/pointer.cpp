#include <iostream>
using namespace std;

int main() {
    int *p;
    int array[10];
    int i;

    for (i = 0; i < 10; i++) {
        array[i] = i*2;
    }

    for (i = 0; i < 10; i++) {
        cout << "array[" << i << "] = " << array[i] << endl;
    }

    return 0;
}

