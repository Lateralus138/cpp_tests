#include "ErrorsLib.h"
#include <iostream>
Errors::Errors(std::vector<std::string> vector_)
{
	value = 0;
	vector_.insert(vector_.begin(), "Success");
	errorVector = vector_;
}
int Errors::getValue()
{
	return value;
}
void Errors::setValue(int value_)
{
	value = value_;
}
std::string Errors::getMessageOf(int value_)
{
	return errorVector[value_];
}
std::string Errors::getMessage()
{
	return errorVector[value];
}
void Errors::setMessage(int value_, std::string message_)
{
	errorVector[value_] = message_;
}
void Errors::printMessageOf(int value_)
{
	std::cerr << errorVector[value_] << '\n';
}
void Errors::printMessage()
{
	std::cerr << getMessage() << '\n';
}
void Errors::setErrorVector(std::vector<std::string> vector_)
{
	errorVector = vector_;
}