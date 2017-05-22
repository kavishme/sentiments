#!/usr/bin/env sh

swig -Wall -c++ -python sentiment.i
python setup.py build_ext --inplace