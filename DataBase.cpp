#include "DataBase.h"

#include <map>
#include <vector>
#include <list>
#include <assert.h>
#include <iostream>

#include "User.h"
#include "Message.h"

namespace {
	//База зарегистрированных пользователей
	//где: string - id пользователя(login); User - структура с данными пользователя (ник-логин-пароль)
	std::map <std::string, User> users_map;

	//Имя адресата чтобы отправить сообщение всем
	const std::string MSG_TO_ALL = "all";

	//База сообщений пользователей друг другу
	std::list<Message> messages;
}



void database::initialize()
{
	User u1("G", "Ger", "123");
	User u2("S", "Sve", "qwe");

	std::pair<std::string, User> new_pair = std::make_pair("Ger", u1);
	users_map.insert(new_pair);

	std::pair<std::string, User> new_pair2 = std::make_pair("Sve", u2);
	users_map.insert(new_pair2);
}



bool database::isExistLogin(const std::string& login)
{
	auto result = users_map.find(login);
	if (result != users_map.end()) {
		return true;
	}
	return false;
}



bool database::isExistName(const std::string& name)
{
	//Range-based loop
	for (const auto& user : users_map) {
		if (user.second.getName() == name) {
			return true;
		}
	}
	return false;
}



bool database::isCorrectPassword(const std::string& login, const std::string& password)
{
	if (isExistLogin(login)) {
		if (users_map.at(login).getPassword() == password) {
			return true;
		}
	}
	return false;
}



void database::pushMessage(const Message& message)
{
	messages.push_back(message);
}



void database::loadMessages(const User& addressee, std::shared_ptr<std::list<Message> > destination)
{
	destination->clear();
	//Пройти по сообщениям в базе
	for (const auto& message : messages) {
		//Если адресат сообщения совпадает с заданным пользователем
		//или сообщение ВСЕМ
		if (message.getNameTo() == addressee.getName() ||
			(message.getNameTo() == MSG_TO_ALL)) {
			destination->push_back(message);
		}
	}
}



void database::addUser(const User& user)
{
	//Если пользователь ещё не в базе данных
	const std::string login = user.getLogin();
	if (!isExistLogin(login)) {
		std::pair<std::string, User> new_pair = std::make_pair(login, user);
		users_map.insert(new_pair);
	}
}


/**
Удалить из базы все сообщения, адресованные пользователю с заданным ником
\param[in] name Ник пользователя
*/
static void removeMessagesToUser(const std::string& name);

void database::removeUser(const User& user)
{
	removeMessagesToUser(user.getName());
	users_map.erase(user.getLogin());    //удалить по логину
}



std::string database::getNameByLogin(const std::string& login)
{
	if (isExistLogin(login)) {
		return users_map.at(login).getName();
	}
	return "";
}



size_t database::getNumberUser()
{
	return users_map.size();
}



void database::loadUserNames(std::shared_ptr<std::vector<std::string> > userNames)
{
	userNames->clear();
	for (const auto& user : users_map) {
		userNames->push_back(user.second.getName());
	}
}



static void testIsExistLogin();
static void testIsExistName();
static void testIsCorrectPassword();
static void testPushMessage();
static void testLoadMessages();
static void testAddUser();
static void testRemoveUser();
static void testGetNameByLogin();
static void testGetNumberUser();
static void testLoadUserNames();
static void testRemoveMessagesToUser();


void database::test()
{
	testIsExistLogin();
	testIsExistName();
	testIsCorrectPassword();
	testPushMessage();
	testLoadMessages();
	testAddUser();
	testRemoveUser();
	testGetNameByLogin();
	testGetNumberUser();
	testLoadUserNames();
	testRemoveMessagesToUser();
}



static void removeMessagesToUser(const std::string& name)
{
	//Удалить сообщение по условию true
	messages.remove_if([&name](const Message& message) {
		//Если адресат текущего сообщения совпадает с заданным именем
		if (message.getNameTo() == name) {
			return true;
		}
		return false;
		});
}



static void testIsExistLogin()
{
	//Поместить тестовое значение
	User user("name", "login", "password");
	std::pair<std::string, User> new_pair = std::make_pair("login", user);
	users_map.insert(new_pair);

	assert(database::isExistLogin(user.getLogin()) == true);
	assert(database::isExistLogin("incorrect_login") == false);

	//Очистить от тестовых значений
	users_map.clear();
	assert(users_map.empty() == true);
}



static void testIsExistName()
{
	//Поместить тестовое значение
	User user("name", "login", "password");
	std::pair<std::string, User> new_pair = std::make_pair("login", user);
	users_map.insert(new_pair);

	assert(database::isExistName(user.getName()) == true);
	assert(database::isExistName("incorrect_name") == false);

	//Очистить от тестовых значений
	users_map.clear();
	assert(users_map.empty() == true);
}



static void testIsCorrectPassword()
{
	//Поместить тестовое значение
	User user("name", "login", "password");
	std::pair<std::string, User> new_pair = std::make_pair("login", user);
	users_map.insert(new_pair);

	assert(database::isCorrectPassword(user.getLogin(), user.getPassword()) == true);
	assert(database::isCorrectPassword(user.getLogin(), "incorrect_password") == false);
	assert(database::isCorrectPassword("incorrect_login", user.getPassword()) == false);

	//Очистить от тестовых значений
	users_map.clear();
	assert(users_map.empty() == true);
}



static void testPushMessage()
{
	messages.clear();
	const std::string nameFrom = "nameFrom";
	const std::string nameTo = "nameTo";
	const std::string text = "Hello nameTo!";
	Message message(nameFrom, nameTo, text);	//Создать сообщение
	database::pushMessage(message);				//Поместить в базу сообщений
	assert(messages.front().getNameFrom() == nameFrom);
	assert(messages.front().getNameTo() == nameTo);
	assert(messages.front().getText() == text);

	//Очистить от тестовых значений
	messages.clear();
	assert(messages.empty() == true);
}



static void testLoadMessages()
{
	messages.clear();
	User u1("name_1", "login_1", "pass_1");
	User u2("name_2", "login_2", "pass_2");

	//Создать сообщения
	Message messageU1_U2(u1.getName(), u2.getName(), "U1 -> U2");
	Message messageU2_U1(u2.getName(), u1.getName(), "U2 -> U1");
	Message messageU1_ALL(u1.getName(), MSG_TO_ALL, "U1 -> ALL");
	//Поместить сообщения в базу данных
	database::pushMessage(messageU1_U2);
	database::pushMessage(messageU2_U1);
	database::pushMessage(messageU1_ALL);

	//Укзатель на сообщения конкретному пользователю
	auto messagesToUser = std::make_shared<std::list<Message> >();

	database::loadMessages(u1, messagesToUser);	//Заполнить вектор сообщениями адресату
	assert(messagesToUser->size() == 2);
	assert(messagesToUser->front().getNameFrom() == u2.getName());
	assert(messagesToUser->front().getNameTo() == u1.getName());
	assert(messagesToUser->front().getText() == "U2 -> U1");
	assert(messagesToUser->back().getNameFrom() == u1.getName());
	assert(messagesToUser->back().getNameTo() == MSG_TO_ALL);
	assert(messagesToUser->back().getText() == "U1 -> ALL");

	database::loadMessages(u2, messagesToUser);
	assert(messagesToUser->size() == 2);
	assert(messagesToUser->front().getNameFrom() == u1.getName());
	assert(messagesToUser->front().getNameTo() == u2.getName());
	assert(messagesToUser->front().getText() == "U1 -> U2");
	assert(messagesToUser->back().getNameFrom() == u1.getName());
	assert(messagesToUser->back().getNameTo() == MSG_TO_ALL);
	assert(messagesToUser->back().getText() == "U1 -> ALL");

	//Очистить от тестовых значений
	messages.clear();
	assert(messages.empty() == true);
}



static void testAddUser()
{
	//Поместить тестовое значение
	User user("name", "login", "password");
	database::addUser(user);
	assert(database::isExistName(user.getName()) == true);
	assert(database::isExistLogin(user.getLogin()) == true);
	assert(database::isCorrectPassword(user.getLogin(), user.getPassword()) == true);
	//Очистить от тестовых значений
	users_map.clear();
	assert(users_map.empty() == true);
}



static void testRemoveUser()
{
	//Поместить тестовое значение
	User user("name", "login", "password");
	database::addUser(user);
	database::removeUser(user);

	assert(users_map.empty() == true);
	assert(database::isExistName(user.getName()) == false);
	assert(database::isExistLogin(user.getLogin()) == false);
	assert(database::isCorrectPassword(user.getLogin(), user.getPassword()) == false);

	//Очистить от тестовых значений
	users_map.clear();
	assert(users_map.empty() == true);
}



static void testGetNameByLogin()
{
	//Поместить тестовое значение
	User user("name", "login", "password");
	std::pair<std::string, User> new_pair = std::make_pair("login", user);
	users_map.emplace(new_pair);

	assert(database::getNameByLogin(user.getLogin()) == user.getName());
	assert(database::getNameByLogin("Not_Exist") == "");
	//Очистить от тестовых значений
	users_map.clear();
	assert(users_map.empty() == true);
}



static void testGetNumberUser()
{
	//Поместить тестовое значение
	User user("name", "login", "password");
	std::pair<std::string, User> new_pair = std::make_pair("login", user);
	users_map.insert(new_pair);
	assert(database::getNumberUser() == 1);

	users_map.clear();
	assert(users_map.empty() == true);
}



static void testLoadUserNames()
{
	//Поместить тестовое значение
	User user_1("user_1", "login_1", "password_1");
	std::pair<std::string, User> new_pair = std::make_pair("login_1", user_1);
	users_map.insert(new_pair);

	User user_2("user_2", "login_2", "password_2");
	std::pair<std::string, User> new_pair2 = std::make_pair("login_2", user_2);
	users_map.insert(new_pair2);
	
	//Указатель на вектор сообщений конкретному пользователю
	auto userNames = std::make_shared<std::vector<std::string> >();

	database::loadUserNames(userNames);
	assert(userNames->size() == 2);
	assert(userNames->at(0) == user_1.getName());
	assert(userNames->at(1) == user_2.getName());

	//Очистить от тестовых значений
	users_map.clear();
	assert(users_map.empty() == true);
}



static void testRemoveMessagesToUser()
{
	messages.clear();
	User u1("name_1", "login_1", "pass_1");
	User u2("name_2", "login_2", "pass_2");

	//Создать сообщения
	Message messageU1_U2(u1.getName(), u2.getName(), "U1 -> U2");
	Message messageU2_U1(u2.getName(), u1.getName(), "U2 -> U1");
	Message messageU1_ALL(u1.getName(), MSG_TO_ALL, "U1 -> ALL");
	//Поместить сообщения в базу данных
	database::pushMessage(messageU1_U2);
	database::pushMessage(messageU2_U1);
	database::pushMessage(messageU1_ALL);

	removeMessagesToUser(u1.getName());

	for (auto& message : messages) {
		//Нет сообщений адресованных пользователю u1
		assert((message.getNameTo() == u1.getName()) == false);
	}
	//Очистить от тестовых значений
	messages.clear();
	assert(messages.empty() == true);
}