#include <iostream>
#include <string>

void use_after_free()
{
    int* arr = new int[5];
    delete [] arr;
    arr[0] = 5;
}

void double_free()
{
    int* arr = new int[5];
    delete [] arr;
    delete [] arr;
}

int main(int argc, char** argv)
{
    //use_after_free();
    int *array = new int[100];
    delete [] array;
    return array[argc];  // BOOM
}
