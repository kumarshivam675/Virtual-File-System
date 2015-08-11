#include "VfsNodeInfo.h"
#include "VfsRepository.h"
#include "VfsFolderInfo.h"

using namespace std;

VfsNodeInfo::VfsNodeInfo(std::string nodename){
	node_name = nodename;

}

VfsNodeInfo::VfsNodeInfo(){

}

void VfsNodeInfo::getHeader(HeaderRecord& header){

}

string VfsNodeInfo::get_nodename(){
	//cout <<"nodename" << node_name << endl;
	return node_name;
}

/*void VfsNodeInfo::addChild(VfsFolderInfo* f){

}*/
