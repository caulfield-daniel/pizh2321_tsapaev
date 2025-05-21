#ifndef COMMENTFRAME_H
#define COMMENTFRAME_H

#include <vector>

#include "Frame.h"

// Фрейм для хранения комментариев (ID3v2.4 COMM)
class CommentFrame : public Frame {
   public:
	CommentFrame(const std::string& id, uint32_t size) : Frame(id, size) {}

	// Разбор данных фрейма из потока
	void parse(std::ifstream& stream) override {
		// Структура COMM-фрейма:
		// 1 байт кодировки, 3 байта языка, краткое описание, текст комментария
		uint8_t encoding;
		stream.read(reinterpret_cast<char*>(&encoding),
					1);	 // Чтение кодировки текста

		char lang[3];
		stream.read(lang,
					3);	 // Чтение 3-символьного кода языка (например, 'eng')

		// Чтение оставшихся данных (размер = общий размер фрейма - 4 байта)
		std::vector<char> buf(size - 4);
		stream.read(buf.data(), buf.size());

		// Пропуск краткого описания: поиск двойного нуля (окончание строки)
		size_t pos = 0;
		while (pos + 1 < buf.size() && !(buf[pos] == 0 && buf[pos + 1] == 0))
			pos++;
		pos += 2;  // Пропуск двух нулевых байтов

		// Извлечение текста комментария (после описания)
		comment = std::string(buf.begin() + pos, buf.end());
	}

	// Форматированный вывод для отладки/показа
	std::string repr() const override { return id + ": " + comment; }

   private:
	std::string comment;  // Текст комментария
};

#endif	// COMMENTFRAME_H