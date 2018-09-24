/*
** EPITECH PROJECT, 2018
** CPP-Project-Template
** File description:
** Application
*/

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

class Application {
public:
	Application();
	~Application();
	void runApp();
private:
	void createProjectDir();
	void createSubDir();
	void createTestFile();
	void generateCmakeTest();
	void generateCmake();
	void createFiles();
	void addFileContent(std::string const &, bool);
	void getProjectName();
	void getFileName();
	void getBinaryName();
	bool getUTInfo();
	void copyCatch();
	std::string _projectName;
	std::string _filename;
	std::string _binaryName;
};

#endif /* !APPLICATION_HPP_ */
