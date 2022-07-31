#!/bin/bash

emcc --bind -O3 bindings.cpp -I ../src -I ../yanl/src -std=c++20