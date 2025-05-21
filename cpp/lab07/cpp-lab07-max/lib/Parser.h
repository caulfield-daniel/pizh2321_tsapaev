#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>

#include "Frame.h"

// Класс для парсинга ID3v2 тегов из файла
class Parser {
   public:
	explicit Parser(const std::string& filename);  // Конструктор с именем файла
	bool parse();								   // Запуск разбора тега
	void show() const;							   // Вывод информации о фреймах

   private:
	std::string filename;						 // Имя файла для разбора
	std::vector<std::unique_ptr<Frame>> frames;	 // Список распознанных фреймов
};

#endif	// PARSER_H