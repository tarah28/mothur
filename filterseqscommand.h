#ifndef FILTERSEQSCOMMAND_H
#define FILTERSEQSCOMMAND_H

/*
 *  filterseqscommand.h
 *  Mothur
 *
 *  Created by Thomas Ryabin on 5/4/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "command.hpp"
#include "filters.h"
#include "mpi.h"

class Sequence;
class FilterSeqsCommand : public Command {

public:
	FilterSeqsCommand(string);
	~FilterSeqsCommand() {};
	int execute();	
	void help();
	
private:
	struct linePair {
		int start;
		int numSeqs;
		linePair(long int i, int j) : start(i), numSeqs(j) {}
	};
	vector<linePair*> lines;
	vector<int> processIDS;

	string vertical, filter, fasta, hard, outputDir, filterFileName;
	vector<string> fastafileNames;	
	int alignmentLength, processors;
	vector<int> bufferSizes;
	vector<string> outputNames;

	char trump;
	bool abort;
	float soft;
	int numSeqs;
	
	string createFilter();
	int filterSequences();
	int createProcessesCreateFilter(Filters&, string);
	int createProcessesRunFilter(string, string);
	int driverCreateFilter(Filters&, string, linePair*);
	int driverRunFilter(string, string, string, linePair*);	
	int driverMPIRun(istringstream&, MPI_File&);
	int MPICreateFilter(Filters&, string);	
	int setLines(string);
	int parseBuffer(string, vector<string>&);
	
};

#endif
