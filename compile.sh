#!/bin/bash

gcc -g -O0 drawing.o cpaint.o main.c -o cpaint `pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_ttf-5`
rm *.o
