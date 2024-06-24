This search engine is a console application that can be run on any server or computer. These are the configurable json files "config.json" and "request.json", so that you can change the paths to the files that the search engine will search for, as well as the search queries that will be searched.

This project was created using the following technologies:
1) Language standart C++17
2) Nlohmann JSON Library
3) GoogleTest Framework
4) CMake 3.23.3

How to create and run this application
Download the project in ZIP format, and then unzip it or clone this repository to your computer using the command:
git clone https://github.com/aikvist/SearchEngine .git
and then navigate to the project folder. The "json_file" and "resource file" folders must be moved to the project's build location.

Before launching the application, you must specify in this system the paths to the text files that you wanted to get, to search for the "files" key of the "config.json" file, and your requests to the "requests.json" file.
For example:
config.json
{
    "config": {
        "name": "Search_Engine",
        "version": "0.1",
        "max_responses": 5
    },
    "files": [
        "./resources/first_file.txt",
        "./resources/second_file.txt",
        "./resources/third_file.txt"
    ]
}
requests.json
{
    "requests": [
        "Dima",
        "one two three",
        "some words"
    ]
}

After launching, the application object of the "ConverterJSON" class will search for the files "config.json" and "request.json" and will try to serialize them.  It will receive the necessary data in the private field of the object, such as paths to text files and query strings.

Then an object of the "InvertedIndex" class will analyze the files.txt along the paths that the "ConverterJSON" object received from the "config.json" file into unique words and will count the number of entries of each word in each file.
An object of the "SearchServer" class calculates the relative relevance for each query in each file, and puts the results of the calculation in the "answers_file.json".
