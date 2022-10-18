#pragma once
#ifndef ERRORSLIB_H
#define ERRORSLIB_H
#include <string>
#include <vector>
class Errors
{
private:
	int value;
	std::vector<std::string> errorVector;
public:
	Errors(std::vector<std::string> vector_);
	int getValue(); 
	void setValue(int value_);
	std::string getMessageOf(int value_);
	std::string getMessage();
	void setMessage(int value_, std::string message_);
	void printMessageOf(int value_);
	void printMessage();
	void setErrorVector(std::vector<std::string> vector_);
};
#endif // ! ERRORSLIB_H
