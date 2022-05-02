#pragma once
#include "Buddy.h"

//Considerar, hacer que funcione con (void*) en lugar de (int)
int buddy_malloc(int size_to_alloc);
void buddy_free(int adress);

#include "Buddy_malloc.cpp"
