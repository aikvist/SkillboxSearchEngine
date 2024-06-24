#include"ConverterJSON.h"
#include"InvertedIndex.h"
#include"SearchServer.h"

int main()
{
    ConverterJSON converterJSON;

    std::vector<std::string> vec_docs = converterJSON.get_text_documents();

    InvertedIndex index;
    index.update_document_base(vec_docs);

    SearchServer searchServer(index);

    std::vector<std::string> requests = converterJSON.get_requests();
 
    std::vector<std::vector<std::pair<size_t, float>>> answers;

    for (const auto& request : requests)
    {
        std::cout << "Request: " << request << "\n";
        auto words = searchServer.split_words(request);
        auto ranked_documents = searchServer.rank_documents(words);
        answers.emplace_back(ranked_documents);
    }
    converterJSON.put_answers(answers);

    system("pause");
    return 0;
}
