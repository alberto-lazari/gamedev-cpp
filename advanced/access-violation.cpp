const int x = 0;

int main()
{
    int* mut_x = const_cast<int*>(&x);
    // Works but UB
    ++mut_x;

    int n {};
    // Runtime error (UB): pointer being freed was not allocated
    // delete &n;
    
    // Stack variables live in the same address space
    int sv1;
    int sv2;
    int sv3;
}
