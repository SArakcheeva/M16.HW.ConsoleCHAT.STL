/**
\file Message.h
\brief Класс инкапсулирует данные о сообщении

Содержит поля:
- имя пользователя от кого сообщение
- имя пользователя кому сообщение
- текст сообщения
*/

#pragma once

#include <string>

class Message {
    public:
        /**
        Конструктор по-умолчанию
        */
        Message() = delete;

        /**
        Параметризованный конструктор
        \param[in] nameUserFrom Ник пользователя от которого сообщение
        \param[in] nameUserTo Ник пользователя кому адресовано сообщение
        \param[in] text Текст сообщения
        */
        Message(const std::string& nameUserFrom,
            const std::string& nameUserTo,
            const std::string& text);
        /**
        \return Ник пользователя от которого сообщение
        */
        const std::string& getNameFrom() const;

        /**
        \return Ник пользователя кому сообщение
        */
        const std::string& getNameTo() const;

        /**
        \return Ник пользователя кому сообщение
        */
        const std::string& getText() const;

    private:
        const std::string nameUserFrom_;	///<Имя пользователя от которого сообщение
        const std::string nameUserTo_;		///<Имя пользователя кому адресовано сообщение
        const std::string text_;			///<Текст сообщения
};



namespace message {
    /**
    Запустить тестирование методов класса
    */
    void test();
}