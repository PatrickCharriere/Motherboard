#include "parser.h"

void Parser::parseFile(string filename, char delimiter, vector<string>* row) {
	ifstream in(filename);
	if (in.fail()) throw 20;

	while(in.good()) {
		csv_read_row(in, delimiter, row);
	}
	in.close();
}


void Parser::csv_read_row(istream &in, char delimiter, vector<string>* row) {
    stringstream ss;
    bool inquotes = false;
    while(in.good())
    {
        char c = in.get();
        if (!inquotes && c=='"') //beginquotechar
        {
            inquotes=true;
        }
        else if (inquotes && c=='"') //quotechar
        {
            if ( in.peek() == '"')//2 consecutive quotes resolve to 1
            {
                ss << (char)in.get();
            }
            else //endquotechar
            {
                inquotes=false;
            }
        }
        else if (!inquotes && c==delimiter) //end of field
        {
            row->push_back( ss.str() );
            ss.str("");
        }
        else if (!inquotes && (c=='\r' || c=='\n') )
        {
            if(in.peek()=='\n') { in.get(); }
            row->push_back( ss.str() );
            return;
        }
        else
        {
            ss << c;
        }
    }
}
