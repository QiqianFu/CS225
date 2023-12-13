#include "list.h"
#include <iostream>
using namespace std;
int main() {
  List<int> list, list2;

  list.insertFront(3);
  list.insertFront(-2);
  list2.insertFront(4);
  list2.insertFront(2);
  list2.insertFront(1);
  list2.insertFront(-3);

  list.print(std::cout);
  // list.waterfall();

  list.mergeWith(list2);
  list.print(std::cout);
  // List<int> list2 = list.split(2);
  // list.print(std::cout);

  return 0;
}
