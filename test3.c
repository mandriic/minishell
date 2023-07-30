    #include <stdio.h>
#include <stdlib.h>

int main() {
    // Dereference a NULL pointer to cause a segmentation fault
    int* ptr = NULL;
    *ptr = 42; // This will cause a segmentation fault

    return 0;
}

