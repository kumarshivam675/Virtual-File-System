//VfsFileInfo

#ifndef VFSFILEINFO_H
#define VFSFILEINFO_H

#include "VfsNodeInfo.h"

class VfsFile;
class VfsFolderInfo;
struct HeaderRecord;

class VfsFileInfo:public VfsNodeInfo{
	long file_bytes;
	long file_offset;
	VfsFile* vfsfile;
	VfsFolderInfo* vfsfolder;
public:
	virtual void getHeader(HeaderRecord& header);
	VfsFileInfo();
	VfsFileInfo(std::string nodename);	
	VfsFileInfo(std::string nodename,long filesbytes, long fileoffset);
	int get_nodetype();
	void copyInFileInfo(std::string hostname, std::string vfsname);
	void copyOutFileInfo(std::string hostname, std::string vfsname);
};

#endif
