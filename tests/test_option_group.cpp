#include "../config_parser.hpp"
#include <string>

int main()
{
	OptionsGroup group;
	group.add_option("int_opt", "10");
	group.add_option("opt2", "blah");

	for (auto key : group.get_options())
	{
		std::cout << "\t" << key << "\n";
	}
	std::optional<std::string> o = group.get_arg("int_opt");
	std::cout << *o << "\n";
}