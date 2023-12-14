#!/bin/bash
clang++ grader.cpp robot.cpp
./a.out < examples/02.in
./display.py robot.bin