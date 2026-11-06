#include "Huffman.h"

#include <iostream>

void main2()
{
	Huffman h;

	h.GenerateTree("mississippi");

	std::cout << h.Encode("mips") << std::endl; // 100111010

	std::cout << h.Decode("101011") << std::endl; // psi

}
int main()
{
	main2();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}
