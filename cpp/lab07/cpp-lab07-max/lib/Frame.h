#ifndef FRAME_H
#define FRAME_H

#include <fstream>
#include <string>

// Базовый класс для всех типов фреймов ID3v2
class Frame {
   public:
	Frame(const std::string& id, int size) : id(id), size(size) {}
	virtual ~Frame() = default;

	virtual void parse(std::ifstream& stream) = 0;	// Разбор данных фрейма
	virtual std::string repr() const = 0;			// Строковое представление

	const std::string& getId() const {
		return id;
	}  // ID фрейма (например, "COMM")

   protected:
	std::string id;	 // Идентификатор фрейма (4 символа)
	int size;		 // Размер данных фрейма в байтах
};

#endif	// FRAME_H