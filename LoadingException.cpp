#include "LoadingException.h"
#include <iostream>
#include <string>

LoadingException::LoadingException(const std::string& path)
{
	this->msg = "Loading assets failed at: " + path;
}

LoadingException::LoadingException(const std::string& path, int type)
{
	this->msg = "Game failed at: " + path + ", error type: " + std::to_string(type);
}

const char* LoadingException::what()
{
	return (this->msg).c_str();
}
