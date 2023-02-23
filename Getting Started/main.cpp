#include "iostream"

void main()
{
	std::string outputMessage = "Hi! I'm Tiyani.";

	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << outputMessage << std::endl;
		}
		std::system("PAUSE");
		outputMessage = "Coding is awesome!";
	}
}