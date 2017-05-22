#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>


#define NUM_THREADS 1

using namespace std;

vector<vector<string> > readTSV(string filepath);
vector<string> parseWords(string words);
map<string, float> getSentimentScores();
vector<string> getFiles();
bool getSentiment(const map<string, float> &sentiment, string filepath);
int run(int argc, char **argv);