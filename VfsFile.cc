#include "VfsFile.h"
#include "VfsFileInfo.h"
#include "vfs_errors.h"

using namespace std;

VfsFile::VfsFile(){

}

void VfsFile::saveInVfs(fstream& fout, fstream& fin, long &fileoffset, long &filebyteswritten){
	long totalfilesize = 0;
	long file_bytes;
	//int numnodes;
	//fout.read((char*)&numnodes,sizeof(int));
	//cout << numnodes <<fout.tellp() << endl;
	fout.seekp(0,ios::end);
	fileoffset = fout.tellp();
	//cout <<"offset " << fileoffset << endl;
	while(!fin.eof()){
		fin.read(data_bytes, DATABUFFERSIZE);
		file_bytes = fin.gcount();
		//cout << "file_bytes" << file_bytes << endl;
		//cout << "data_bytes" << data_bytes << endl;
		/*cout <<"again ";
		for(int i = 0 ; i < file_bytes; i++)
			cout << data_bytes[i];
		cout << endl;*/
		fout.write(data_bytes, file_bytes);
		totalfilesize += file_bytes;
		if(fin.eof())
			break;
	}
	filebyteswritten = totalfilesize;
	//cout << "filesize " << filebyteswritten << endl;
	fin.close();
	fout.close();
}

void VfsFile::exportfile(fstream& fout, fstream& fin, long fileoffset, long filebytes){
	long bytes_remaining = filebytes;
	//cout << "fileoffset " << fileoffset << endl;
	//cout << "filebytes " << filebytes << endl;
	fin.seekg(fileoffset, ios::beg);
	while(bytes_remaining > 0){
		if(bytes_remaining > 1024){
			fin.read(data_bytes, DATABUFFERSIZE);
			//cout << data_bytes << endl;
			fout.write(data_bytes, DATABUFFERSIZE);
		}
		
		else{
			fin.read(data_bytes, bytes_remaining);
			//cout << data_bytes << endl;
			fout.write(data_bytes, bytes_remaining);
		}
		bytes_remaining -= 1024;
		if(bytes_remaining < 0)
			break;
	}
	fin.close();
	fout.close();
}
		
		
		
		
		
		
