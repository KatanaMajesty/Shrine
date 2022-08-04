#!/bin/bash

cmake -G "Unix Makefiles" -S . -B ./build
cd ./build
make
cd Sandbox && ./sandbox