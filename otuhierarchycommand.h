#ifndef OTUHIERARCHYCOMMAND_H
#define OTUHIERARCHYCOMMAND_H
/*
 *  otuhierarchycommand.h
 *  Mothur
 *
 *  Created by westcott on 1/19/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */

#include "command.hpp"
#include "listvector.hpp"

//**********************************************************************************************************************

class OtuHierarchyCommand : public Command {

public:
	OtuHierarchyCommand(string);
	OtuHierarchyCommand();
	~OtuHierarchyCommand();
	vector<string> getRequiredParameters();
	vector<string> getValidParameters();
	vector<string> getRequiredFiles();
	map<string, vector<string> > getOutputFiles() { return outputTypes; }
	int execute();
	void help();
	
private:
	bool abort;
	set<string> labels; //holds labels to be used
	string label, listFile, outputDir, output;
	vector<string> outputNames;
	map<string, vector<string> > outputTypes;
	
	vector<ListVector> getListVectors();
		
};

//**********************************************************************************************************************

#endif


