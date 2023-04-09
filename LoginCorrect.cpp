#include "LoginCorrect.h"
#include "Chat.h"
#include <iostream>
#include <memory>

LoginCorrect::LoginCorrect() : State("LoginCorrect")
{
};



void LoginCorrect::handle(Chat& chat)
{
    std::cout << "Введите Пароль: ";
    std::string password;
    std::getline(std::cin >> std::ws, password);

    //Допустимые символы
    if (chat.isCorrectValue(password)) {
        const std::string login = chat.getUser()->getLogin();
        //Пароль правильный
        if (database::isCorrectPassword(login, password)) {
            //Загрузить из базы и задать Ник текущего пользователя
            const std::string name = database::getNameByLogin(login);
            chat.getUser()->setName(name);
            std::cout << chat.getUser()->getName() << ", добро пожаловать в Чат!\n";
            chat.transitionTo(std::move(std::make_unique<UserInChat>()));
            chat.printMessagesToUser();
        }

        //Пароль неверный
        else {
            std::cout << "Пароль неверный!\n";
            chat.transitionTo(std::move(std::make_unique<PasswordIncorrect>()));
        }
    }

    //Недопустимые символы
    else {
        std::cout << "Некорректные символы.\n";
        std::cin.clear();
        chat.transitionTo(std::move(std::make_unique<LoginCorrect>()));
    }
}