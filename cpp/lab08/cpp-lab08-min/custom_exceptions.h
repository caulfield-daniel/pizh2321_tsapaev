#pragma once
#include <stdexcept>
#include <string>

class EmptyEventNameError : public std::runtime_error {
   public:
	EmptyEventNameError() : std::runtime_error("Event name cannot be empty") {}
};

class InvalidDateError : public std::runtime_error {
   public:
	InvalidDateError() : std::runtime_error("Invalid date format") {}
};
