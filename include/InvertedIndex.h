#pragma once
#include<vector>
#include<unordered_map>
#include<string>
#include<algorithm>
#include<sstream>
#include<thread>
#include<mutex>
#include <future>
#include <cctype>

class InvertedIndex
{
private:
    std::vector<std::string> docs;
    std::mutex mtx;
    std::unordered_map<std::string, std::unordered_map<size_t, size_t>>freq_dictionary;
    

public:
    InvertedIndex() = default;
    void update_document_base(const std::vector<std::string> input_docs); // This method takes a vector of lines, where each line represents a separate document. The method initializes the database документов и запускает многопоточную обработку каждого документа для индексации слов

    std::unordered_map<size_t, size_t>get_word_count(const std::string& word); // This method returns a map showing in which documents and how often the specified word occurs

    
};
