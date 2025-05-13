#pragma once

#include <map>
#include <string>

namespace ArgumentParser {

class ArgParser {
   private:
	struct Argument;

	std::string parser_name_;
	std::map<std::string, Argument> args_;
	std::map<char, std::string> short_to_long_;

   public:
	explicit ArgParser(const std::string& name);
};

}  // namespace ArgumentParser
