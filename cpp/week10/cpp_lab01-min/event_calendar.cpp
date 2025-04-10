#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Класс, представляющий событие
 */
class Event {
   private:
	/**
	 * @brief Дата события
	 */
	std::string date_;

	/**
	 * @brief Название события
	 */
	std::string name_;

	/**
	 * @brief Описание события
	 */
	std::string description_;

   public:
	/**
	 * @brief Конструктор события
	 * @param date Дата события
	 * @param name Название события
	 * @param description Описание события
	 */
	Event(std::string date, std::string name, std::string description)
		: date_(date), name_(name), description_(description) {}

	/**
	 * @brief Метод для получения даты события
	 * @return Дата события
	 */
	std::string getDate() const { return date_; }

	/**
	 * @brief Метод для получения названия события
	 * @return Название события
	 */
	std::string getName() const { return name_; }

	/**
	 * @brief Метод для получения описания события
	 * @return Описание события
	 */
	std::string getDescription() const { return description_; }
};

/**
 * @brief Класс, представляющий календарь
 */
class Calendar {
   private:
	/**
	 * @brief Название комнаты
	 */
	std::string room_;

	/**
	 * @brief Адрес комнаты
	 */
	std::string address_;

	/**
	 * @brief Вектор событий
	 */
	std::vector<Event> events_;

   public:
	/**
	 * @brief Конструктор календаря
	 * @param room Название комнаты
	 * @param address Адрес комнаты
	 */
	Calendar(std::string room, std::string address)
		: room_(room), address_(address) {}

	/**
	 * @brief Метод для добавления события в календарь
	 * @param event Событие, которое нужно добавить
	 */
	void addEvent(const Event& event) { events_.push_back(event); }

	/**
	 * @brief Метод для удаления события из календаря
	 * @param eventName Название события, которое нужно удалить
	 */
	void removeEvent(const std::string& eventName) {
		auto it = events_.begin();
		while (it != events_.end()) {
			if (it->getName() == eventName) {
				it = events_.erase(it);
			} else {
				++it;
			}
		}
	}

	/**
	 * @brief Метод для вывода информации о событиях в календаре
	 */
	void print() const {
		int i = 1;
		std::cout << "*** " << room_ << ", " << address_ << " ***" << std::endl;
		for (const Event& event : events_) {
			std::cout << "\n                           EVENT " << i
					  << std::endl;
			std::cout << "-----------------------------------------------------"
						 "-----------"
					  << std::endl;
			std::cout << "Name:\t\t" << event.getName() << std::endl;
			std::cout << "Date:\t\t" << event.getDate() << std::endl;
			std::cout << "Description:\t" << event.getDescription()
					  << std::endl;
			std::cout << "-----------------------------------------------------"
						 "-----------"
					  << std::endl;
			std::cout << std::endl;
			i++;
		}
	}
};
