#ifndef ROUTINE_H
#define ROUTINE_H

#include <stdint.h>

#define ROUTINE_SOURCE_MESSAGE 1

typedef struct {
    uint16_t block_count;
    uint16_t block_height;
} routine_source_t;

typedef struct {
    uint32_t cant;
    uint16_t height;
} routine_t;

#endif // ROUTINE_H
