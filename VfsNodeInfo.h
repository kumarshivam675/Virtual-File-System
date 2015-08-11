//VfsNodeInfo

#ifndef VFSNODEINFO_H
#define VFSNODEINFO_H

#include<string>

class VfsFolderInfo;
class VfsRepository;
struct HeaderRecord;

class VfsNodeInfo{
	std::string node_name;
	enum node_type{ FILES, FOLDER };
	VfsRepository* vfsrepository;
public:
	virtual void getHeader(HeaderRecord& header);
	VfsNodeInfo();
	VfsNodeInfo(std::string nodename);
	std::string get_nodename();
	//virtual void addChild(VfsFolderInfo* f);
	//virtual void setParent(VfsFolderInfo* p);
	//virtual int get_nodetype();
};

#endif
