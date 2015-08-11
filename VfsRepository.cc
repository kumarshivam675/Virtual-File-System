#include "VfsRepository.h"
#include "VfsNodeInfo.h"
#include "VfsFolderInfo.h"
#include "VfsFileInfo.h"
#include "PathString.h"
#include "vfs_errors.h"
#include "vfs_errors_def.h"
#include<exception>
#include<cstring>
#include<sstream>

using namespace std;

VfsRepository::VfsRepository(){

}

/*VfsRepository::VfsRepository(string reponame,string extern_path){
	repo_name = reponame;
	repo_file_path = extern_path;
}*/

void VfsRepository::create(string reponame, string repo_filepath){
	repo_name = reponame;
	repo_file_path = repo_filepath;
	num_nodes = 0;
	fstream fout;
	fout.open(repo_file_path, ios::out | ios::binary);
	if( !fout.good() ){
		throw VFS_CREATE_01;
	}
	fout.write((char*)&num_nodes, sizeof(int));
	HeaderRecord header;
	for(int i = 0; i < MAX_NODES; i++)
		fout.write((char*)&header, sizeof(HeaderRecord));
	fout.close();
}

void VfsRepository::open(string reponame, std::string repo_filepath){
	status = OPEN;
	repo_name = reponame;
	repo_file_path = repo_filepath;
	vfsmap.clear();
	fstream fin;
	HeaderRecord header;
	fin.open(repo_file_path, ios::in | ios::binary);
	if( !fin.good() ){
		throw VFS_OPEN_01;
		//cout << "Stream not good " << endl;
		//exit(1);
	}
	fin.read((char*)&num_nodes, sizeof(int));
	for(int i = 0; i < num_nodes; i++){
		fin.read((char*)&header, sizeof(HeaderRecord));
		string nodename(header.node_name);
		if(header.node_type == 1){
			string folderpath(header.folder_path);
			if(nodename == "")
				makeDir("", "");
			else{
				PathString p (folderpath,"/");	
				string foldername = p.getLast();
				string newfolder_path = p.excludeLast();
				makeDir(newfolder_path, foldername);
			}
		}
		
		else{
			//cout << nodename << " " << header.size << " " << header.offset << " " << header.folder_path << " " << endl;
			PathString p (header.folder_path,"/");
			string folderpath = p.excludeLast();
			map<string, VfsNodeInfo*>::iterator it;
			it = vfsmap.find(folderpath);
			if(it != vfsmap.end()){
				VfsFileInfo* fileinfo = new VfsFileInfo(nodename,header.size, header.offset);
				vfsmap[header.folder_path] = fileinfo;
				dynamic_cast<VfsFolderInfo*>(it->second)->createFileInfoLink(fileinfo);
			}
		}
	}
	fin.close();
}



void VfsRepository::close(){
	if(status == CLOSED)
		throw VFS_GEN_01;
	fstream fout;
	fout.open(repo_file_path, ios::ate | ios::out | ios::in | ios::binary);
	if(fout.fail()){
		throw VFS_CLOSE_01;
	}
	//cout << fout.tellp() << endl;	
	fout.seekp(0,ios::beg);
	//cout << fout.tellp() << endl;	
	num_nodes = vfsmap.size();
	//cout << "numnodes " << num_nodes << endl;
	fout.write((char*)&num_nodes, sizeof(int));
	map<string, VfsNodeInfo*>::iterator it;
	for(it = vfsmap.begin(); it != vfsmap.end(); it++){
		//cout << "in the loop" << fout.tellp() << endl;
		HeaderRecord header;
		strcpy(header.node_name, it->second->get_nodename().c_str());
		strcpy(header.folder_path, it->first.c_str());
		it->second->getHeader(header);
		fout.write((char*)&header, sizeof(HeaderRecord));
	}
	//cout << fout.tellp() << endl;
	int rem_header = MAX_NODES - num_nodes;
	HeaderRecord header1;
	for(int i = 0; i < rem_header; i++)
		fout.write((char*)&header1, sizeof(HeaderRecord));
	//cout << fout.tellp() << endl;
	vfsmap.clear();
	fout.close();
	
}


void VfsRepository::makeDir(string path, string folder_name){
	if(status == CLOSED)
		throw VFS_GEN_01;
	stringstream str, str_folderpath;
	str << path <<"/" << folder_name;
	string finalpath = str.str();
	map<string, VfsNodeInfo*>::iterator it;
	string fullname = path + "/" + folder_name;
	if(path == "" && folder_name == ""){
		if(vfsmap.find("") != vfsmap.end())
		throw VFS_MAKEDIR_02;
	}
		
	if(vfsmap.find(fullname) != vfsmap.end())
		throw VFS_MAKEDIR_02;
	it = vfsmap.find(path);
	if(it != vfsmap.end()){
		VfsFolderInfo* f = new VfsFolderInfo(folder_name, path);
		vfsmap[finalpath] = f;
		dynamic_cast<VfsFolderInfo*>(it->second)->addChild(f);
		f->setParent(dynamic_cast<VfsFolderInfo*>(it->second));
		//f->setParent(it->second);
	}
	
	else if(path =="" && folder_name == ""){
		VfsFolderInfo* f = new VfsFolderInfo(folder_name, "");
		vfsmap[""] = f;
	}
	
	/*else if(path =="" && folder_name != ""){
		VfsFolderInfo* rootfolder = new VfsFolderInfo("", "");
		vfsmap[""] = rootfolder;
		VfsFolderInfo* childfolder = new VfsFolderInfo(folder_name, "");
		stringstream str1;
		str1 << "/" << folder_name;
		string temp = str1.str();
		vfsmap[temp] = childfolder;
		rootfolder->addChild(childfolder);
		childfolder->setParent(rootfolder);
	}*/
	else
		throw VFS_MAKEDIR_01;
}

void VfsRepository::list(string path, vector<string> &content){
	if(status == CLOSED)
		throw VFS_GEN_01;
	if(path == "/")
		path = "";
	map<string, VfsNodeInfo*>::iterator it;
	it = vfsmap.find(path);
	if(it != vfsmap.end()){
		dynamic_cast<VfsFolderInfo*>(it->second)->printChild(content);
	}
	else
		throw VFS_LISTDIR_01;
}

void VfsRepository::copyIn(string host_path, string vfs_path){
	if(status == CLOSED)
		throw VFS_GEN_01;
	PathString p (vfs_path,"/");
	string folder_path = p.excludeLast();
	string file_name = p.getLast();
	if(vfsmap.find(vfs_path) != vfsmap.end())
		throw VFS_COPYIN_02;
	map<string, VfsNodeInfo*>::iterator it;
	it = vfsmap.find(folder_path);
	if(it != vfsmap.end()){
		VfsFileInfo* fileinfo = new VfsFileInfo(file_name);
		vfsmap[vfs_path] = fileinfo;
		dynamic_cast<VfsFolderInfo*>(it->second)->copyInFolder(host_path, repo_file_path, fileinfo);
	}
	else
		throw VFS_COPYIN_01;
}

void VfsRepository::copyOut(string vfs_path, string host_path){
	if(status == CLOSED)
		throw VFS_GEN_01;
	//cout << "Welcome\n";
	map<string, VfsNodeInfo*>::iterator it;
	it = vfsmap.find(vfs_path);
	PathString p (vfs_path,"/");
	string folder_name = p.excludeLast();
	string file_name = p.getLast();
	if(it != vfsmap.end()){
		//cout << "found the file\n";
		map<string, VfsNodeInfo*>::iterator it1;
		it1 = vfsmap.find(folder_name);
		if(it1 != vfsmap.end()){
			//cout <<"foundthe folder containing the file\n";
			dynamic_cast<VfsFolderInfo*>(it1->second)->copyOutFolder(host_path, repo_file_path, file_name);
		}
	}
	else
		throw VFS_COPYOUT_01;
}
	
	
	
	
	
	
	
