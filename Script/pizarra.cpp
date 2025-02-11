#include <iostream>
#include <cmath>
#include <termios.h>
#include <unistd.h>
using namespace std;

int main() {
    char ch;
    const unsigned char white = '\xDB';
    const unsigned char gray = '\xB0';
    
    for(int count = 0; count < 80*25-1; count++) {
        ch = white;
        for (int j = 2; j < count; j++) {
            if(count % j == 0) {
                ch = gray;
                break;
            }
        }
        cout << ch;
    }
    
    cin.get();
    return 0;
}