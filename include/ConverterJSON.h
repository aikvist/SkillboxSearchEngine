#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"nlohmann/json.hpp"
#include<iostream>

class ConverterJSON
{
private:
	std::string way_config_file = "./json_file/config.json";
	std::string way_requests_file = "./json_file/requests.json";
	std::string way_answers_file = "./json_file/answers.json";

public:
	ConverterJSON() = default;

	std::vector<std::string> get_text_documents(); // the method returns the contents of the documents

    int get_responses_limit() const; // the method returns the maximum number of responses to the request

	std::vector<std::string> get_requests(); // the method returns the contents of the requests.json file

	void put_answers(std::vector<std::vector<std::pair<size_t, float>>> answers); // the method places the result of the program in the answers.json file
};