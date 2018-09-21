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
	path.clear();
	path = _projectName + "/srcs/" + _filename + ".cpp";
	file.close();
	std::fstream file2(path, std::ios::out | std::ios::app);
	file2 << "<!--XML Document-->\n";
	file2 << "<?xml version='1.0'?>\n\n";
	file.close();
}

void Application::createHeaderFiles()
{
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