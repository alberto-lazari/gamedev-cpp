#include <iostream>

// Template-like get function
#define get(type, list) *((type*) list->data)

struct node {
  void* data;
  node* next;
};

int main() {
  node list = { new int {1}, new node { new int {2}, new node { new int {3}, nullptr } } };
  for (node* n = &list; n != nullptr; n = n->next) {
    std::cout << get(int, n);
    if (n->next != nullptr) {
      std::cout << " -> ";
    }
  }
  std::cout << std::endl;
}
