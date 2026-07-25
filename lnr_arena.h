// Arena allocator library for C/C++
// Version 1.0.0
// https://github.com/liner-exe/ArenaAllocator.C
// 2026-present liner-exe
// License: MIT

#ifndef LNR_ARENA_H
#define LNR_ARENA_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* buffer;
    size_t capacity;
    size_t offset;
} lnr_arena;

typedef lnr_arena Arena;

bool lnr_arena_init(Arena* arena, const size_t capacity);
void* lnr_arena_alloc(Arena* arena, const size_t size);
void lnr_arena_reset(Arena* arena);
void lnr_arena_free(Arena* arena);

#ifdef __cplusplus
}
#endif

#ifdef LNR_ARENA_IMPLEMENTATION

#ifdef __cplusplus
extern "C" {
#endif

bool lnr_arena_init(Arena* arena, const size_t capacity) {
    if (arena == NULL || capacity == 0) {
        return false;
    }

    void* tempBuffer = malloc(capacity);

    if (tempBuffer != NULL) {
        arena->buffer = (char*)tempBuffer;
        arena->capacity = capacity;
        arena->offset = 0;
        return true;
    }

    return false;
}

void* lnr_arena_alloc(Arena* arena, const size_t size) {
    if (arena == NULL || size == 0) {
        return NULL;
    }

    size_t aligned_size = 0;
    size_t remainder = size % 8;
    if (remainder != 0) {
        aligned_size = size + (8 - remainder);
    } else {
        aligned_size = size;
    }

    if (arena->offset + aligned_size > arena->capacity) {
        return NULL;
    }

    void* address = arena->buffer + arena->offset;
    arena->offset += aligned_size;

    return address;
}

void lnr_arena_reset(Arena* arena) {
    if (arena != NULL) {
        arena->offset = 0;
    }
}

void lnr_arena_free(Arena* arena) {
    if (arena == NULL) {
        return;
    }

    free(arena->buffer);
    arena->buffer = NULL;
    arena->capacity = 0;
    arena->offset = 0;
}

#ifdef __cplusplus
}
#endif

#endif // LNR_ARENA_IMPLEMENTATION

#endif // LNR_ARENA_H