#include "Parser.h"

#include <iostream>

#include "Frame.h"
#include "FrameFactory.h"
#include "Utils.h"

Parser::Parser(const std::string& filename) : filename(filename) {}

// Основной метод разбора ID3-тега
bool Parser::parse() {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "Ошибка открытия файла: " << filename << std::endl;
		return false;
	}

	// Чтение заголовка ID3 (10 байт)
	char header[10];
	file.read(header, 10);

	// Проверка наличия ID3-тега
	if (std::string(header, 3) != "ID3") {
		std::cerr << "Тег ID3 не найден" << std::endl;
		return false;
	}

	// Проверка версии (поддерживается только версия 2.4)
	uint8_t ver = header[3];
	if (ver != 4) {
		std::cerr << "Неподдерживаемая версия ID3: 2." << (int)ver << std::endl;
		return false;
	}

	// Получение размера тега (синхросейф-кодирование)
	std::array<uint8_t, 4> sizeBytes;
	for (int i = 0; i < 4; ++i) sizeBytes[i] = header[6 + i];
	uint32_t tagSize = syncsafeToInt(sizeBytes);

	// Чтение фреймов
	uint32_t bytesRead = 0;
	while (bytesRead < tagSize) {
		char fid[4];
		file.read(fid, 4);	// Чтение ID фрейма
		std::string frameId(fid, 4);

		// Чтение размера данных фрейма
		std::array<uint8_t, 4> szb;
		file.read(reinterpret_cast<char*>(szb.data()), 4);
		uint32_t frameSize = syncsafeToInt(szb);

		file.ignore(2);	 // Пропуск флагов фрейма

		bytesRead += 10 + frameSize;  // Обновление счетчика

		// Создание и разбор фрейма через фабрику
		auto frame = FrameFactory::create(frameId, frameSize);
		if (frame) {
			frame->parse(file);
			frames.push_back(std::move(frame));
		} else {
			file.ignore(frameSize);	 // Пропуск неподдерживаемых фреймов
		}
	}
	return true;
}

// Вывод информации о всех распознанных фреймах
void Parser::show() const {
	for (const auto& f : frames) {
		std::cout << f->repr() << std::endl;
	}
}