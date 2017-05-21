#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/tokenizer.hpp"
#include "omp.h"
#include <numeric>
#include "boost/chrono.hpp"

#define NUM_THREADS 1

using namespace std;
using namespace boost::chrono;

string SENTIMENT_FILE = "data/SentiWordNet_3.0.0_20130122.txt";
string DIALOGS = "data/dialogs";
uint UNITS = 100;

vector<vector<string>> readTSV(string filepath) {
    try {
        ifstream sf;
        sf.open(filepath);
        vector<vector<string>> tsvf;
        uint32_t rows = 0;
        while (sf.good()) {
            string line;
            getline(sf, line);
            ++rows;
            vector<std::string> cells;
            stringstream lineStream(line);
            string cell;

            while (getline(lineStream, cell, '\t')) {
                cells.push_back(cell);
            }

            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty()) {
                // If there was a trailing comma then add an empty element.
                cells.push_back("");
            }

            tsvf.push_back(cells);
        }
        cerr << endl << rows << " rows read from file: " << filepath;
        return tsvf;
    }
    catch (exception e) {
        cerr << endl << "Cannot read file: " << filepath << endl << e.what();
        exit(0);
    }
}

// breaks word string and removes #xx from word
vector<string> parseWords(string words) {
    string word;
    vector<string> result;

    stringstream ss(words);
    while (getline(ss, word, ' ')) {
        auto hloc = word.find('#');
        word = word.substr(0, hloc);
        result.push_back(word);
    }
    return result;
}

map<string, float> getSentimentScores() {
    auto tsvf = readTSV(SENTIMENT_FILE);
    map<string, float> sentvalues;

    for (auto i = tsvf.begin(); i != tsvf.end(); ++i) {

        vector<string> &row = *i;
        try {
            if (row.size() >= 5) {
                float ps = stof(row[2]);
                float ns = stof(row[3]);
                auto words = parseWords(row[4]);
                for (auto j = words.begin(); j != words.end(); ++j) {
                    sentvalues[*j] = ps - ns;
                }
            }
        }
        catch (exception e) {
            cerr << endl << "Cannot process words: " << row[4] << endl << e.what();
        }
    }

    return sentvalues;
}


vector<string> getFiles() {
    try {
        vector<string> files;
        uint count = 0;
        for (boost::filesystem::recursive_directory_iterator end, dir(DIALOGS);
             dir != end; ++dir) {
            if (boost::filesystem::is_regular_file(dir->path())) {
                files.push_back(dir->path().string());

                if (++count > UNITS)
                    break;
            }
        }
        return files;
    }
    catch (exception e) {
        cerr << endl << "Cannot read files from directory: " << DIALOGS << endl << e.what();
    }
}

bool getSentiment(const map<string, float> &sentiment, string filepath) {
    try {
        // Read dialogs from tsv
        auto rows = readTSV(filepath);

        string conversation;
        // Ignore all columns except last one with dialog
        for (auto i = rows.begin(); i != rows.end(); ++i) {
            auto row = *i;
            conversation += row.back();
        }

        boost::algorithm::to_lower(conversation);
        boost::tokenizer<> tok(conversation);
        float sum = 0;
        for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
            string word = *beg;
            if (sentiment.count(word))
                sum += sentiment.at(word);
        }

        return sum >= 0;
    }
    catch (exception e) {
        cerr << endl << "Cannot get sentiment for file: " << filepath << endl << e.what();
    }
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        SENTIMENT_FILE = argv[1];
        DIALOGS = argv[2];
        UNITS = stoi(argv[3]);

        // load sentiments into memory
        const map<string, float> sentiments = getSentimentScores();

        // Fetch files from dialog corpus. UNIT number of files only
        auto files = getFiles();
        uint positives[NUM_THREADS] = {0};
        omp_set_num_threads(NUM_THREADS);
        auto dt_s = high_resolution_clock::now();

#pragma omp parallel
        {// For each file in files process it to find sentiment
            int id = omp_get_thread_num();
            for (auto i = id; i < files.size(); i += NUM_THREADS) {
                bool is_positive = getSentiment(sentiments, files[i]);

                if (is_positive) {
                    cerr << endl << "Positive sentiment for conversation: " << files[i];
                    ++positives[id];
                } else {
                    cerr << endl << "Negative sentiment for conversation: " << files[i];
                }
            }
        }
        auto dt = duration_cast<nanoseconds>(high_resolution_clock::now() - dt_s);
        int count = accumulate(begin(positives), end(positives), 0, plus<int>());
//        cout<<endl<<"Threads, Units, dt, Positives, Negatives"<<endl;

//        cout << endl << "Threads: " << NUM_THREADS << ",";
//        cout << endl << "Units: " << UNITS << ",";
//        cout << endl << "dt: " << dt.count() << ",";
//        cout << endl << "Positives: " << count << ",";
//        cout << endl << "Negatives: " << UNITS - count << "," << endl;

        cout << NUM_THREADS << ",";
        cout << UNITS << ",";
        cout << dt.count() << ",";
        cout << count << ",";
        cout << UNITS - count << endl;

    } else {
        cerr << endl
             << "Required three arguments, arg1:path/to/sentimentfile, arg2:path/to/data/folder, arg3: number of dialogs to process.";
    }
    return 0;
}