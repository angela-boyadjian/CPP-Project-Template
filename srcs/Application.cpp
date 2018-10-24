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
#include "unistd.h"
#include <stdlib.h>

#include "Application.hpp"

namespace fs = std::experimental::filesystem;
//
// ──────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: C L A S S :   A P P L I C A T I O N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────
//

//
// ─── RUN ────────────────────────────────────────────────────────────────────────
//
void Application::runApp()
{
	if (getProjectType()) {
		getProjectName();
		createProjectDir();
		createSubDir(true);
		getFileName();
		createFilesC();
		getBinaryName();
		generateMakefile();
		std::cout << "\033[1;30;34m...Generating Makefile... \033[0m" << std::endl;
		sleep(1);
	} else {
		getProjectName();
		createProjectDir();
		createSubDir(false);
		getFileName();
		createFiles();
		getBinaryName();
		if (getCmakeInfo()) {
			generateCmake();
			std::cout << "\033[1;30;33m...Generating Cmake... \033[0m" << std::endl;
			sleep(1);
		} else {
			generateMakefileCPP();
			std::cout << "\033[1;30;33m...Generating Makefile... \033[0m" << std::endl;
			sleep(1);
		}
		if (getUTInfo()) {
			std::cout << "\033[1;30;34m...Initializing Unit Tests... \033[0m" << std::endl;
			copyCatch();
			createTestFile();
			generateCmakeTest();
			sleep(1);
		}
	}
	std::cout << "\033[1;30;32m--- DONE ---\033[0m" << std::endl;
}

//
// ─── CREATE ─────────────────────────────────────────────────────────────────────
//
void Application::createProjectDir()
{
	if (!fs::is_directory(_projectName) or !fs::exists(_projectName))
		fs::create_directory(_projectName);
	else {
		std::cerr << "\033[1;31mFAILURE: Directory already exists.\033[0m\n";
		exit(EXIT_FAILURE);
	}
}

void Application::createSubDir(bool isC)
{
	std::string path = _projectName + "/srcs";
	fs::create_directory(path);
	path.clear();
	path = _projectName + "/includes";
	fs::create_directory(path);
	path.clear();
	path = _projectName + "/tests";
	fs::create_directory(path);
	path.clear();
	if (!isC) {
		path = _projectName + "/catch";
		fs::create_directory(path);
	}
}

void Application::createFiles()
{
	std::string path = _projectName + "/srcs/main.cpp";

	std::fstream file(path, std::ios::out | std::ios::app);
	file << "/*\n** EPITECH PROJECT, 2018\n** " << _projectName
		<< "\n** File description:\n** main" << "\n*/\n\n";
	file << "#include \"" << _filename << ".hpp\"\n\n"
		<<"int main(int ac, char **av)\n{\n\t(void)av;\n\t(void)ac;\n\treturn 0;\n}";
	file.close();
	path.clear();
	path = _projectName + "/srcs/" + _filename + ".cpp";
	addFileContent(path, false);
	path.clear();
	path = _projectName + "/includes/" + _filename + ".hpp";
	addFileContent(path, true);
}

void Application::createFilesC()
{
	std::string path = _projectName + "/srcs/main.c";

	std::fstream file(path, std::ios::out | std::ios::app);
	file << "/*\n** EPITECH PROJECT, 2018\n** " << _projectName
		<< "\n** File description:\n** main" << "\n*/\n\n";
	file << "#include \"" << _filename << ".h\"\n\n"
		<<"int main(int ac, char **av)\n{\n\t(void)av;\n\t(void)ac;\n\treturn (0);\n}";
	file.close();
	path.clear();
	path = _projectName + "/srcs/" + _filename + ".c";
	addFileContentC(path, false);
	path.clear();
	path = _projectName + "/includes/" + _filename + ".h";
	addFileContentC(path, true);
}

void Application::createTestFile()
{
	std::string path = _projectName + "/tests/test.cpp";
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "#define CATCH_CONFIG_MAIN\n#include \"catch.hpp\"\n"
		<< "#include \"../srcs/" << _filename << ".cpp\"\n#include <iostream>\n\n"
		<< "// Example (not working)\n\n" << "TEST_CASE(\""
		<< _filename << " getters\", \"test1\") {\n\t" << _filename
		<< " obj(\"Lama\", 3);\n\n\tREQUIRE(obj.function() == 3);\n\t"
		<< "REQUIRE(obj.function(5) == 5);\n\t"
		<< "REQUIRE(obj.function() == \"lama\");\n}";
	file.close();
}

void Application::generateCmake()
{
	std::string path = _projectName + "/CMakeLists.txt";
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "cmake_minimum_required(VERSION 3.0)\n\nproject("
		<< _binaryName << ")\n\nadd_definitions(\"-std=c++14\")\n\n"
		<< "set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)\n\n"
		<< "set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})\n"
		<< "set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})\n"
		<< "include_directories(includes)\n\n" << "add_executable(${PROJECT_NAME}\n"
		<< "\tsrcs/main.cpp\n\tsrcs/" << _filename << ".cpp\n"
		<< "\tincludes/" << _filename << ".hpp\n)\n\n"
		<< "target_link_libraries(${PROJECT_NAME} stdc++fs)";
}

void Application::generateCmakeTest()
{
	std::string path = _projectName + "/tests/CMakeLists.txt";
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "cmake_minimum_required(VERSION 3.0)\n\nproject(cmake_test"
		<< ")\n\n# Prepare \"Catch\" library for other executables\n"
		<< "set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../catch)\n"
		<< "add_library(Catch INTERFACE)\n"
		<< "target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})\n\n"
		<< "# Make test executable\n"
		<< "include_directories(../includes)\n\n" << "add_library(func\n"
		<< "\t../srcs/" << _filename << ".cpp\n"
		<< "\tincludes/" << _filename << ".hpp\n)\n\n"
		<< "set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)\n"
		<< "add_executable(tests ${TEST_SOURCES})\n"
		<< "target_link_libraries(tests Catch)";
}

void Application::generateMakefile()
{
	std::string path = _projectName + "/Makefile";
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "##\n## EPITECH PROJECT, 2018\n## " << _projectName
		<< "\n## File description:\n## Makefile\n##\n\n"
		<< "CC\t=\tgcc\n\nCFLAGS\t+=\t-W -Wall -Wextra -Werror\n\n"
		<< "CFLAGS\t+=\t-I./includes\n\nNAME\t=\t" << _binaryName
		<< "\n\nDIR\t=\tsrcs/\n\nSRCS\t=\t$(DIR)main.c\t\\\n"
		<< "\t\t\t$(DIR)" << _filename << ".c\n\n"
		<< "OBJS\t=\t$(SRCS:.c=.o)\n\n%.o: %.c\n"
		<< "\t\t@printf \"[\\033[0;32mcompiled\\033[0m] % 29s\\n\" $< | tr ' ' '.'\n"
		<< "\t\t@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)\n\n"
		<< "EXEC:\t$(NAME)\n\n"
		<< "all: EXEC\n\n"
		<< "$(NAME):\t$(OBJS)\n\t\t@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)\n"
		<< "\t\t@printf \"[\\033[0;36mbuilt\\033[0m] % 32s\\n\" $(NAME) | tr ' ' '.'\n\n"
		<< "clean:\n\t\t@rm $(OBJS)\n"
		<< "\t\t@printf \"[\\033[0;31mdeleted\\033[0m] % 30s\\n\" $(OBJS) | tr ' ' '.'\n\n"
		<< "fclean:\tclean\n\t\t@rm $(NAME)\n\t\t"
		<< "@printf \"[\\033[0;31mdeleted\\033[0m] % 30s\\n\" $(NAME) | tr ' ' '.'\n\n"
		<< "re:\t\tfclean all\n\n"
		<< ".PHONY:	all exec clean fclean re";
}

void Application::generateMakefileCPP()
{
	std::string path = _projectName + "/Makefile";
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "##\n## EPITECH PROJECT, 2018\n## " << _projectName
		<< "\n## File description:\n## Makefile\n##\n\n"
		<< "CC\t=\tg++\n\nCFLAGS\t+=\t-W -Wall -Wextra -Werror -std=c++14\n\n"
		<< "CFLAGS\t+=\t-I./includes\n\nNAME\t=\t" << _binaryName
		<< "\n\nDIR\t=\tsrcs/\n\nSRCS\t=\t$(DIR)main.cpp\t\\\n"
		<< "\t\t\t$(DIR)" << _filename << ".cpp\n\n"
		<< "OBJS\t=\t$(SRCS:.cpp=.o)\n\n%.o: %.cpp\n"
		<< "\t\t@printf \"[\\033[0;32mcompiled\\033[0m] % 29s\\n\" $< | tr ' ' '.'\n"
		<< "\t\t@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)\n\n"
		<< "EXEC:\t$(NAME)\n\n"
		<< "all: EXEC\n\n"
		<< "$(NAME):\t$(OBJS)\n\t\t@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)\n"
		<< "\t\t@printf \"[\\033[0;36mbuilt\\033[0m] % 32s\\n\" $(NAME) | tr ' ' '.'\n\n"
		<< "clean:\n\t\t@rm $(OBJS)\n"
		<< "\t\t@printf \"[\\033[0;31mdeleted\\033[0m] % 30s\\n\" $(OBJS) | tr ' ' '.'\n\n"
		<< "fclean:\tclean\n\t\t@rm $(NAME)\n\t\t"
		<< "@printf \"[\\033[0;31mdeleted\\033[0m] % 30s\\n\" $(NAME) | tr ' ' '.'\n\n"
		<< "re:\t\tfclean all\n\n"
		<< ".PHONY:	all exec clean fclean re";
}

void Application::copyCatch()
{
	char *log = getlogin();

	std::string buff(log);
	std::string path = "/home/" + buff + "/Documents/save/catch";

	if (fs::exists(path))
		fs::copy(path, _projectName + "/catch");
	else
		std::cerr << "\033[1;31mFAILURE: catch directory not found.\033[0m\n";
}

//
// ─── GET INFO FROM USER ─────────────────────────────────────────────────────────
//
void Application::getProjectName()
{
	std::string input;

	std::cout << "\033[1;30;33mProject name: \033[0m";
	std::getline(std::cin, input);

	if (input.empty())
		printNoInputErrorMsg();
	_projectName = input;
}

void Application::getFileName()
{
	std::string input;

	std::cout << "\033[1;30;36mFile name: \033[0m";
	std::getline(std::cin, input);
	if (input.empty())
		printNoInputErrorMsg();
	_filename = input;
}

void Application::getBinaryName()
{
	std::string input;

	std::cout << "\033[1;30;35mBinary name: \033[0m";
	std::getline(std::cin, input);
	if (input.empty())
		printNoInputErrorMsg();
	_binaryName = input;
}

bool Application::getUTInfo()
{
	std::string input;

	std::cout << "\033[1;30;34mDo you use Catch for UT ? (y, n): \033[0m";
	std::getline(std::cin, input);
	if (input.empty())
		printNoInputErrorMsg();
	if (input[0] == 'y')
		return true;
	return false;
}

bool Application::getProjectType()
{
	std::string input;

	std::cout << "\033[1;30;35mIs your project in C or C++ ? (c, c++): \033[0m";
	std::getline(std::cin, input);
	if (input.empty())
		printNoInputErrorMsg();
	if (input[0] == 'c' and input[1] != '+')
		return true;
	return false;
}

bool Application::getCmakeInfo()
{
	std::string input;

	std::cout << "\033[1;30;33mDo you prefer a Cmake or a Makefile ? (c, m): \033[0m";
	std::getline(std::cin, input);
	if (input.empty())
		printNoInputErrorMsg();
	if (input[0] == 'c')
		return true;
	return false;
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
		file << _filename << "::" << "~" << _filename << "()\n{\n}";
	} else {
		std::string s = _filename;
		transform(s.begin(), s.end(), s.begin(), toupper);
		file << "#ifndef " << s << "_HPP\n#define " << s << "_HPP\n\nclass "
		<< _filename << " {\npublic:\n\t" << _filename << "();\n\t~"
		<< _filename << "();\nprotected:\nprivate:\n};\n\n" << "#endif /* !" << s << "_HPP_ */";
	}
	file.close();
}

void Application::addFileContentC(std::string const &path, bool isHeader)
{
	std::fstream file(path, std::ios::out | std::ios::app);

	file << "/*\n** EPITECH PROJECT, 2018\n** " << _projectName
		<< "\n** File description:\n** " << _filename << "\n*/\n\n";

	if (!isHeader) {
		file << "#include \"" << _filename << ".h\"\n\n";
	} else {
		std::string s = _filename;
		transform(s.begin(), s.end(), s.begin(), toupper);
		file << "#ifndef " << s << "_H\n#define " << s << "_H\n\n"
		<< "#endif /* !" << s << "_HPP_ */";
	}
	file.close();
}

//
// ─── ERROR HANDLING ─────────────────────────────────────────────────────────────
//
void Application::printNoInputErrorMsg()
{
	std::cerr << "\033[1;31mFAILURE: No user input.\033[0m\n";
	exit(EXIT_FAILURE);
}