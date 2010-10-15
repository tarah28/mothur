/*
 *  readotu.cpp
 *  Mothur
 *
 *  Created by Sarah Westcott on 1/20/09.
 *  Copyright 2009 Schloss Lab UMASS AMherst. All rights reserved.
 *
 */

#include "readotucommand.h"

//**********************************************************************************************************************
vector<string> ReadOtuCommand::getValidParameters(){	
	try {
		string Array[] =  {"list","order","shared","relabund","label","group","sabund", "rabund","groups","ordergroup","outputdir","inputdir"};
		vector<string> myArray (Array, Array+(sizeof(Array)/sizeof(string)));
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "ReadOtuCommand", "getValidParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
ReadOtuCommand::ReadOtuCommand(){	
	try {
		//initialize outputTypes
		vector<string> tempOutNames;
		outputTypes["rabund"] = tempOutNames;
		outputTypes["shared"] = tempOutNames;
	}
	catch(exception& e) {
		m->errorOut(e, "ReadOtuCommand", "ReadOtuCommand");
		exit(1);
	}
}
//**********************************************************************************************************************
vector<string> ReadOtuCommand::getRequiredParameters(){	
	try {
		string Array[] =  {"list","shared","relabund","sabund","rabund","or"};
		vector<string> myArray (Array, Array+(sizeof(Array)/sizeof(string)));
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "ChopSeqsCommand", "getRequiredParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
vector<string> ReadOtuCommand::getRequiredFiles(){	
	try {
		vector<string> myArray;
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "ReadOtuCommand", "getRequiredFiles");
		exit(1);
	}
}
//**********************************************************************************************************************
ReadOtuCommand::ReadOtuCommand(string option)  {
	try {
		globaldata = GlobalData::getInstance();
		abort = false;
		allLines = 1;
		
		//allow user to run help
		if(option == "help") { help(); abort = true; }
		
		else {
			//valid paramters for this command
			string Array[] =  {"list","order","shared","relabund","label","group","sabund", "rabund","groups","ordergroup","outputdir","inputdir"};
			vector<string> myArray (Array, Array+(sizeof(Array)/sizeof(string)));
			
			OptionParser parser(option);
			map<string, string> parameters = parser.getParameters();
			
			ValidParameters validParameter;
			map<string, string>::iterator it;
		
			//check to make sure all parameters are valid for command
			for (it = parameters.begin(); it != parameters.end(); it++) { 
				if (validParameter.isValidParameter(it->first, myArray, it->second) != true) {  abort = true;  }
			}
			
			//initialize outputTypes
			vector<string> tempOutNames;
			outputTypes["rabund"] = tempOutNames;
			outputTypes["shared"] = tempOutNames;
			
			globaldata->newRead();
			
			//if the user changes the input directory command factory will send this info to us in the output parameter 
			string inputDir = validParameter.validFile(parameters, "inputdir", false);		
			if (inputDir == "not found"){	inputDir = "";		}
			else {
				string path;
				it = parameters.find("list");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["list"] = inputDir + it->second;		}
				}
				
				it = parameters.find("order");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["order"] = inputDir + it->second;		}
				}
				
				it = parameters.find("shared");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["shared"] = inputDir + it->second;		}
				}
				
				it = parameters.find("group");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["group"] = inputDir + it->second;		}
				}
				
				it = parameters.find("sabund");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["sabund"] = inputDir + it->second;		}
				}
				
				it = parameters.find("rabund");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["rabund"] = inputDir + it->second;		}
				}
				
				it = parameters.find("ordergroup");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["ordergroup"] = inputDir + it->second;		}
				}
				
				it = parameters.find("relabund");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["relabund"] = inputDir + it->second;		}
				}
			}

			
			//if the user changes the output directory command factory will send this info to us in the output parameter 
			outputDir = validParameter.validFile(parameters, "outputdir", false);		if (outputDir == "not found"){	outputDir = "";	}

			//check for required parameters
			listfile = validParameter.validFile(parameters, "list", true);
			if (listfile == "not open") { abort = true; }
			else if (listfile == "not found") { listfile = ""; }	
			else {  globaldata->setListFile(listfile);  globaldata->setFormat("list"); 	}
			
			sabundfile = validParameter.validFile(parameters, "sabund", true);
			if (sabundfile == "not open") { abort = true; }	
			else if (sabundfile == "not found") { sabundfile = ""; }
			else {  globaldata->setSabundFile(sabundfile); globaldata->setFormat("sabund");	}

			rabundfile = validParameter.validFile(parameters, "rabund", true);
			if (rabundfile == "not open") { abort = true; }	
			else if (rabundfile == "not found") { rabundfile = ""; }
			else {  globaldata->setRabundFile(rabundfile);	globaldata->setFormat("rabund");}
			
			ordergroupfile = validParameter.validFile(parameters, "ordergroup", true);
			if (ordergroupfile == "not open") { abort = true; }	
			else if (ordergroupfile == "not found") { ordergroupfile = ""; }
			else {  globaldata->setOrderGroupFile(ordergroupfile);  }
			
			sharedfile = validParameter.validFile(parameters, "shared", true);
			if (sharedfile == "not open") { abort = true; }	
			else if (sharedfile == "not found") { sharedfile = ""; }
			else {  globaldata->setSharedFile(sharedfile); globaldata->setFormat("sharedfile");	}
			
			relAbundfile = validParameter.validFile(parameters, "relabund", true);
			if (relAbundfile == "not open") { abort = true; }	
			else if (relAbundfile == "not found") { relAbundfile = ""; }
			else {  globaldata->setRelAbundFile(relAbundfile); globaldata->setFormat("relabund");	}

			
			groupfile = validParameter.validFile(parameters, "group", true);
			if (groupfile == "not open") { abort = true; }	
			else if (groupfile == "not found") { groupfile = ""; }
			else {  
				globaldata->setGroupFile(groupfile); 
				groupMap = new GroupMap(groupfile);
				
				int error = groupMap->readMap();
				if (error == 1) { abort = true; }
				
				globaldata->gGroupmap = groupMap;
			}
			
			groups = validParameter.validFile(parameters, "groups", false);			
			if (groups == "not found") { groups = ""; }
			else { 
				m->splitAtDash(groups, Groups);
				globaldata->Groups = Groups;
			}

			//you are doing a list and group shared
			if ((listfile != "") && (groupfile != "")) { globaldata->setFormat("shared"); }
			
			//you have not given a file
			if ((listfile == "") && (sharedfile == "") && (rabundfile == "") && (sabundfile == "") && (relAbundfile == "")) {
				m->mothurOut("You must enter either a listfile, rabundfile, sabundfile, relabund or a sharedfile with the read.otu command. "); m->mothurOutEndLine(); abort = true; 
			}
		
			//check for optional parameter and set defaults
			// ...at some point should added some additional type checking...
			label = validParameter.validFile(parameters, "label", false);			
			if (label == "not found") { label = ""; }
			else { 
				if(label != "all") {  m->splitAtDash(label, labels);  allLines = 0;  }
				else { allLines = 1;  }
				globaldata->labels = labels;
			}
			
			globaldata->allLines = allLines;
		
			orderfile = validParameter.validFile(parameters, "order", true);
			if (orderfile == "not open") { abort = true; }	
			else if (orderfile == "not found") { orderfile = ""; }
			else {  globaldata->setOrderFile(orderfile);	}
			
				
			if (abort == false) {
				//gets whichever one of the above is set
				filename = globaldata->inputFileName;
			}
		}

	}
	catch(exception& e) {
		m->errorOut(e, "ReadOtuCommand", "ReadOtuCommand");
		exit(1);
	}
}
//**********************************************************************************************************************

void ReadOtuCommand::help(){
	try {
		m->mothurOut("The read.otu command must be run before you execute a collect.single, rarefaction.single, summary.single, \n");
		m->mothurOut("collect.shared, rarefaction.shared, summary.shared heatmap.bin, heatmap.sim or venn command.   Mothur will generate a .list, .rabund and .sabund upon completion of the cluster command \n");
		m->mothurOut("or you may use your own. The read.otu command parameter options are list, rabund, sabund, shared, relabund, group, order, ordergroup, label and groups.\n");
		m->mothurOut("The read.otu command can be used in two ways.  The first is to read a list, rabund or sabund and run the collect.single, rarefaction.single or summary.single.\n");
		m->mothurOut("For this use the read.otu command should be in the following format: read.otu(list=yourListFile, order=yourOrderFile, label=yourLabels).\n");
		m->mothurOut("The list, rabund or sabund parameter is required, but you may only use one of them.\n");
		m->mothurOut("The label parameter is used to read specific labels in your input.\n");
		m->mothurOut("The second way to use the read.otu command is to read a list and a group, or a shared so you can use the collect.shared, rarefaction.shared or summary.shared commands.\n");
		m->mothurOut("In this case the read.otu command should be in the following format: read.otu(list=yourListFile, group=yourGroupFile) or read.otu(shared=yourSharedFile).  \n");
		m->mothurOut("The list parameter and group paramaters or the shared paremeter is required. When using the command the second way with a list and group file read.otu command parses the .list file\n");
		m->mothurOut("and separates it into groups.  It outputs a .shared file containing the OTU information for each group. The read.otu command also outputs a .rabund file for each group. \n");
		m->mothurOut("You can use the groups parameter to choose only specific groups to be used in the .shared and .rabund files. \n");
		m->mothurOut("You can use the ordergroup parameter to provide a file containing a list of group names in the order you would like them to appear in your shared file. \n");
		m->mothurOut("Note: No spaces between parameter labels (i.e. list), '=' and parameters (i.e.yourListfile).\n\n");

	}
	catch(exception& e) {
		m->errorOut(e, "ReadOtuCommand", "help");
		exit(1);
	}
}



//**********************************************************************************************************************
ReadOtuCommand::~ReadOtuCommand(){}
//**********************************************************************************************************************

int ReadOtuCommand::execute(){
	try {
	
		if (abort == true) {	return 0;	}
	
		if (globaldata->getFormat() == "shared") {
			
			shared = new SharedCommand(outputDir);
			int okay = shared->execute();
			
			//problem with shared
			if (okay == 1) {
				globaldata->setListFile("");
				globaldata->setGroupFile("");
				globaldata->setSharedFile("");
			}else { //shared command outputs the filenames
				//m->mothurOutEndLine();
				//m->mothurOut("Output File Name: "); m->mothurOutEndLine();
				//m->mothurOut(globaldata->getSharedFile()); m->mothurOutEndLine();	
				//m->mothurOutEndLine();
			}
			
			outputTypes = shared->getOutputFiles();
			
			delete shared;
		}
		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "ReadOtuCommand", "execute");
		exit(1);
	}
}
//**********************************************************************************************************************
