//VfsRepository.h

#ifndef VFSREPOSITORY_H
#define VFSREPOSITORY_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>

class VfsNodeInfo;

const int MAX_NAME_LEN = 200;
const int MAX_PATH_LEN = 200;
const int MAX_NODES = 2000;

struct HeaderRecord{
	char node_name[MAX_NAME_LEN];
	int node_type;
	long offset;
	long size;
	char folder_path[MAX_PATH_LEN];
};

class VfsRepository{
	int num_nodes;
	std::string repo_name;
	enum repo_status { CLOSED = 0, OPEN } status;
	std::string repo_file_path;
	std::map< std::string,VfsNodeInfo*> vfsmap;
public:
	VfsRepository();
	//VfsRepository(std::string reponame, std::string extern_path);
	void create(std::string reponame, std::string filename);
	void open(std::string reponame, std::string filename);
	void close();
	void makeDir(std::string path, std::string folder_name);
	void list(std::string arg1, std::vector<std::string> &content);
	void copyIn(std::string arg1, std::string arg2);
	void copyOut(std::string arg1, std::string arg2);
	//void loadHeader();
	//void saveHeader();
	
};

#endif
