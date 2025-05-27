#ifndef ARTISTFRAME_H
#define ARTISTFRAME_H

#include "TextFrame.h"

// Фрейм для хранения информации об авторе (TPE1)
class ArtistFrame : public TextFrame {
   public:
	ArtistFrame(const std::string& id, uint32_t size) : TextFrame(id, size) {}

	// Переопределяем repr()
	std::string repr() const override { return "Artist: " + text; }
};

#endif	// ARTISTFRAME_H