#include <iostream>
using namespace std;
 
struct employee {
 char name[100];
 int age;
 float salary;
 char department[50];
};

// This function takes structure variable as parameter
void printEmployeeDetails(struct employee emp){
   cout << "\n*** Employee Details ***\n";
   cout << "Name : " << emp.name << "\nAge : "<< emp.age << "\nSalary : "
        << emp.salary << "\nDepartment : "<< emp.department;
}
 
// This function takes structure pointer as parameter
void printEmployeeDetails(struct employee *emp){
   cout << "\n--- Employee Details ---\n";
   cout << "Name : " << emp->name << "\nAge : "<< emp->age << "\nSalary : "
        << emp->salary << "\nDepartment : "<< emp->department;
}

void printAge(int age){
    cout << "\n\nAge = " << age;
}
 
int main(){
   struct employee manager, *ptr;
    
   printf("Enter Name, Age, Salary and Department of Employee\n");
   // Assigning data to members of structure variable
   cin >> manager.name >> manager.age >> manager.salary >> manager.department;
    
   // Passing structure variable to function
   printEmployeeDetails(manager);

   // Passing address of structure variable to a function
   printEmployeeDetails(&manager);
   /* Passing structure member to function */
   printAge(manager.age);

   return 0;
}