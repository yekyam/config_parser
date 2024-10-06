#include "../config_parser.hpp"

#include <algorithm>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <stdexcept>
#include <fstream>
#include <sstream>

int main() {
	OptionsParser p("../testfile.txt");
	auto opts = p.parse();
	if (!opts.has_value())
	{
		return -1;
	}
	for (const auto& opt : opts->get_options())
	{
		std::cout << opt << '\t' << (*opts->get_arg(opt)) << '\n';
	}
}