#!/usr/bin/env bash
# path to binary       path to sentiment dataset    path to dialog dataset   number of units to process
./cmake-build-debug/sentiment ./../data/sentiment_scores.txt ./../data/dialogs/ 100 >out 2>error