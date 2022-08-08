#!/bin/bash

cmake -G "Unix Makefiles" -S . -B ./Build
cd ./Build
make
cd Sandbox && ./sandbox