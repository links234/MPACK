#!/bin/sh

make -f "jni/Linux.mk"
valgrind --tool=memcheck --leak-check=full --suppressions=scripts/LinuxValgrind.supp --log-file=valgrind.log ./game
