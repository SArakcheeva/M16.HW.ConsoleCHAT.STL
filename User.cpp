#include "User.h"

#include <assert.h>


//Не требуется инициализировать нулевой строкой объекты типа string
//User::User() : name_(""), login_(""), password_("")
User::User() = default;



User::User(const std::string& name,
	const std::string& login,
	const std::string& password) :
	name_(name), login_(login), password_(password)
{
}



User::User(const User& u)
{
	this->name_ = u.name_;
	this->login_ = u.login_;
	this->password_ = u.password_;
}



bool User::operator==(User other) const
{
	//Объекты равны если совпадает Логин
	if (login_ == other.login_) {
		return true;
	}
	return false;
}



std::string User::getName() const
{
	return name_;
}



std::string User::getLogin() const
{
	return login_;
}



std::string User::getPassword() const
{
	return password_;
}



void User::setName(const std::string& name)
{
	name_ = name;
}



void User::setLogin(const std::string& login)
{
	login_ = login;
}



void User::setPassword(const std::string& password)
{
	password_ = password;
}



void User::reset()
{
	name_.clear();
	login_.clear();
	password_.clear();
}



void user::test()
{
	//Тест конструктора по-умолчанию и get-методов
	User user1;
	assert(user1.getName() == "");
	assert(user1.getLogin() == "");
	assert(user1.getPassword() == "");

	//Тест параметризованного конструктора и get-методов
	std::string name = "name";
	std::string login = "login";
	std::string password = "password";

	User user(name, login, password);
	assert(user.getName() == name);
	assert(user.getLogin() == login);
	assert(user.getPassword() == password);

	//Тест set-методов
	std::string new_name = "new_name";
	std::string new_login = "new_login";
	std::string new_password = "new_password";
	user.setName(new_name);
	user.setLogin(new_login);
	user.setPassword(new_password);
	assert(user.getName() == new_name);
	assert(user.getLogin() == new_login);
	assert(user.getPassword() == new_password);

	//Тест пегруженного оператора ==
	User user2(name, login, password);
	User user3(name, login, new_password);
	User user4(new_name, login, new_password);

	assert((user == user2) == false);
	assert((user2 == user3) == true);
	assert((user2 == user4) == true);

	//Tecт reset()
	user.reset();
	assert(user.getName() == "");
	assert(user.getLogin() == "");
	assert(user.getPassword() == "");
}