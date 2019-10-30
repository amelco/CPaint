#!/bin/bash

gcc -g -O0 drawing.o cpaint.o main.c -o cpaint
rm *.o
