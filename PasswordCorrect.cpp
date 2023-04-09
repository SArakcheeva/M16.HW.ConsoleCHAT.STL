#include "PasswordCorrect.h"
#include "Chat.h"
#include <iostream>
#include <memory>

PasswordCorrect::PasswordCorrect() : State("PasswordCorrect")
{
};



void PasswordCorrect::handle(Chat& chat)
{
    std::cout << "Придумайте Ник: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);

    //Допустимые символы
    if (chat.isCorrectValue(name)) {
        //Такой ник уже зарегистрирован
        if (database::isExistName(name)) {
            std::cout << "Пользователь с таким Ником уже зарегистрирован\n";
            chat.transitionTo(std::move(std::make_unique<PasswordCorrect>()));
        }

        //Ник уникальный
        else {
            chat.getUser()->setName(name);
            database::addUser(*chat.getUser());
            std::cout << "Вы успешно зарегистрированы!\n"
                << chat.getUser()->getName() << ", добро пожаловать в Чат!\n";
            chat.transitionTo(std::move(std::make_unique<UserInChat>()));
        }
    }

    //Недопустимые символы
    else {
        std::cout << "Некорректные символы.\n";
        std::cin.clear();
        chat.transitionTo(std::move(std::make_unique<PasswordCorrect>()));
    }
}