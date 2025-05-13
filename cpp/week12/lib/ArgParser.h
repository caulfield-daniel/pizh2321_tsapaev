#pragma once

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

enum class ArgumentType { STRING, INT, FLAG };

namespace ArgumentParser {
class Argument {
   public:
	Argument(ArgumentType type, const std::string& long_name, char short_name,
			 const std::string& description);
	virtual ~Argument() = default;

	ArgumentType GetType() const;
	const std::string& GetLongName() const;
	char GetShortName() const;
	const std::string& GetDescription() const;

	virtual bool IsPositional() const = 0;
	virtual bool IsMultiValue() const = 0;
	virtual size_t GetMinArgsCount() const = 0;
	virtual bool HasDefault() const = 0;
	virtual bool IsRequired() const = 0;
	virtual bool IsSet() const = 0;

	virtual void Parse(const std::string& value) = 0;
	virtual void SetDefault() = 0;

	virtual size_t GetCount() const = 0;
	virtual std::string GetStringValue(size_t index) const = 0;
	virtual int GetIntValue(size_t index) const = 0;
	virtual bool GetFlagValue() const = 0;

   protected:
	ArgumentType type_;
	std::string long_name_;
	char short_name_;
	std::string description_;
};

class StringArgument : public Argument {
   public:
	StringArgument(const std::string& long_name, char short_name,
				   const std::string& description);

	bool IsPositional() const override;
	bool IsMultiValue() const override;
	size_t GetMinArgsCount() const override;
	bool HasDefault() const override;
	bool IsRequired() const override;
	bool IsSet() const override;

	StringArgument& Positional();
	StringArgument& MultiValue(size_t min_args_count = 0);
	StringArgument& Default(const std::string& value);
	StringArgument& StoreValue(std::string& value);

	void Parse(const std::string& value) override;
	void SetDefault() override;

	size_t GetCount() const override;
	std::string GetStringValue(size_t index) const override;
	int GetIntValue(size_t index) const override;
	bool GetFlagValue() const override;

   private:
	bool is_positional_ = false;
	bool is_multi_value_ = false;
	size_t min_args_count_ = 0;
	bool has_default_ = false;
	std::string default_value_;
	bool is_required_ = false;
	bool is_set_ = false;
	std::vector<std::string> values_;
	std::string* stored_value_ = nullptr;
};

class IntArgument : public Argument {
   public:
	IntArgument(const std::string& long_name, char short_name,
				const std::string& description);

	bool IsPositional() const override;
	bool IsMultiValue() const override;
	size_t GetMinArgsCount() const override;
	bool HasDefault() const override;
	bool IsRequired() const override;
	bool IsSet() const override;

	IntArgument& Positional();
	IntArgument& MultiValue(size_t min_args_count = 0);
	IntArgument& Default(int value);
	IntArgument& StoreValue(std::vector<int>& values);

	void Parse(const std::string& value) override;
	void SetDefault() override;

	size_t GetCount() const override;
	std::string GetStringValue(size_t index) const override;
	int GetIntValue(size_t index) const override;
	bool GetFlagValue() const override;

   private:
	bool is_positional_ = false;
	bool is_multi_value_ = false;
	size_t min_args_count_ = 0;
	bool has_default_ = false;
	int default_value_ = 0;
	bool is_required_ = false;
	bool is_set_ = false;
	std::vector<int> values_;
	std::vector<int>* stored_values_ = nullptr;
};

class FlagArgument : public Argument {
   public:
	FlagArgument(const std::string& long_name, char short_name,
				 const std::string& description);

	bool IsPositional() const override;
	bool IsMultiValue() const override;
	size_t GetMinArgsCount() const override;
	bool HasDefault() const override;
	bool IsRequired() const override;
	bool IsSet() const override;

	FlagArgument& Default(bool value);
	FlagArgument& StoreValue(bool& value);

	void Parse(const std::string& value) override;
	void SetDefault() override;

	size_t GetCount() const override;
	std::string GetStringValue(size_t index) const override;
	int GetIntValue(size_t index) const override;
	bool GetFlagValue() const override;

   private:
	bool has_default_ = false;
	bool default_value_ = false;
	bool is_set_ = false;
	bool* stored_value_ = nullptr;
};

class ArgParser {
   public:
	ArgParser(const std::string& name);

	StringArgument& AddStringArgument(const std::string& long_name,
									  char short_name = '\0',
									  const std::string& description = "");
	StringArgument& AddStringArgument(char short_name,
									  const std::string& long_name,
									  const std::string& description = "");

	IntArgument& AddIntArgument(const std::string& long_name,
								char short_name = '\0',
								const std::string& description = "");
	IntArgument& AddIntArgument(char short_name, const std::string& long_name,
								const std::string& description = "");

	FlagArgument& AddFlag(const std::string& long_name, char short_name = '\0',
						  const std::string& description = "");
	FlagArgument& AddFlag(char short_name, const std::string& long_name,
						  const std::string& description = "");

	void AddHelp(char short_name, const std::string& long_name,
				 const std::string& description);
	bool Parse(const std::vector<std::string>& args);

	std::string GetStringValue(const std::string& name, size_t index = 0) const;
	int GetIntValue(const std::string& name, size_t index = 0) const;
	bool GetFlag(const std::string& name) const;

	bool Help() const;
	std::string HelpDescription() const;

   private:
	void RegisterArgument(Argument* arg);
	std::string FormatArgument(const Argument* arg) const;
	std::string FormatPositionalArgument(const Argument* arg) const;
	static std::string Join(const std::vector<std::string>& vec,
							const std::string& delimiter);

	std::string name_;
	std::vector<std::unique_ptr<Argument>> arguments_;
	std::map<std::string, Argument*> long_name_to_arg_;
	std::map<char, Argument*> short_name_to_arg_;
	std::vector<Argument*> positional_args_;
	FlagArgument* help_arg_ = nullptr;
	bool help_requested_ = false;
};
}  // namespace ArgumentParser
