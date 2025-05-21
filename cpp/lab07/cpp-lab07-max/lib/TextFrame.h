#ifndef TEXTFRAME_H
#define TEXTFRAME_H

#include <vector>

#include "Frame.h"

// Базовый класс для текстовых фреймов (например, TIT2, TALB и др.)
class TextFrame : public Frame {
   public:
	TextFrame(const std::string& id, uint32_t size) : Frame(id, size) {}

	void parse(std::ifstream& stream) override {
		uint8_t encoding;
		stream.read(reinterpret_cast<char*>(&encoding), 1);	 // Кодировка текста

		std::vector<char> buf(size - 1);
		stream.read(buf.data(), buf.size());  // Чтение текста

		// Преобразование в строку (предполагается UTF-8 или ISO-8859-1)
		text = std::string(buf.begin(), buf.end());
	}

	std::string repr() const override { return id + ": " + text; }

   protected:
	std::string text;  // Текстовое содержимое фрейма
};

#endif	// TEXTFRAME_H