#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <sstream>

#include "toolbox.hpp"

void *smalloc(int size, int qty) {
    void *ret = NULL;

    if ((ret = malloc(size * qty)) == NULL) {
        printf("Malloc failed (%d*%d)\n", size, qty);
        exit(EXIT_FAILURE);
    }

    return ret;
}

void *srealloc(void *ptr, int size) {
    void *ret = NULL;

    if ((ret = realloc(ptr, size)) == NULL) {
        printf("Realloc failed (%d)\n", size);
        exit(EXIT_FAILURE);
    }

    return ret;
}

void dbg() {
  printf("dbg\n");
}

void empty(){

}

double getTimeDiff(clock_t start, clock_t end){

  return (end - start) / (double) CLOCKS_PER_SEC;
}

double getSin(long time) {
  return sin(time);
}

std::string toString(double n){
  std::ostringstream buf;
  buf << n;
  std::string str = buf.str();

  return str;
}
