#!/usr/bin/env bash
# path to binary       path to sentiment dataset    path to dialog dataset   number of units to process
# JSON output
#echo '['
#for i in {1,10,100,1000,10000,100000,900000}
#do
#    echo '{'
#    ./cmake-build-debug/sentiment ./../data/sentiment_scores.txt ./../data/dialogs/ $i 2>error
#    echo '},'
#done
#echo ']'

# CSV output
echo "Threads, Units, dt, Positives, Negatives"
for i in {1,10,100,1000,10000,100000,900000}
do
    ./cmake-build-debug/sentiment ./../data/sentiment_scores.txt ./../data/dialogs/ ${i} 2>error${i}
done