/*
** EPITECH PROJECT, 2018
** CPP-Project-Template
** File description:
** Application
*/

#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>

#include "Application.hpp"

namespace fs = std::experimental::filesystem;
//
// ──────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: C L A S S :   A P P L I C A T I O N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────
//
Application::Application()
{
}

Application::~Application()
{
}

//
// ─── RUN ────────────────────────────────────────────────────────────────────────
//
void Application::runApp()
{
	getProjectName();
	createProjectDir();
	createSubDir();
	getFileName();
	createFiles();
	getBinaryName();
	generateCmake();
}

//
// ─── CREATE ─────────────────────────────────────────────────────────────────────
//
void Application::createProjectDir()
{
	if (!fs::is_directory(_projectName) or !fs::exists(_projectName))
		fs::create_directory(_projectName);
}

void Application::createSubDir()
{
	std::string path = _projectName + "/srcs";
	fs::create_directory(path);
	path.clear();
	path = _projectName + "/include";
	fs::create_directory(path);
	path.clear();
	path = _projectName + "/tests";
	fs::create_directory(path);
}

void Application::createFiles()
{
	std::string path = _projectName + "/srcs/main.cpp";

	std::fstream file(path, std::ios::out | std::ios::app);
	file << "/*\n** EPITECH PROJECT, 2018\n** " << _projectName
		<< "\n** File description:\n** main" << "\n*/\n\n";
	file << "#include \"" << _filename << ".hpp\"\n\n"
		<<"int main(int ac, char **av)\n{\n\t\n\treturn 0;\n}";
	file.close();
	path.clear();
	path = _projectName + "/srcs/" + _filename + ".cpp";
	addFileContent(path, false);
	path.clear();
	path = _projectName + "/include/" + _filename + ".hpp";
	addFileContent(path, true);
}

void Application::generateCmake()
{
	std::string path = _projectName + "/CMakeLists.txt";
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "cmake_minimum_required(VERSION 3.0)\n\nproject("
		<< _binaryName << ")\n\nadd_definitions(\"-std=c++11\")\n\n"
		<< "set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)\n\n"
		<< "set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})\n"
		<< "set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})\n"
		<< "include_directories(include)\n\n" << "add_executable(${PROJECT_NAME}\n"
		<< "\tsrcs/main.cpp\n\tsrcs/" << _filename << ".cpp\n"
		<< "\tinclude/" << _filename << ".hpp\n)\n\n"
		<< "target_link_libraries(${PROJECT_NAME} stdc++fs)";
}

//
// ─── GET INFO FROM USER ─────────────────────────────────────────────────────────
//
void Application::getProjectName()
{
	std::string input;

	std::cout << "Project name: ";
	std::getline(std::cin, input);
	_projectName = input;
}

void Application::getFileName()
{
	std::string input;

	std::cout << "File name: ";
	std::getline(std::cin, input);
	_filename = input;
}

void Application::getBinaryName()
{
	std::string input;

	std::cout << "Binary name: ";
	std::getline(std::cin, input);
	_binaryName = input;
}

//
// ─── ADD CONTENT TO FILE ────────────────────────────────────────────────────────
//
void Application::addFileContent(std::string const &path, bool isHeader)
{
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "/*\n** EPITECH PROJECT, 2018\n** " << _projectName
		<< "\n** File description:\n** " << _filename << "\n*/\n\n";

	if (!isHeader) {
		file << "#include \"" << _filename << ".hpp\"\n\n";
		file << _filename << "::" << _filename << "()\n{\n}\n\n";
		file << _filename << "::" << "~" << _filename << "()\n{\n}\n";
	} else {
		std::string s = _filename;
		transform(s.begin(), s.end(), s.begin(), toupper);
		file << "#ifndef " << s << "_HPP\n#define " << s << "_HPP\n\nclass "
		<< _filename << " {\npublic:\n\t" << _filename << "();\n\t~"
		<< _filename << "();\nprotected:\nprivate:\n};\n\n" << "#endif /* !" << s << "_HPP_ */";
	}
	file.close();
}