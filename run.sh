#!/usr/bin/env bash

echo "Threads, Units, dt, Positives, Negatives"
./cmake-build-debug/sentiment ./../data/sentiment_scores.txt ./../data/dialogs/ 100 2>error