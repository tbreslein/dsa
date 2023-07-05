#include "arraybuffer.h"
#include "doublelinkedlist.h"
#include "linkedlist.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>

int main() {
    printf("\nRunning C tests...\n");
    lli_test();
    dlli_test();
    qi_test();
    si_test();
    abi_test();
    printf("Finished all C tests!\n");
    return 0;
}
