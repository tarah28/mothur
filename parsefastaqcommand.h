#ifndef PARSEFASTAQCOMMAND_H
#define PARSEFASTAQCOMMAND_H

/*
 *  parsefastaqcommand.h
 *  Mothur
 *
 *  Created by westcott on 9/30/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */


#include "command.hpp"

class ParseFastaQCommand : public Command {

public:
	ParseFastaQCommand(string);
	ParseFastaQCommand();
	~ParseFastaQCommand();
	vector<string> getRequiredParameters();
	vector<string> getValidParameters();
	vector<string> getRequiredFiles();
	map<string, vector<string> > getOutputFiles() { return outputTypes; }
	int execute();
	void help();	
	
private:

	vector<string> outputNames;	
	map<string, vector<string> > outputTypes;
	string outputDir, fastaQFile;
	bool abort;
	
	vector<int> convertQual(string);
};

#endif


