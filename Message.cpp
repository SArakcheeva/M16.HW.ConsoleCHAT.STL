#include "Message.h"

#include <assert.h>


Message::Message(const std::string& nameUserFrom,
	const std::string& nameUserTo,
	const std::string& text) :
	nameUserFrom_(nameUserFrom),
	nameUserTo_(nameUserTo),
	text_(text)
{
}



const std::string& Message::getNameFrom() const
{
	return nameUserFrom_;
}



const std::string& Message::getNameTo() const
{
	return nameUserTo_;
}



const std::string& Message::getText() const
{
	return text_;
}



void message::test()
{
	//Тест параметризованного конструктора и get-методов
	std::string nameUserFrom = "nameUserFrom";
	std::string nameUserTo = "nameUserTo";
	std::string text = "text";

	Message message(nameUserFrom, nameUserTo, text);
	assert(message.getNameFrom() == nameUserFrom);
	assert(message.getNameTo() == nameUserTo);
	assert(message.getText() == text);
}