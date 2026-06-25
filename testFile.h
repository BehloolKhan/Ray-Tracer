//This file will contain the methods used to test certain methods
//

#ifndef TEST_FILE_H
#define TEST_FILE_H
#include <tuple>
#include <iostream>

void testFile(std::tuple<int, int, int>& color_) {
	std::cout << "current R: " << std::get<0>(color_) << '\n';
	std::cout << "current G: " << std::get<1>(color_) << '\n';
	std::cout << "current B: " << std::get<2>(color_) << '\n';
}
#endif