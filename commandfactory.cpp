/*
 *  commandfactory.cpp
 *  
 *
 *  Created by Pat Schloss on 10/25/08.
 *  Copyright 2008 Patrick D. Schloss. All rights reserved.
 *
 */

#include "command.hpp"
#include "readdistcommand.h"
#include "readotucommand.h"
#include "readlistcommand.h"
#include "clustercommand.h"
#include "parselistcommand.h"
#include "collectcommand.h"
#include "collectsharedcommand.h"
#include "rarefactcommand.h"
#include "summarycommand.h"
#include "summarysharedcommand.h"
#include "rarefactsharedcommand.h"
#include "nocommand.h"
#include "quitcommand.h"
#include "helpcommand.h"
#include "commandfactory.hpp"
#include <exception>


/***********************************************************/

/***********************************************************/
CommandFactory::CommandFactory(){
	command = new NoCommand();
}

/***********************************************************/

/***********************************************************/
CommandFactory::~CommandFactory(){
	delete command;
}

/***********************************************************/

/***********************************************************/
//This function calls the appropriate command fucntions based on user input.
Command* CommandFactory::getCommand(string commandName){
	try {
		delete command;   //delete the old command

			 if(commandName == "read.dist")				{	command = new ReadDistCommand();	}
		else if(commandName == "read.otu")				{	command = new ReadOtuCommand();	}
		else if(commandName == "read.list")				{	command = new ReadListFileCommand();	}
		else if(commandName == "cluster")				{	command = new ClusterCommand();			}
		else if(commandName == "help")					{	command = new HelpCommand();			}
		else if(commandName == "quit")					{	command = new QuitCommand();			}
		else if(commandName == "collect.single")		{	command = new CollectCommand();			}
		else if(commandName == "collect.shared")		{	command = new CollectSharedCommand();	}
		else if(commandName == "rarefaction.single")	{	command = new RareFactCommand();		}
		else if(commandName == "rarefaction.shared")	{	command = new RareFactSharedCommand();	}
		else if(commandName == "summary.single")		{	command = new SummaryCommand();			}
		else if(commandName == "summary.shared")		{	command = new SummarySharedCommand();	}
		else											{	command = new NoCommand();				}

		return command;
	}
	catch(exception& e) {
		cout << "Standard Error: " << e.what() << " has occurred in the CommandFactory class Function getCommand. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
	catch(...) {
		cout << "An unknown error has occurred in the CommandFactory class function getCommand. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}

}
/***********************************************************/

/***********************************************************/