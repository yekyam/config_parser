#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <stdexcept>
#include <fstream>
#include <sstream>

// Header only cause I'm lazy and this lib is small

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (std::getline (ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

class OptionsGroup {
	protected:
	    std::string group_name;
	    std::unordered_map<std::string, std::string> options;

	public:

		std::string get_group_name() const {
			return group_name;
		}

		std::vector<std::string> get_options() const {
			std::vector<std::string> keys;
			keys.reserve(options.size());

			for (auto opt : options)
			{
				keys.push_back(opt.first);
			}

			return keys;
		}

		std::optional<std::string> get_arg(std::string key) const
		{
			try {
				return options.at(key);
			} catch (std::exception& e) {
				return {};
			}
		}

		void add_option(std::string key, std::string value)
		{
			options[key] = value;
		}
};

class OptionsParser {
	protected:
	std::string filename;

    public:
	OptionsParser(std::string filename) {
		this->filename = filename;
	}

	std::optional<OptionsGroup> parse()
	{
		/* Steps:
			1) Get a line from a string
			2) Remove whitespace
			3) Split at '=' into key,value
		 */
		std::ifstream file(filename, std::ifstream::in);

		if (!file.is_open() || !file.good())
		{
			return {};
		}

		std::string line;
		OptionsGroup group;

		while (std::getline(file, line))
		{
			line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return std::isspace(c); }), line.end());
			//std::cout << line << '\n';

			auto tokens = split(line, '=');

			if (tokens.size() == 1)
			{
				// check if its a category
			}
			if (tokens.size() == 2)
			{
				// check if its key value
				group.add_option(tokens[0], tokens[1]);
			}
		}
		return group;
	}
};

