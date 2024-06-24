#include"InvertedIndex.h"

void InvertedIndex::update_document_base(const std::vector<std::string> input_docs)
{
    docs = input_docs;
    freq_dictionary.clear(); // Clearing freq_dictionary before updating
    std::vector<std::thread> threads;

    for (size_t i = 0; i < docs.size(); ++i)
    {
        threads.emplace_back([this, i]
            {
                std::lock_guard<std::mutex> lock(mtx); // Locking the mutex for the duration of the thread execution
                std::stringstream ss(docs[i]);
                std::string word;
                while (ss >> word)
                {
                    // We bring the word to the lower case for unification
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    // Removing punctuation from the word
                    word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
                    freq_dictionary[word][i]++;
                }
            });
    }

    for (auto& thread : threads)
    {
        thread.join(); // Waiting for all threads to complete
    }
}

std::unordered_map<size_t, size_t> InvertedIndex::get_word_count(const std::string& word)
{
    for (auto str : freq_dictionary)
    {
        if (str.first == word)
        {
            return str.second;
        }
    }

    return std::unordered_map<size_t, size_t>{}; // We return an empty dictionary if the word is not found
}
