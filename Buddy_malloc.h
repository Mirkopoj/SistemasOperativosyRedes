#pragma once
#include "Buddy.h"

//Considerar, hacer que funcione con (void*) en lugar de (int)
void *buddy_malloc(void *size_to_alloc);
void buddy_free(void *adress);

#include "Buddy_malloc.cpp"
