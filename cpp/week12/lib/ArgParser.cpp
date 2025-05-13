#include "ArgParser.h"

namespace ArgumentParser {

struct ArgParser::Argument {};

ArgParser::ArgParser(const std::string& name) : parser_name_(name) {}

}  // namespace ArgumentParser