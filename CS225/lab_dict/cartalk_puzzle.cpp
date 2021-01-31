/*
 * @Author: Houhao
 * @Date: 2020-08-25 19:08:19
 * @LastEditors: Houhao
 * @LastEditTime: 2020-12-06 12:01:06
 * @FilePath: \cs225git\lab_dict\cartalk_puzzle.cpp
 */
/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            if (word.size() == 5)
            {
                string word1 = word.substr(1); // first removed
                string word2 = word.substr(0,1) + word.substr(2); // second removed
                if (d.homophones(word, word1) && d.homophones(word, word2))
                {
                    // cout<< word << endl;
                    std::tuple<std::string, std::string, std::string> combo = std::make_tuple(word, word1, word2);
                    ret.push_back(combo);
                }
            }
        }
    }
    return ret;
}
