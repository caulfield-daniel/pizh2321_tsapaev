#ifndef ALBUMFRAME_H
#define ALBUMFRAME_H

#include "TextFrame.h"

// Фрейм для хранения информации об альбоме (TALB)
class AlbumFrame : public TextFrame {
   public:
	AlbumFrame(const std::string& id, uint32_t size) : TextFrame(id, size) {}

	// Переопределяем repr()
	std::string repr() const override { return "Album: " + text; }
};

#endif	// ALBUMFRAME_H