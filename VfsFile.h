//VfsFile.h

#ifndef VFSFILE_H
#define VFSFILE_H

#include<iostream>
#include<string>
#include<fstream>
int const DATABUFFERSIZE = 1024;

class VfsFileInfo;

class VfsFile{
	char data_bytes[1024];
	VfsFileInfo* vfsfile;
public:
	VfsFile();
	void exportfile(std::fstream& ext_file, std::fstream& repository, long fileoffset, long filebytes);
	void saveInVfs(std::fstream& repository,std::fstream& ext_file, long& file_offset, long& file_bytes_written);
};

#endif
