#include "LoginIncorrect.h"
#include "Chat.h"
#include <iostream>
#include <memory>

//Возможный выбор пользователя
enum class EnumChoiceLI : unsigned
{
    INPUT_AGAIN = 1,
    REGISTRATION,
    EXIT
};



LoginIncorrect::LoginIncorrect() : State("LoginIncorrect")
{
};



void LoginIncorrect::handle(Chat& chat)
{
    std::cout << "| 1 - Ввести Логин заново | 2 - Регистрация | 3 - Выход из программы | :  ";
    std::string input;
    std::getline(std::cin >> std::ws, input);

    //Введено более одного символа
    if (input.length() > 1) {
        chat.transitionTo(std::move(std::make_unique<LoginIncorrect>()));
    }
    //Введён один символ
    else {
        //Попытка преобразовать символ в число
        try {
            int choice = std::stoi(input);
            handleChoice(chat, choice);
        }
        //Символ не число - вернуться в начало ко вводу
        catch (const std::invalid_argument&) {
            chat.transitionTo(std::move(std::make_unique<LoginIncorrect>()));
        }
    }
}



void LoginIncorrect::handleChoice(Chat& chat, int choice_)
{
    EnumChoiceLI choice = static_cast<EnumChoiceLI>(choice_);
    switch (choice) {
    case EnumChoiceLI::INPUT_AGAIN: {
        chat.transitionTo(std::move(std::make_unique<SignIn>()));
        break;
    }
    case EnumChoiceLI::REGISTRATION: {
        chat.transitionTo(std::move(std::make_unique<Registration>()));
        break;
    }
    case EnumChoiceLI::EXIT: {
        std::cout << "Завершение работы";
        chat.exit();
        break;
    }
    default: {
        std::cin.clear();
        chat.transitionTo(std::move(std::make_unique<LoginIncorrect>()));
        break;
    }
    }
}