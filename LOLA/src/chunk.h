#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
typedef enum {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

// Wrapper around array of bytes
typedef struct {
    int count;
    int capacity;
    uint8_t* code; 
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk); 
// appends byte
void writeChunk(Chunk* chunk, uint8_t byte, int lines);

int addConstant(Chunk* chunk, Value value);

void freeChunk(Chunk* chunk);

#endif
