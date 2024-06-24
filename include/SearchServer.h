#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include"InvertedIndex.h"
#include<iostream>

class SearchServer
{
private:
    InvertedIndex &index;

public:
    SearchServer(InvertedIndex& idx) : index(idx) { };

    void process_request(const std::string& request); // request processing method

    std::vector<std::string> split_words(const std::string& text); // the method splits search queries into separate words

    std::vector<std::pair<size_t, float>> rank_documents(const std::vector<std::string>& words); // a method that ranks documents
};