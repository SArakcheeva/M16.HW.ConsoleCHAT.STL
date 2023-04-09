#include "Chat.h"
#include <iostream>
#include <vector>

//Начальная инициализация указателя на статический объект класса
Chat* Chat::instance_ = nullptr;



Chat* Chat::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = new Chat();
    }
    return instance_;
}



void Chat::process()
{
    state_->handle(*this);
}



Chat::Chat() : state_(std::make_unique<StartState>()), user_(new User), isRun_(nullptr)
{

};



void Chat::transitionTo(std::unique_ptr<State> newState)
{
    state_ = std::move(newState);
}



User* Chat::getUser()
{
    return user_;
}



void Chat::attach(std::shared_ptr<bool> isRun)
{
    isRun_ = isRun;
}



void Chat::exit()
{
    *isRun_ = false;
}



void Chat::printUserList()
{
    //Загрузить список пользователей и вывести на экран
    auto userNames = std::make_shared<std::vector<std::string> >();
    database::loadUserNames(userNames);
	for (const auto& name : *userNames) {
		std::cout << name << "; ";
	}
	std::cout << std::endl;
}



void Chat::printMessagesToUser()
{
    //Загрузить сообщения и вывести на экран
    auto messagesToUser = std::make_shared<std::list<Message> >();  //Сообщения текущему пользователю
    database::loadMessages(*user_, messagesToUser);                 //Заполнить вектор - сообщениями пользователю
    if (messagesToUser->empty()) {
        std::cout << "Вам сообщений нет.\n";
    }
    else {
        for (const auto& message : *messagesToUser) {
            std::cout << message.getNameFrom() << ": "
                << message.getText() << std::endl;
        }
    }
}



void Chat::removeAccount()
{
    database::removeUser(*user_);
    user_->reset();
    std::cout << "Ваш аккаунт удалён.\n";
}



bool Chat::isCorrectValue(const std::string& inputValue)
{
    //Можно вводить символы латинского алфавита и арабские цифры
    const std::string permissionedChars =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t pos = inputValue.find_first_not_of(permissionedChars);
    if (pos != std::string::npos) {
        return false;
    }
    return true;
}