#!/bin/bash

gcc -c -g -O0 drawing.c `pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_ttf-5`
#gcc -c -g -O0 globals.c
gcc -c -g -O0 cpaint.c `pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_ttf-5`
