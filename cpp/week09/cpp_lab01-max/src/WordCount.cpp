#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Класс для анализа статистики файла
 */
class FileStats {
   private:
	size_t lines_ = 0;
	size_t words_ = 0;
	size_t chars_ = 0;
	size_t bytes_ = 0;
	std::string filename_;

	/**
	 * @brief Подсчет слов в строке
	 * @param line Строка для анализа
	 */
	void count_words(const std::string& line) {
		bool inWord = false;
		for (char c : line) {
			if (std::isspace(c)) {
				inWord = false;
			} else if (!inWord) {
				words_++;
				inWord = true;
			}
		}
	}

   public:
	/**
	 * @brief Конструктор класса FileStats
	 * @param filename Имя файла для анализа
	 */
	explicit FileStats(const std::string& filename) : filename_(filename) {}

	/**
	 * @brief Анализ файла
	 */
	void analyze() {
		// Первый проход для подсчета байтов
		std::ifstream file(filename_, std::ios::binary | std::ios::ate);
		if (!file) throw std::runtime_error("Can't open file: " + filename_);
		bytes_ = file.tellg();
		file.close();

		// Второй проход для остальной статистики (открываем в бинарном режиме)
		file.open(filename_, std::ios::binary);
		if (!file) throw std::runtime_error("Can't open file: " + filename_);

		std::string line;
		while (std::getline(file, line)) {
			// Удаляем завершающий \r, если он есть (для обработки Windows)
			if (!line.empty() && line.back() == '\r') {
				line.pop_back();
			}

			if (!line.empty()) {
				lines_++;
			}
			chars_ += line.size();

			count_words(line);
		}
		file.close();
	}

	/**
	 * @brief Получение количества строк в файле
	 * @return Количество строк
	 */
	size_t get_lines() const { return lines_; }

	/**
	 * @brief Получение количества слов в файле
	 * @return Количество слов
	 */
	size_t get_words() const { return words_; }

	/**
	 * @brief Получение количества символов в файле
	 * @return Количество символов
	 */
	size_t get_chars() const { return chars_; }

	/**
	 * @brief Получение количества байтов в файле
	 * @return Количество байтов
	 */
	size_t get_bytes() const { return bytes_; }

	/**
	 * @brief Получение имени файла
	 * @return Имя файла
	 */
	std::string get_filename() const { return filename_; }
};

/**
 * @brief Класс для парсинга аргументов командной строки
 */
class ArgumentParser {
   private:
	bool show_lines_ = false;
	bool show_words_ = false;
	bool show_bytes_ = false;
	bool show_chars_ = false;
	std::vector<std::string> filenames_;

	/**
	 * @brief Парсинг опции командной строки
	 * @param option Опция для парсинга
	 */
	void parse_option(const std::string& option) {
		if (option == "-l" || option == "--lines")
			show_lines_ = true;
		else if (option == "-w" || option == "--words")
			show_words_ = true;
		else if (option == "-c" || option == "--bytes")
			show_bytes_ = true;
		else if (option == "-m" || option == "--chars")
			show_chars_ = true;
		else if (option[0] == '-') {
			for (size_t i = 1; i < option.size(); ++i) {
				switch (option[i]) {
					case 'l':
						show_lines_ = true;
						break;
					case 'w':
						show_words_ = true;
						break;
					case 'c':
						show_bytes_ = true;
						break;
					case 'm':
						show_chars_ = true;
						break;
					default:
						throw std::invalid_argument("Unknown option: -" +
													std::string(1, option[i]));
				}
			}
		}
	}

   public:
	/**
	 * @brief Парсинг аргументов командной строки
	 * @param argc Количество аргументов
	 * @param argv Массив аргументов
	 */
	void parse(int argc, char* argv[]) {
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (arg[0] == '-') {
				parse_option(arg);
			} else {
				filenames_.push_back(arg);
			}
		}

		if (!(show_lines_ || show_words_ || show_bytes_ || show_chars_)) {
			show_lines_ = show_words_ = show_bytes_ = true;
		}
	}

	/**
	 * @brief Проверка, нужно ли показывать количество строк
	 * @return true, если нужно показывать количество строк, иначе false
	 */
	bool show_lines() const { return show_lines_; }

	/**
	 * @brief Проверка, нужно ли показывать количество слов
	 * @return true, если нужно показывать количество слов, иначе false
	 */
	bool show_words() const { return show_words_; }

	/**
	 * @brief Проверка, нужно ли показывать количество байтов
	 * @return true, если нужно показывать количество байтов, иначе false
	 */
	bool show_bytes() const { return show_bytes_; }

	/**
	 * @brief Проверка, нужно ли показывать количество символов
	 * @return true, если нужно показывать количество символов, иначе false
	 */
	bool show_chars() const { return show_chars_; }

	/**
	 * @brief Получение списка имен файлов
	 * @return Список имен файлов
	 */
	const std::vector<std::string>& get_filenames() const { return filenames_; }
};

/**
 * @brief Класс для вывода результатов анализа
 */
class ResultPrinter {
   public:
	/**
	 * @brief Вывод результатов анализа
	 * @param stats Статистика файла
	 * @param parser Парсер аргументов командной строки
	 */
	static void print(const FileStats& stats, const ArgumentParser& parser) {
		if (parser.show_lines()) std::cout << stats.get_lines() << " ";
		if (parser.show_words()) std::cout << stats.get_words() << " ";
		if (parser.show_bytes()) std::cout << stats.get_bytes() << " ";
		if (parser.show_chars()) std::cout << stats.get_chars() << " ";
		std::cout << stats.get_filename() << std::endl;
	}
};
