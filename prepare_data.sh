#!/usr/bin/env bash

cd ..
mkdir data
cp sentiments/sentiment_scores.txt data/
cd data
wget http://dataset.cs.mcgill.ca/ubuntu-corpus-1.0/ubuntu_dialogs.tgz
tar xf ubuntu_dialogs.tgz
