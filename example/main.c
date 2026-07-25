#define LNR_ARENA_IMPLEMENTATION
#include <lnr_arena.h>

#include <stdio.h>

int main(void) {
    lnr_arena arena;

    // Allocate 1 MB for the Arena
    if (lnr_arena_init(&arena, 1024 * 1024)) {
        printf("Successfully initialized\n");
    }

    // Allocate memory
    int* numbers = (int*)lnr_arena_alloc(&arena, 10 * sizeof(int));

    // Use allocated memory
    if (numbers != NULL) {
        numbers[0] = 42;
        printf("%d\n", numbers[0]);
    }

    // Reset arena offset for next task or frame
    lnr_arena_reset(&arena);

    // Release memory when shutting down
    lnr_arena_free(&arena);

    return 0;
}