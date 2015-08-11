// VfsCommand
#include <string>
#include <iostream>
#include<sstream>
#include "VfsCommand.h"
#include "VfsRepository.h"
#include "VfsNodeInfo.h"
#include "PathString.h"

using namespace std;

VfsCommand *VfsCommand::getVfsCommand( string cmdline, VfsRepository* repo, ostream& ostr )
{
	string cmd, arg1, arg2;
	VfsCommand *cmdObject;

	stringstream cmdstr(cmdline);
	
	cmdstr >> cmd >> arg1 >> arg2;
	// ostr << "cmd:" << cmd << " arg1:" << arg1 << " arg2:" << arg2 << endl;
	if( cmd == "quit" || cmd == "exit" ){
		cmdObject = (VfsCommand*) 0;
	} else if( cmd == "create" ){
		// Create and return specific object for the command
		cmdObject = new VfsCreateCommand( repo, arg1, arg2, ostr );
	} else if( cmd == "open" ){
		// Create and return specific object for the command
		cmdObject = new VfsOpenCommand( repo, arg1, arg2, ostr );
	} else if( cmd == "close" ){
		// Create and return specific object for the command
		cmdObject = new VfsCloseCommand(repo, ostr);
	} else if( cmd == "list" ){
		// Create and return specific object for the command
		cmdObject = new VfsListCommand( repo, arg1, ostr );
	} else if( cmd == "makedir" ){
		// Create and return specific object for the command
		cmdObject = new VfsMakeDirCommand( repo, arg1, ostr );
	} else if( cmd == "copyin" ){
		// Create and return specific object for the command
		cmdObject = new VfsCopyInCommand( repo, arg1, arg2, ostr );
	} else if( cmd == "copyout" ){
		// Create and return specific object for the command
		cmdObject = new VfsCopyOutCommand( repo, arg1, arg2, ostr );
	} else if( cmd == "move" ){
		// Create and return specific object for the command
		cmdObject = new VfsMoveCommand( repo, arg1, arg2, ostr );
	} else if( cmd == "cat" ){
		// Create and return specific object for the command
		cmdObject = new VfsCatCommand( repo, arg1, ostr  );
	}
	else{
		// Return error command object
		cmdObject = new VfsInvalidCommand(ostr);
	}
	return cmdObject;
}

//========================================================================

VfsCommand::VfsCommand(VfsRepository *repoptr, const char* cmdname, string arg1, string arg2, ostream& outputstream) : 
	repo(repoptr), command(cmdname), param1(arg1), param2(arg2), ostr(outputstream)
{
}

string VfsCommand::getCommand() const
{
	return command + " " + param1 + " " + param2;
}

//========================================================================

VfsInvalidCommand::VfsInvalidCommand(ostream& ostr) :
	VfsCommand(nullptr,"error", string(""), string(""), ostr)
{
}

int VfsInvalidCommand::doCommand()
{
	throw "Invalid command";
}

string VfsInvalidCommand::usage()
{
	return ("Commands: create open close list makedir copy move cat");
}

//========================================================================

VfsCreateCommand::VfsCreateCommand( VfsRepository* repo, string arg1, string arg2, ostream& ostr) :
	VfsCommand(repo, "create", arg1, arg2, ostr)
{
}

int VfsCreateCommand::doCommand()
{
	VfsRepository repo;
	repo.create(param1, param2);

	ostr << "VfsCreateCommand executed" << endl;
}

string VfsCreateCommand::usage()
{
	return ("create file-system-name file-system-path");
}

//========================================================================

VfsOpenCommand::VfsOpenCommand( VfsRepository* repo, string arg1, string arg2, ostream& ostr ) :
	VfsCommand(repo, "open", arg1, arg2, ostr )
{
}

int VfsOpenCommand::doCommand()
{
	repo->open(param1, param2);
	ostr << "VfsOpenCommand executed" << endl;
}

string VfsOpenCommand::usage()
{
	return ("open file-system-name file-system-path");
}

//========================================================================

VfsCloseCommand::VfsCloseCommand(VfsRepository* repo, ostream& ostr) :
	VfsCommand(repo, "close", string(""), string(""), ostr)
{
}

int VfsCloseCommand::doCommand()
{
	repo->close();
	ostr << "VfsCloseCommand executed" << endl;
}

string VfsCloseCommand::usage()
{
	return ("close");
}

//========================================================================

VfsMakeDirCommand::VfsMakeDirCommand( VfsRepository* repo, string arg1, ostream& ostr ) :
	VfsCommand(repo, "makedir", arg1, string(""), ostr )
{
}

int VfsMakeDirCommand::doCommand()
{
     PathString p (param1,"/");

     string path = p.excludeLast();

     string folder_name = p.getLast();

     repo->makeDir(path, folder_name);
	ostr << "VfsMakeDirCommand executed" << endl;
}

string VfsMakeDirCommand::usage()
{
	return ("makedir full-dir-path");
}

//========================================================================

VfsCopyInCommand::VfsCopyInCommand( VfsRepository* repo, string arg1, string arg2, ostream& ostr) :
	VfsCommand(repo, "copyin", arg1, arg2, ostr)
{
}

int VfsCopyInCommand::doCommand()
{
	repo->copyIn(param1, param2);
	ostr << "VfsCopyInCommand executed" << endl;
}

string VfsCopyInCommand::usage()
{
	return ("copyin external-full-path internal-full-path");
}

//========================================================================

VfsCopyOutCommand::VfsCopyOutCommand( VfsRepository* repo, string arg1, string arg2, ostream& ostr) :
	VfsCommand(repo, "copyout", arg1, arg2, ostr)
{
}

int VfsCopyOutCommand::doCommand()
{
	repo->copyOut(param1, param2);
	ostr << "VfsCopyOutCommand executed" << endl;
}

string VfsCopyOutCommand::usage()
{
	return ("copyout internal-full-path external-full-path");
}

//========================================================================

VfsMoveCommand::VfsMoveCommand( VfsRepository* repo, string arg1, string arg2, ostream& ostr) :
	VfsCommand(repo, "move", arg1, arg2, ostr)
{
}

int VfsMoveCommand::doCommand()
{
	ostr << "VfsMoveCommand executed" << endl;
}

string VfsMoveCommand::usage()
{
	return ("move source-full-path dest-full-path");
}

//========================================================================

VfsCatCommand::VfsCatCommand( VfsRepository* repo, string arg1, ostream& ostr ) :
	VfsCommand(repo, "cat", arg1, string(""), ostr )
{
}

int VfsCatCommand::doCommand()
{
	ostr << "VfsCatCommand executed" << endl;
}

string VfsCatCommand::usage()
{
	return ("cat text-file-path");
}

//========================================================================

VfsListCommand::VfsListCommand( VfsRepository* repo, string arg1, ostream& ostr ) :
	VfsCommand(repo, "list", arg1, string(""), ostr)
{
}

int VfsListCommand::doCommand()
{
	vector<string> contents;
	repo->list(param1, contents);

	for( auto s : contents )
		ostr << s << endl;
	ostr << "VfsListCommand executed" << endl;
}

string VfsListCommand::usage()
{
	return ("list full-path");
}

//========================================================================

VfsDeleteCommand::VfsDeleteCommand( VfsRepository* repo, string arg1, ostream& ostr ) :
	VfsCommand(repo, "delete", arg1, string(""), ostr)
{
}

int VfsDeleteCommand::doCommand()
{
	ostr << "VfsDeleteCommand executed" << endl;
}

string VfsDeleteCommand::usage()
{
	return ("delete full-file-or-folder-path");
}



