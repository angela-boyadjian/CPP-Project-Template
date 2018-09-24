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
	void createSubDir(bool);
	void printNoInputErrorMsg();
	void createTestFile();
	void generateCmakeTest();
	void generateCmake();
	void generateMakefile();
	void generateMakefileCPP();
	void createFiles();
	void addFileContent(std::string const &, bool);
	void addFileContentC(std::string const &, bool);
	void getProjectName();
	bool getProjectType();
	void createFilesC();
	void getFileName();
	void getBinaryName();
	bool getUTInfo();
	bool getCmakeInfo();
	void copyCatch();
	std::string _projectName;
	std::string _filename;
	std::string _binaryName;
};

#endif /* !APPLICATION_HPP_ */
