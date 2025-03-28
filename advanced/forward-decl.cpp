class Class;

int main()
{
    // Compiler knows the size of the variable at compile time.
    // It will reserve sizeof(void*) for pc.
    Class* pc = nullptr;

    // Error: forward declaration is not sufficient.
    // The compiler cannot know sizeof(Class) without its full definition.
    // Class* pc = new Class;
}
