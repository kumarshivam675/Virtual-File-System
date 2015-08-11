#include<cstdlib>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>
#include "VfsCommand.h"
#include "VfsRepository.h"

using namespace std;

void processInstructions(istream& is, bool is_interactive, ostream& ostr);
VfsCommand *getVfsCommand( string cmdline );

// Global object for generating output file for non-interactive session
ofstream outstr;

int main(int argc, char *argv[])
{
	if( argc == 2 ){
		if( string(argv[1]) == string("--interactive")){
			processInstructions(cin, true, cout);
		}
		else{
			string infile(argv[1]);

			ifstream cmdfile(infile);

			if (! cmdfile.is_open()){
				cout << "Error opening file " << argv[1] << endl; 
				exit (2); 
			}
			string outfile = string(argv[1]);
			if( outfile.rfind(".") != string::npos )
				outfile = outfile.erase(outfile.rfind("."),outfile.size());
			outfile += ".out";
			cout << "Running commands from " << infile << endl;
			cout << "Generating " << outfile << endl;
			
			outstr.open(outfile);
			processInstructions(cmdfile, false, outstr);
			outstr.close();
		}
	}
	else{
		cout << "Usage: " << argv[0] << " --interactive | cmdfile" << endl;
		exit(1);
	}
}

void processInstructions(istream& is, bool is_interactive, ostream& ostr)
{
	string cmdline;
	VfsRepository *repo;
	if(is_interactive){
		ostr << "vfs> "; 
		ostr.flush();
	}
	repo = new VfsRepository();
	while( getline(is, cmdline) ){
		// cout << "Line read: " << cmdline << endl;
		if( cmdline == string("") )
			continue;		

		VfsCommand *cmd = VfsCommand::getVfsCommand( cmdline, repo, ostr );
		if( cmd == (VfsCommand*) 0 )
			break;

		if( !is_interactive ){
			// Display the command being processed
			ostr << cmd->getCommand() << endl;
		}

		// Take all necessary action
		try{		
			cmd->doCommand();
		}
		catch(const char *err){
			ostr << err << endl;
		}
		catch(...){
			ostr << "Unknown error encountered" << endl;
			ostr << cmd->usage() << endl;
		}
		
		if(is_interactive){
			ostr << "vfs> "; ostr.flush();
		}
		else
			ostr << "==========================" << endl;
	}
	delete repo;
}


