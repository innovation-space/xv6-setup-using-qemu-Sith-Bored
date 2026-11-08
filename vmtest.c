#include "types.h"
#include "stat.h"
#include "user.h"

int global_var = 100;

int
main(void)
{
    int local_var = 200;
    char *heap_var;

    printf(1, "\n===== XV6 VIRTUAL MEMORY TEST =====\n");

    heap_var = malloc(100);
    if(heap_var == 0){
        printf(1, "Memory allocation failed\n");
        exit();
    }

    heap_var[0] = 'A';

    printf(1, "\n--- MEMORY ADDRESSES ---\n");

    printf(1, "Global variable: %p = %d\n",
           &global_var, global_var);

    printf(1, "Local variable:  %p = %d\n",
           &local_var, local_var);

    printf(1, "Heap variable:   %p = %c\n",
           heap_var, heap_var[0]);

    printf(1, "\n--- PAGE TABLE MAPPING ---\n");

    printf(1, "Global variable mapping:\n");
    vmmap((uint)&global_var);

    printf(1, "Local variable mapping:\n");
    vmmap((uint)&local_var);

    printf(1, "Heap variable mapping:\n");
    vmmap((uint)heap_var);

    printf(1, "\n--- FORK MEMORY ISOLATION ---\n");

    int pid = fork();

    if(pid < 0){
        printf(1, "Fork failed\n");
    }
    else if(pid == 0){
        printf(1, "Child: initial global_var = %d\n", global_var);
        global_var = 500;
        printf(1, "Child: modified global_var = %d\n", global_var);
        exit();
    }
    else{
        wait();
        printf(1, "Parent: global_var = %d\n", global_var);
    }

    free(heap_var);

    printf(1, "\n===== TEST COMPLETED =====\n");

    exit();
}
