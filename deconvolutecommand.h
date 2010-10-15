#ifndef DECONVOLUTECOMMAND_H
#define DECONVOLUTECOMMAND_H
/*
 *  deconvolute.h
 *  Mothur
 *
 *  Created by Sarah Westcott on 1/21/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "command.hpp"
#include "fastamap.h"

/* The unique.seqs command reads a fasta file, finds the duplicate sequences and outputs a names file
	containing 2 columns.  The first being the groupname and the second the list of identical sequence names. */ 


class DeconvoluteCommand : public Command {

public:
	DeconvoluteCommand(string);
	DeconvoluteCommand();
	~DeconvoluteCommand() {}
	vector<string> getRequiredParameters();
	vector<string> getValidParameters();
	vector<string> getRequiredFiles();
	map<string, vector<string> > getOutputFiles() { return outputTypes; }
	int execute();
	void help();	
	
private:
	string inFastaName, oldNameMapFName, outputDir;
	vector<string> outputNames;
	map<string, vector<string> > outputTypes;

	bool abort;
};

#endif
