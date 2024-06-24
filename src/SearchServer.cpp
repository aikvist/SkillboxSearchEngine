#include"SearchServer.h"

std::vector<std::string> SearchServer::split_words(const std::string& text)
{
    std::istringstream ss(text);
    std::vector<std::string> words;
    std::string word;
    while (ss >> word)
    {
        // We bring the word to the lower case for unification
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        // Removing punctuation from the word
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

        words.push_back(word);
    }

    return words;
}

void SearchServer::process_request(const std::string& request)
{
    std::vector<std::string> words = split_words(request);

    if (words.empty())
    {
        std::cout << "No words found in the request. Result: false" << std::endl;
    }

    
    std::sort(words.begin(), words.end(), [this](const std::string& a, const std::string& b)
        {
            return index.get_word_count(a).size() < index.get_word_count(b).size();
        });

    auto ranked_documents = rank_documents(words);
    if (ranked_documents.empty())
    {
        std::cout << "No documents found. Result: false" << std::endl;
    }

    else
    {
        for (const auto& doc : ranked_documents)
        {
            std::cout << "Doc ID: " << doc.first << ", Rank: " << doc.second << std::endl;
        }
    }
}

std::vector<std::pair<size_t, float>> SearchServer::rank_documents(const std::vector<std::string>& words)
{
    std::unordered_map<size_t, size_t> doc_scores;

    for (int i = 0; i < words.size(); i++)
    {
        auto counts = index.get_word_count(words[i]);

        for (const auto& count : counts)
        {
            doc_scores[count.first] += count.second;
            std::cout << "Doc ID: " << count.first << ", Score: " << doc_scores[count.first] << std::endl;
        }
    }

    std::vector<std::pair<size_t, float>> ranked_docs(doc_scores.begin(), doc_scores.end());
    std::cout << "Ranked docs size: " << ranked_docs.size() << std::endl;

    if (!ranked_docs.empty())
    {
        float max_score = 0;
        for (const auto& doc : ranked_docs)
        {
            if (doc.second > max_score)
            {
                max_score = doc.second;
            }
        }
        std::cout << "Max score: " << max_score << std::endl;

        if (max_score > 0)
        {
            for (auto& doc : ranked_docs)
            {
                doc.second /= max_score;
                std::cout << "Normalized Doc ID: " << doc.first << ", Score: " << doc.second << std::endl;
            }
        }

        std::sort(ranked_docs.begin(), ranked_docs.end(), [](std::pair<size_t, float> a, std::pair<size_t, float> b)
            {
                return a.second > b.second;
            });
    }

    return ranked_docs;
}