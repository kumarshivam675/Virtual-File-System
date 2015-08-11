#include "VfsFileInfo.h"
#include "VfsFile.h"
#include "VfsFolderInfo.h"
#include "VfsRepository.h"
#include "vfs_errors.h"

using namespace std;

VfsFileInfo::VfsFileInfo(){
	//VfsNodeInfo();
}

VfsFileInfo::VfsFileInfo(string nodename): VfsNodeInfo(nodename){

}	

VfsFileInfo::VfsFileInfo(string nodename,long filesbytes, long fileoffset): VfsNodeInfo(nodename){
	//VfsNodeInfo(nodename);
	file_bytes = filesbytes;
	file_offset = fileoffset;
}

void VfsFileInfo::getHeader(HeaderRecord& header){
	header.offset = file_offset;
	header.size = file_bytes;
	header.node_type = 0;
}

int VfsFileInfo::get_nodetype(){
	return 0;
}

void VfsFileInfo::copyInFileInfo(string hostname, string vfsname){
	int numnodes;
	//cout <<"hostname " << hostname << endl;
	//cout <<"vfsname " << vfsname << endl;
	VfsFile* file = new VfsFile();
	vfsfile = file;
	fstream fin, fout;
	fin.open(hostname, ios::in | ios::binary);
	if(fin.fail()){
		throw VFS_COPYIN_03;
	}
	fout.open(vfsname, ios::in | ios::out | ios::binary);
	//fout.read((char*)&numnodes,sizeof(int));
	//cout <<numnodes << endl;
	file->saveInVfs(fout, fin, file_offset, file_bytes);
}

void VfsFileInfo::copyOutFileInfo(string hostname, string vfsname){
	//cout <<"hostname " << hostname << endl;
	//cout <<"vfsname " << vfsname << endl;
	VfsFile* file = new VfsFile();
	fstream fin, fout;
	fin.open(vfsname, ios::in | ios::out | ios::binary);
	fout.open(hostname, ios::out | ios::binary);
	if(fout.fail()){
		throw VFS_COPYOUT_02;
	}
	//fout.close();
	//fout.open(hostname, ios::in | ios::out | ios::binary);
	file->exportfile(fout, fin, file_offset, file_bytes);
}
	



	
