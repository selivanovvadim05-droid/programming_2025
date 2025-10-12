#include <iostream>

int main() {
	setlocale(LC_ALL, "RU");
	float x, y, s;
	std::cout << "левая граница ";
	std::cin >> x;	// тип переменной float

	std::cout << "правая граница ";
	std::cin >> y;	// тип переменной float

	s = (x + y) / 2;	//тип переменной float

	std::cout << "Середина интервала [" << x << "," << y << "] равна " << s << std::endl;	//середина интервала 
	std::cout << "float takes " << x + y << " bytes. Min = " << FLT_MIN << " Max = " << FLT_MAX << std::endl;	// минимальный и максимальный объем переменых x, y
	return 0;

}