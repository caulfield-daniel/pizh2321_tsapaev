#include "ArgParser.h"

#include <algorithm>
#include <sstream>

using namespace ArgumentParser;

Argument::Argument(ArgumentType type, const std::string& long_name,
				   char short_name, const std::string& description)
	: type_(type),
	  long_name_(long_name),
	  short_name_(short_name),
	  description_(description) {}

ArgumentType Argument::GetType() const { return type_; }
const std::string& Argument::GetLongName() const { return long_name_; }
char Argument::GetShortName() const { return short_name_; }
const std::string& Argument::GetDescription() const { return description_; }

StringArgument::StringArgument(const std::string& long_name, char short_name,
							   const std::string& description)
	: Argument(ArgumentType::STRING, long_name, short_name, description) {}

bool StringArgument::IsPositional() const { return is_positional_; }
bool StringArgument::IsMultiValue() const { return is_multi_value_; }
size_t StringArgument::GetMinArgsCount() const { return min_args_count_; }
bool StringArgument::HasDefault() const { return has_default_; }
bool StringArgument::IsRequired() const { return is_required_; }
bool StringArgument::IsSet() const { return is_set_; }

StringArgument& StringArgument::Positional() {
	is_positional_ = true;
	return *this;
}

StringArgument& StringArgument::MultiValue(size_t min_args_count) {
	is_multi_value_ = true;
	min_args_count_ = min_args_count;
	return *this;
}

StringArgument& StringArgument::Default(const std::string& value) {
	has_default_ = true;
	default_value_ = value;
	return *this;
}

StringArgument& StringArgument::StoreValue(std::string& value) {
	stored_value_ = &value;
	return *this;
}

void StringArgument::Parse(const std::string& value) {
	values_.push_back(value);
	if (stored_value_ && !is_multi_value_) {
		*stored_value_ = value;
	}
	is_set_ = true;
}

void StringArgument::SetDefault() {
	if (has_default_) {
		values_.push_back(default_value_);
		if (stored_value_ && !is_multi_value_) {
			*stored_value_ = default_value_;
		}
		is_set_ = true;
	}
}

size_t StringArgument::GetCount() const { return values_.size(); }
std::string StringArgument::GetStringValue(size_t index) const {
	return index < values_.size() ? values_[index] : "";
}

int StringArgument::GetIntValue(size_t) const { return 0; }
bool StringArgument::GetFlagValue() const { return false; }

IntArgument::IntArgument(const std::string& long_name, char short_name,
						 const std::string& description)
	: Argument(ArgumentType::INT, long_name, short_name, description) {}

bool IntArgument::IsPositional() const { return is_positional_; }
bool IntArgument::IsMultiValue() const { return is_multi_value_; }
size_t IntArgument::GetMinArgsCount() const { return min_args_count_; }
bool IntArgument::HasDefault() const { return has_default_; }
bool IntArgument::IsRequired() const { return is_required_; }
bool IntArgument::IsSet() const { return is_set_; }

IntArgument& IntArgument::Positional() {
	is_positional_ = true;
	return *this;
}

IntArgument& IntArgument::MultiValue(size_t min_args_count) {
	is_multi_value_ = true;
	min_args_count_ = min_args_count;
	return *this;
}

IntArgument& IntArgument::Default(int value) {
	has_default_ = true;
	default_value_ = value;
	return *this;
}

IntArgument& IntArgument::StoreValue(std::vector<int>& values) {
	stored_values_ = &values;
	return *this;
}

void IntArgument::Parse(const std::string& value) {
	try {
		int num = std::stoi(value);
		values_.push_back(num);
		if (stored_values_) {
			stored_values_->push_back(num);
		}
		is_set_ = true;
	} catch (...) {
		throw std::runtime_error("Invalid integer value: " + value);
	}
}

void IntArgument::SetDefault() {
	if (has_default_) {
		values_.push_back(default_value_);
		if (stored_values_) {
			stored_values_->push_back(default_value_);
		}
		is_set_ = true;
	}
}

size_t IntArgument::GetCount() const { return values_.size(); }
std::string IntArgument::GetStringValue(size_t) const { return ""; }
int IntArgument::GetIntValue(size_t index) const {
	return index < values_.size() ? values_[index] : 0;
}
bool IntArgument::GetFlagValue() const { return false; }

FlagArgument::FlagArgument(const std::string& long_name, char short_name,
						   const std::string& description)
	: Argument(ArgumentType::FLAG, long_name, short_name, description) {}

bool FlagArgument::IsPositional() const { return false; }
bool FlagArgument::IsMultiValue() const { return false; }
size_t FlagArgument::GetMinArgsCount() const { return 0; }
bool FlagArgument::HasDefault() const { return has_default_; }
bool FlagArgument::IsRequired() const { return false; }
bool FlagArgument::IsSet() const { return is_set_; }

FlagArgument& FlagArgument::Default(bool value) {
	has_default_ = true;
	default_value_ = value;
	is_set_ = value;
	return *this;
}

FlagArgument& FlagArgument::StoreValue(bool& value) {
	stored_value_ = &value;
	*stored_value_ = is_set_;
	return *this;
}

void FlagArgument::Parse(const std::string&) {
	is_set_ = true;
	if (stored_value_) {
		*stored_value_ = true;
	}
}

void FlagArgument::SetDefault() {
	if (has_default_) {
		is_set_ = default_value_;
		if (stored_value_) {
			*stored_value_ = default_value_;
		}
	}
}

size_t FlagArgument::GetCount() const { return 0; }
std::string FlagArgument::GetStringValue(size_t) const { return ""; }
int FlagArgument::GetIntValue(size_t) const { return 0; }
bool FlagArgument::GetFlagValue() const { return is_set_; }

ArgParser::ArgParser(const std::string& name) : name_(name) {}

StringArgument& ArgParser::AddStringArgument(const std::string& long_name,
											 char short_name,
											 const std::string& description) {
	auto arg =
		std::make_unique<StringArgument>(long_name, short_name, description);
	auto& ref = *arg;
	arguments_.push_back(std::move(arg));
	RegisterArgument(&ref);
	return ref;
}

StringArgument& ArgParser::AddStringArgument(char short_name,
											 const std::string& long_name,
											 const std::string& description) {
	return AddStringArgument(long_name, short_name, description);
}

IntArgument& ArgParser::AddIntArgument(const std::string& long_name,
									   char short_name,
									   const std::string& description) {
	auto arg =
		std::make_unique<IntArgument>(long_name, short_name, description);
	auto& ref = *arg;
	arguments_.push_back(std::move(arg));
	RegisterArgument(&ref);
	return ref;
}

IntArgument& ArgParser::AddIntArgument(char short_name,
									   const std::string& long_name,
									   const std::string& description) {
	return AddIntArgument(long_name, short_name, description);
}

FlagArgument& ArgParser::AddFlag(const std::string& long_name, char short_name,
								 const std::string& description) {
	auto arg =
		std::make_unique<FlagArgument>(long_name, short_name, description);
	auto& ref = *arg;
	arguments_.push_back(std::move(arg));
	RegisterArgument(&ref);
	return ref;
}

FlagArgument& ArgParser::AddFlag(char short_name, const std::string& long_name,
								 const std::string& description) {
	return AddFlag(long_name, short_name, description);
}

void ArgParser::AddHelp(char short_name, const std::string& long_name,
						const std::string& description) {
	help_arg_ = &AddFlag(long_name, short_name, description);
	help_arg_->Default(false);
}

bool ArgParser::Parse(const std::vector<std::string>& args) {
	help_requested_ = false;
	std::vector<std::string> positional_args;
	size_t i = 1;

	for (auto& arg : arguments_) {
		arg->SetDefault();
	}

	while (i < args.size()) {
		const std::string& current = args[i];
		if (current == "--help" || current == "-h") {
			help_requested_ = true;
			return true;
		}

		if (current.size() > 1 && current[0] == '-') {
			if (current[1] == '-') {
				std::string key = current.substr(2);
				std::string value;
				size_t eq_pos = key.find('=');
				if (eq_pos != std::string::npos) {
					value = key.substr(eq_pos + 1);
					key = key.substr(0, eq_pos);
				}
				auto it = long_name_to_arg_.find(key);
				if (it == long_name_to_arg_.end()) {
					return false;
				}
				Argument* arg = it->second;
				if (arg->GetType() == ArgumentType::FLAG) {
					if (!value.empty()) {
						return false;
					}
					arg->Parse("");
				} else {
					if (value.empty()) {
						if (++i >= args.size()) {
							return false;
						}
						value = args[i];
					}
					try {
						arg->Parse(value);
					} catch (...) {
						return false;
					}
				}
			} else {
				std::string keys = current.substr(1);
				for (size_t k = 0; k < keys.size(); ++k) {
					char c = keys[k];
					auto it = short_name_to_arg_.find(c);
					if (it == short_name_to_arg_.end()) {
						return false;
					}
					Argument* arg = it->second;
					if (arg->GetType() == ArgumentType::FLAG) {
						arg->Parse("");
					} else {
						if (k != keys.size() - 1) {
							return false;
						}
						std::string value;
						if (++i < args.size()) {
							value = args[i];
						} else {
							return false;
						}
						try {
							arg->Parse(value);
						} catch (...) {
							return false;
						}
					}
				}
			}
			++i;
		} else {
			positional_args.push_back(current);
			++i;
		}
	}

	size_t pos_idx = 0;
	for (Argument* arg : positional_args_) {
		if (pos_idx >= positional_args.size()) {
			if (arg->IsRequired() && !arg->IsSet()) {
				return false;
			}
			continue;
		}

		if (arg->IsMultiValue()) {
			size_t min_count = arg->GetMinArgsCount();
			if (positional_args.size() - pos_idx < min_count) {
				return false;
			}
			for (size_t j = pos_idx; j < positional_args.size(); ++j) {
				try {
					arg->Parse(positional_args[j]);
				} catch (...) {
					return false;
				}
			}
			pos_idx = positional_args.size();
		} else {
			try {
				arg->Parse(positional_args[pos_idx++]);
			} catch (...) {
				return false;
			}
		}
	}

	if (pos_idx < positional_args.size()) {
		return false;
	}

	for (const auto& arg : arguments_) {
		if (arg->IsRequired() && !arg->IsSet()) {
			return false;
		}
	}

	return true;
}

std::string ArgParser::GetStringValue(const std::string& name,
									  size_t index) const {
	auto it = long_name_to_arg_.find(name);
	if (it != long_name_to_arg_.end() &&
		it->second->GetType() == ArgumentType::STRING) {
		return static_cast<StringArgument*>(it->second)->GetStringValue(index);
	}
	return "";
}

int ArgParser::GetIntValue(const std::string& name, size_t index) const {
	auto it = long_name_to_arg_.find(name);
	if (it != long_name_to_arg_.end() &&
		it->second->GetType() == ArgumentType::INT) {
		return static_cast<IntArgument*>(it->second)->GetIntValue(index);
	}
	return 0;
}

bool ArgParser::GetFlag(const std::string& name) const {
	auto it = long_name_to_arg_.find(name);
	if (it != long_name_to_arg_.end() &&
		it->second->GetType() == ArgumentType::FLAG) {
		return static_cast<FlagArgument*>(it->second)->GetFlagValue();
	}
	return false;
}

bool ArgParser::Help() const { return help_requested_; }

std::string ArgParser::HelpDescription() const {
	std::ostringstream oss;
	oss << name_ << "\n";
	if (help_arg_ && !help_arg_->GetDescription().empty()) {
		oss << help_arg_->GetDescription() << "\n";
	}
	oss << "\n";

	std::vector<Argument*> non_positional;
	for (const auto& arg : arguments_) {
		if (!arg->IsPositional()) {
			non_positional.push_back(arg.get());
		}
	}

	for (Argument* arg : non_positional) {
		oss << FormatArgument(arg) << "\n";
	}

	for (Argument* arg : positional_args_) {
		oss << FormatPositionalArgument(arg) << "\n";
	}

	if (help_arg_) {
		oss << "\n";
		oss << "-" << help_arg_->GetShortName() << ", --"
			<< help_arg_->GetLongName() << " Display this help and exit\n";
	}

	return oss.str();
}

void ArgParser::RegisterArgument(Argument* arg) {
	if (!arg->GetLongName().empty()) {
		long_name_to_arg_[arg->GetLongName()] = arg;
	}
	if (arg->GetShortName() != '\0') {
		short_name_to_arg_[arg->GetShortName()] = arg;
	}
	if (arg->IsPositional()) {
		positional_args_.push_back(arg);
	}
}

std::string ArgParser::FormatArgument(const Argument* arg) const {
	std::ostringstream oss;
	if (arg->GetShortName() != '\0') {
		oss << "-" << arg->GetShortName() << ", ";
	} else {
		oss << "    ";
	}
	oss << "--" << arg->GetLongName();
	if (arg->GetType() == ArgumentType::STRING ||
		arg->GetType() == ArgumentType::INT) {
		oss << "=<"
			<< (arg->GetType() == ArgumentType::STRING ? "string" : "int")
			<< ">";
	}
	oss << "  " << arg->GetDescription();

	std::vector<std::string> options;
	if (arg->IsMultiValue()) {
		options.push_back("repeated");
		if (arg->GetMinArgsCount() > 0) {
			options.push_back("min args = " +
							  std::to_string(arg->GetMinArgsCount()));
		}
	}
	if (arg->HasDefault()) {
		if (arg->GetType() == ArgumentType::FLAG) {
			options.push_back(
				"default = " +
				std::string(
					static_cast<const FlagArgument*>(arg)->GetFlagValue()
						? "true"
						: "false"));
		} else {
			options.push_back(
				"default = " +
				(arg->GetType() == ArgumentType::STRING
					 ? static_cast<const StringArgument*>(arg)->GetStringValue(
						   0)
					 : std::to_string(static_cast<const IntArgument*>(arg)
										  ->GetIntValue(0))));
		}
	}

	if (!options.empty()) {
		oss << " [" << Join(options, ", ") << "]";
	}

	return oss.str();
}

std::string ArgParser::FormatPositionalArgument(const Argument* arg) const {
	std::ostringstream oss;
	oss << "     " << arg->GetLongName() << "=<"
		<< (arg->GetType() == ArgumentType::STRING ? "string" : "int") << ">  "
		<< arg->GetDescription();
	std::vector<std::string> options;
	if (arg->IsMultiValue()) {
		options.push_back("repeated");
		if (arg->GetMinArgsCount() > 0) {
			options.push_back("min args = " +
							  std::to_string(arg->GetMinArgsCount()));
		}
	}
	options.push_back("positional");
	if (arg->HasDefault()) {
		options.push_back(
			"default = " +
			(arg->GetType() == ArgumentType::STRING
				 ? static_cast<const StringArgument*>(arg)->GetStringValue(0)
				 : std::to_string(
					   static_cast<const IntArgument*>(arg)->GetIntValue(0))));
	}
	oss << " [" << Join(options, ", ") << "]";
	return oss.str();
}

std::string ArgParser::Join(const std::vector<std::string>& vec,
							const std::string& delimiter) {
	std::ostringstream oss;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (i > 0) {
			oss << delimiter;
		}
		oss << vec[i];
	}
	return oss.str();
}