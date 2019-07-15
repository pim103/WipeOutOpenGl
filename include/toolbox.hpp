#ifndef TOOLBOX_HPP_INCLUDED
#define TOOLBOX_HPP_INCLUDED

#include <time.h>
#include <iostream>

void *smalloc(int size, int qty);
void *srealloc(void *ptr, int size);
void dbg();
double getTimeDiff(clock_t start, clock_t end);
double getSin(long time);
void empty();
std::string toString(double n);

#endif // TOOLBOX_HPP_INCLUDED
