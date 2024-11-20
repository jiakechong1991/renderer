#!/bin/bash

DEFS="-D_POSIX_C_SOURCE=200809L"
OPTS="-std=c89 -Wall -Wextra -pedantic -O3 -flto -ffast-math"
SRCS="main.c platforms/linux.c core/*.c scenes/*.c shaders/*.c tests/*.c"
LIBS="-lm -lX11"

cd renderer && gcc -o ../viewer $DEFS $OPTS $SRCS $LIBS && cd ..

echo "编译完成,运行 ./viewer来开启二进制程序"


