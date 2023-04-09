#include <iostream>
#include <windows.h>

#include "DataBase.h"
#include "Chat.h"

/**
��������� ����� ������� ���������
*/
static void test();


int main()
{
	//��� ����������� �����/������ ��������� � �������
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
		std::cerr << "������ ��������� ������: " << error.what() << std::endl;
	}
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (...) {
		std::cerr << "������������� ����������" << std::endl;
	}
	return EXIT_SUCCESS;
}



static void test()
{
	user::test();
	message::test();
	database::test();
}