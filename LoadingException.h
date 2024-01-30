#pragma once
#include <stdio.h>
#include <iostream>
#include <string>

class LoadingException : public std::exception
{
private:
	std::string msg;
public:
	LoadingException(const std::string& path);
	LoadingException(const std::string& path, int type);
	const char* what();
};

