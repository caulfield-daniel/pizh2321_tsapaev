#include <iostream>
#include <string>
#include <vector>

#include "WordCount.cpp"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [OPTION]... [FILE]..."
				  << std::endl;
		std::cerr << "Options:" << std::endl;
		std::cerr << "  -l, --lines    Print line count" << std::endl;
		std::cerr << "  -w, --words    Print word count" << std::endl;
		std::cerr << "  -c, --bytes    Print byte count" << std::endl;
		std::cerr << "  -m, --chars    Print character count" << std::endl;
		std::cout << "dfsfds" << std::endl;
		return 1;
	}

	try {
		// 1. Парсинг аргументов командной строки
		ArgumentParser parser;	   // Создаем объект парсера
		parser.parse(argc, argv);  // Парсим аргументы

		// 2. Обработка каждого файла из списка
		for (const auto& filename : parser.get_filenames()) {
			try {
				// 2.1 Создаем объект для сбора статистики по файлу
				FileStats stats(filename);

				// 2.2 Анализируем файл (подсчет строк, слов, символов и байтов)
				stats.analyze();

				// 2.3 Выводим результаты в соответствии с выбранными опциями
				ResultPrinter::print(stats, parser);

			} catch (const std::exception& e) {
				// Обработка ошибок для конкретного файла
				std::cerr << "Error processing " << filename << ": " << e.what()
						  << std::endl;
				// Продолжаем обработку остальных файлов
			}
		}
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}