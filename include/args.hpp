
#ifndef __ARGS_HPP__
#define __ARGS_HPP__
 
#include <list>
#include <string>
 
#define STATE_KEY 0
#define STATE_VALUE 1
#define STATE_NONE 2
 
#define ISNUM(c) (c >= 0x30 && c <= 0x39)
  
using namespace std;

typedef list<pair<string,string> > ArgsList;

class ArgumentsParser : public ArgsList {
public:
	int parse (int argc, char** argv);
	const string& get_value (const string& k);
	bool contains_key (const string& k);
	const string NOT_FOUND;
	
	ArgumentsParser ()
		: NOT_FOUND ("not found") {}
};

 
#endif
