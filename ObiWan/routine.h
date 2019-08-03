#ifndef ROUTINE_H
#define ROUTINE_H

#include <stdint.h>

/*
typedef struct {
    uint8_t type;
    uint16_t size;
} message_header_t;
*/

typedef struct {
    uint8_t block_count;
    uint16_t block_height;
} routine_source_t;

typedef struct {
    uint32_t cant;
    uint16_t height;
} routine_t;

#endif // ROUTINE_H
