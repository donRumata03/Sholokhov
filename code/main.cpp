#include <mylibs.hpp>
#include <Windows.h>
#include "art_parser.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	plot_sholokhov_data();
	// print(parse_text(s));
	
	return 0;
}

