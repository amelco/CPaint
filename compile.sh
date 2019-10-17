#!/bin/bash

gcc -g -O0 globals.o drawing.o cpaint.c -o cpaint
rm *.o
