#include <iostream>
using namespace std;
#define size 101 // max size for the stack dataay

int flow(int, string);

class myStack {
private:
  int data[size]; // dataay used for the implementation of the Stack ADT
  int top;        // holds the index of the top of the Stack
  string name;    // holds the name of the stack

public:
  myStack(string stackName) { // constructor function
    top = -1;                 // newly created Stack will have a top of -1 == empty Stack
    name = stackName;         // sets the name for initialized Stack
  }

  string Name() { // returns the name of the Stack
    return name;
  }

  void Push(int num) { // appends the num to the top of the Stack
    int flag = flow(top, "over");

    if (flag == 1) // exits the function if the Stack overflows
      return;

    data[++top] = num; // increments the top before pushing num
  }

  void Pop() {
    int flag = flow(top, "over");

    if (flag == 1) // exits the function if Stack overflows
      return;

    top--; // subtracts the "top" index by 1 to create space for more items in
           // the Stack
  }

  int Top() { // returns the top element in the Stack
    int flag = flow(top, "under");

    if (flag == 1) // exits the function if Stack underflows
      return -1;

    return data[top];
  }

  int IsEmpty() {
    if (top == -1)
      return 1; // returns 1 if the Stack is empty

    return 0; // returns 0 if the Stack is empty
  }

  void Print() {
    int flag = flow(top, "under");

    if (flag == 1) // exits the function if stack underflows
      return;

    cout << "Stack " << name << ":";

    for (int i = 0; i <= top; i++) { // prints all the elements up to and
                                     // including the top of the Stack
      cout << "\nIndex:  " << i << "\tValue:  " << data[i];
    }
  }
};

int main() {
  myStack toast("toast");

  toast.Push(10);
  toast.Push(20);
  toast.Push(30);
  toast.Push(40);
  toast.Push(50);

  toast.Print();

  // int top = toast.Top();
  // cout << "Top of Stack " << toast.Name() << ":  " << top;

  cout << "\n\n";
  return 0;
}

int flow(int top, string flow) {
  if (top == (size - 1) && flow == "over") { // returns 1 if Stack overflows
    cout << "Stack Overflow! Please pop from the stack!\n";
    return 1;
  }

  else if (top == -1 && flow == "under") { // returns 1 if Stack underflows
    cout << "Stack Underflow! Please push items to the stack!\n";
    return 1;
  }

  return 0; // returns 0 if Stack does not "(under/over)-flow"
}
