#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  ifstream file("../../project2/sample.txt");
  istream *in = &file;
  char c;

  while (in->get(c))
    cout << c;
}
