//Diga cual es la salida (Valor = 2 puntos)
//#include <bits/stdc++.h> 
#include <iostream>

using namespace std; 

#define MAX 1000 

class Stack { 
    int top; 

public: 
    int a[MAX]; 

    Stack() { top = -1; } 
    bool push(int x); 
    int pop(); 
    int peek(); 
    bool isEmpty(); 
}; 

bool Stack::push(int x) 
{ 
    if (top >= (MAX - 1)) { 
       
        return false; 
    } 
    else { 
        a[++top] = x; 
       
        return true; 
    } 
} 

int Stack::pop() 
{ 
    if (top < 0) { 
       
        return 0; 
    } 
    else { 
        int x = a[top--]; 
        return x; 
    } 
} 
int Stack::peek() 
{ 
    if (top < 0) { 
      
        return 0; 
    } 
    else { 
        int x = a[top]; 
        return x; 
    } 
} 

bool Stack::isEmpty() 
{ 
    return (top < 0); 
} 


int main() 
{ 
    class Stack s; 
    s.push(10); 
    s.push(20); 
    s.push(30); 
     s.pop() ; 
     
 
    while(!s.isEmpty()) 
    { 
     
        cout << s.peek() <<" "; 
  
        s.pop(); 
    } 

    return 0; 
}