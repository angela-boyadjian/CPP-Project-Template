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
	void createFiles();
	void createHeaderFiles();
	void getProjectName();
	void getFileName();
	std::string _projectName;
	std::string _filename;
};

#endif /* !APPLICATION_HPP_ */
