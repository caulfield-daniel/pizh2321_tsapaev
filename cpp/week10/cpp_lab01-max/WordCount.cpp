#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [OPTION]... [FILE]..."
				  << std::endl;
		std::cerr << "Options:" << std::endl;
		std::cerr << "  -l, --lines    Print line count" << std::endl;
		std::cerr << "  -w, --words    Print word count" << std::endl;
		std::cerr << "  -c, --bytes    Print byte count" << std::endl;
		std::cerr << "  -m, --chars    Print character count" << std::endl;
		return 1;
	}

	std::vector<std::string> filenames;
	bool countLines = false, countWords = false, countBytes = false,
		 countChars = false;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg[0] == '-') {
			if (arg == "--lines") {
				countLines = true;
			} else if (arg == "--words") {
				countWords = true;
			} else if (arg == "--bytes") {
				countBytes = true;
			} else if (arg == "--chars") {
				countChars = true;
			} else if (arg.size() > 1 &&
					   arg[1] != '-') {	 // Обработка групповых опций (-lwc)
				for (size_t j = 1; j < arg.size(); ++j) {
					switch (arg[j]) {
						case 'l':
							countLines = true;
							break;
						case 'w':
							countWords = true;
							break;
						case 'c':
							countBytes = true;
							break;
						case 'm':
							countChars = true;
							break;
						default:
							std::cerr << "Unknown option: '-" << arg[j] << "'"
									  << std::endl;
							return 1;
					}
				}
			} else {
				std::cerr << "Unknown option: " << arg << std::endl;
				return 1;
			}
		} else {
			filenames.push_back(arg);
		}
	}

	// Если опции не указаны - выводим всё
	if (!countLines && !countWords && !countBytes) {
		countLines = countWords = countBytes = true;
	}

	// Обработка файлов
	for (const auto& filename : filenames) {
		// 1. Подсчёт байт
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		if (!file) {
			std::cerr << "WordCount: " << filename << ": No such file or directory"
					  << std::endl;
			continue;
		}
		const std::streamsize bytes = file.tellg();
		file.close();

		// 2. Подсчёт строк, слов и символов
		file.open(filename);
		if (!file) {
			std::cerr << "Error reopening file: " << filename << std::endl;
			continue;
		}

		size_t lines = 0, words = 0, chars = 0;
		std::string line;
		while (std::getline(file, line)) {
			lines++;
			chars += line.size() + 1;  // +1 для \n (getline его съедает)

			// Подсчёт слов
			bool inWord = false;
			for (char c : line) {
				if (std::isspace(c)) {
					inWord = false;
				} else if (!inWord) {
					words++;
					inWord = true;
				}
			}
		}

		// 3. Вывод результатов
		if (countLines) std::cout << lines << " ";
		if (countWords) std::cout << words << " ";
		if (countBytes) std::cout << bytes << " ";
		if (countChars) std::cout << chars << " ";
		std::cout << filename << std::endl;
	}

	return 0;
}