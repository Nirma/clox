//
//  Value.h
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/24.
//

#ifndef Value_h
#define Value_h

#include <stdio.h>
#include <stdlib.h>

typedef double Value;

typedef struct {
    int count;
    int capacity;
    Value *values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);

#endif /* Value_h */
