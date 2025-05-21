#ifndef FRAMEFACTORY_H
#define FRAMEFACTORY_H

#include <memory>

#include "ArtistFrame.h"
#include "CommentFrame.h"
#include "TextFrame.h"

// Фабрика для создания объектов фреймов по их ID
class FrameFactory {
   public:
	static std::unique_ptr<Frame> create(const std::string& id, uint32_t size) {
		// 1. Сначала проверяем специфичные ID
		if (id == "COMM") {
			// Фрейм комментария (COMM)
			return std::make_unique<CommentFrame>(id, size);
		} else if (id == "TPE1") {
			// Фрейм автора аудио (TPE1 - Involved performer(s)/lead
			// performer(s))
			return std::make_unique<ArtistFrame>(id, size);
		}
		// 2. Затем общие случаи
		else if (id[0] == 'T') {
			// Текстовые фреймы (TIT2, TALB, TCON и др.)
			return std::make_unique<TextFrame>(id, size);
		}
		// 3. Неподдерживаемые фреймы
		else {
			return nullptr;
		}
	}
};

#endif	// FRAMEFACTORY_H