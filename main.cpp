#include <iostream>
#include <windows.h>

#include "DataBase.h"
#include "Chat.h"

/**
Запустить тесты модулей программы
*/
static void test();


int main()
{
	//Для корректного ввода/вывода кириллицы в консоль
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	try {
		test();
		database::initialize();

		std::shared_ptr<bool> isRun = std::make_shared<bool>(true);
		Chat::getInstance()->attach(isRun);

		while (*isRun) {
			Chat::getInstance()->process();
		}
	}
	catch (std::bad_alloc& error) {
		std::cerr << "Ошибка выделения памяти: " << error.what() << std::endl;
	}
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Неопределённое исключение" << std::endl;
	}
	return EXIT_SUCCESS;
}



static void test()
{
	user::test();
	message::test();
	database::test();
}