#include <args.hpp>



int ArgumentsParser::parse (int argc, char** argv) {
	string buf, buf2;
	int state = STATE_NONE;
	for (int i = 1; i < argc; ++i) {
			if(*argv[i] == '-' && !ISNUM(*(argv[i]+1))) {
				if (state == STATE_KEY) {
					this->push_back(pair<string,string>(buf,""));
				} else if (state == STATE_VALUE) {
					this->push_back(pair<string,string>(buf,buf2));
					state = STATE_KEY;
				}
				buf = argv[i]+1;
				state = STATE_KEY;
			} else {
				if (state == STATE_KEY) {
					buf2 = argv[i];
				} else if (state == STATE_VALUE) {
					buf2 += " ";
					buf2 += argv[i];
				} else {
					buf = "*";
					buf2 = argv[i];
				}
				state = STATE_VALUE;
			}
			if (i == argc - 1 && state != STATE_NONE) {
				if (state == STATE_KEY) {
					this->push_back(pair<string,string>(buf,""));
				} else if (state == STATE_VALUE) {
					this->push_back(pair<string,string>(buf,buf2));
					//state = STATE_KEY;
				}
			}
	}
	return 0;
}

const string& ArgumentsParser::get_value (const string& k) {
	for (ArgsList::const_iterator it = this -> begin(); it != this -> end(); ++it) {
		if ((*it).first == k) {
			return it -> second;
		}
	}
	return NOT_FOUND;
}

bool ArgumentsParser::contains_key (const string& k) {
	for (ArgsList::iterator it = this -> begin(); it != this -> end(); ++it) {
		if ((*it).first == k)
			return true;
	}
	return false;
}



