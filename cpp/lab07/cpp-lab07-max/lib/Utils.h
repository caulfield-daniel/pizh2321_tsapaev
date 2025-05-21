#ifndef UTILS_H
#define UTILS_H

#include <array>

// Утилиты для работы с ID3-тегами
inline uint32_t syncsafeToInt(const std::array<uint8_t, 4>& bytes) {
	// Преобразование синхросейф-кодированного числа в uint32_t.
	// Каждый байт использует только 7 младших битов.
	return (bytes[0] & 0x7F) << 21 | (bytes[1] & 0x7F) << 14 |
		   (bytes[2] & 0x7F) << 7 | (bytes[3] & 0x7F);
}

#endif	// UTILS_H