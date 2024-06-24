#include"ConverterJSON.h"

std::vector<std::string> ConverterJSON::get_text_documents()
{
	nlohmann::json conf_t;
	std::ifstream config(way_config_file);

	if (!config)
	{
		std::cout << "Cannot open configuration file!\n";
	}
	config >> conf_t;

	std::vector<std::string>vec_docs;
	for (int i = 0; i < conf_t["files"].size(); i++)
	{
		vec_docs.push_back(conf_t["files"][i]);
	}
	config.close();

	std::vector<std::string>docs;
	std::vector<std::ifstream>file_txt(vec_docs.size());
	std::string words;
	for (int i = 0; i < vec_docs.size(); i++)
	{
		file_txt[i].open(vec_docs[i]);
		while (std::getline(file_txt[i], words))
		{
			docs.push_back(words);
		}
	}

	return docs;
}

int ConverterJSON::get_responses_limit() const
{
	nlohmann::json conf_t;
	std::ifstream config(way_config_file);

	if (!config)
	{
		std::cout << "Cannot open configuration file!\n";
	}
	config >> conf_t;

	config.close();

	int max_responses = conf_t["config"]["max_responses"];

	return max_responses;
}

std::vector<std::string> ConverterJSON::get_requests()
{
	std::vector<std::string>req_words;

	nlohmann::json req_files;
	std::ifstream requests_file(way_requests_file);

	if (!requests_file)
	{
		std::cout << "Cannot open requests file!\n";
	}
	requests_file >> req_files;

	for (int i = 0; i < req_files["requests"].size(); i++)
	{
		req_words.push_back(req_files["requests"][i]);
	}
	requests_file.close();

	return req_words;
}

void ConverterJSON::put_answers(std::vector<std::vector<std::pair<size_t, float>>> answers)
{

	nlohmann::json ans_file;
	int index = 1;
	std::string name;
	for (int i = 0; i < answers.size(); i++)
	{
		name = "request00" + std::to_string(index);
		index++;
		if (answers[i].empty())
		{
			ans_file["answers"][name]["result"] = false;
		}
		else
		{
			ans_file["answers"][name]["result"] = true;
			for (const auto& pair : answers[i])
			{
				ans_file["answers"][name]["relevance"].push_back({ {"docid", pair.first}, {"rank", pair.second} });
			}
		}
	}

	std::ofstream answers_file(way_answers_file);

	if (!answers_file)
	{
		std::cout << "Cannot open answers file!\n";
	}

	answers_file << ans_file;

	answers_file.close();
}
