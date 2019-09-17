#ifndef ROUTINE_H
#define ROUTINE_H

#include <stdint.h>

#define ROUTINE_SOURCE_MESSAGE 1
#define ROUTINE_MESSAGE 2
#define ACK 3

typedef struct {
    uint16_t block_count;
    uint16_t block_height;
} routine_source_t;

typedef struct {
    uint32_t cant;
    uint32_t height;
} routine_t;

#endif // ROUTINE_H
