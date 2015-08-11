#include "VfsFolderInfo.h"
#include "VfsFileInfo.h"
#include "VfsRepository.h"

using namespace std;

VfsFolderInfo::VfsFolderInfo(string nodename, string nodepath): VfsNodeInfo(nodename){
	node_path = nodepath;
}

void VfsFolderInfo::getHeader(HeaderRecord& header){
	//strcpy(header.node_name, get_nodename.c_str());
	header.node_type = 1;
}

void VfsFolderInfo::addChild(VfsFolderInfo* f){
	//cout << "addingchild\n";
	subfolder.push_back(f);
}

void VfsFolderInfo::setParent(VfsFolderInfo* p){
	//cout <<"settingparent\n";
	parentfolder = p;
}

int VfsFolderInfo::get_nodetype(){
	return 1;
}

void VfsFolderInfo::printChild(vector<string> &content){
	for(int i = 0; i < subfolder.size(); i++){
		string nodename = subfolder[i]->get_nodename();
		string folderpath = subfolder[i]->getPath();
		stringstream str;
		str << folderpath << "/" << nodename << "/";
		string finalpath = str.str();
		content.push_back(finalpath);
		//content.push_back(subfolder[i]->getPath());
	}
	
	for(int i = 0; i < subfiles.size(); i++){
		//cout << "subfiles.size() " << subfiles.size() << endl;
		string nodename_file = subfiles[i]->get_nodename();
		string nodename_folder = get_nodename();
		string folderpath = getPath();
		stringstream str;
		//cout << nodename_file << " " << nodename_folder << " " << folderpath << endl;
		str << folderpath << "/" << nodename_folder << "/" << nodename_file;
		string finalpath = str.str();
		//cout << finalpath << endl;
		content.push_back(finalpath);
	}
}

string VfsFolderInfo::getPath(){
	return node_path;
}

void VfsFolderInfo::copyInFolder(string hostname, string vfs_filename, VfsFileInfo* fileinfo){
	//cout <<"filename " << filename << endl;
	//VfsFileInfo *fileinfo = new VfsFileInfo(filename);
	subfiles.push_back(fileinfo);
	fileinfo->copyInFileInfo(hostname,vfs_filename);
}

void VfsFolderInfo::copyOutFolder(string hostname, string vfsfilepath, string filename){
	//cout <<"subfiles.size() " << subfiles.size() << endl;
	for(int i = 0; i < subfiles.size(); i++){
		//cout << subfiles[i]->get_nodename() << endl;
		if(subfiles[i]->get_nodename() == filename){
			//cout << subfiles[i]->get_nodename() << endl;
			subfiles[i]->copyOutFileInfo(hostname, vfsfilepath);
			break;
		}
	}
}

void VfsFolderInfo::createFileInfoLink(VfsFileInfo* fileinfo){
	subfiles.push_back(fileinfo);
}






