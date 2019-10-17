#!/bin/bash

gcc -g -O0 globals.o drawing.o cpaint.o main.c -o cpaint
rm *.o
