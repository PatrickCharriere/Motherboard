#include "parser.h"

vector<string> Parser::parseFile(string filename, char delimiter) {
	ifstream in(filename);
	if (in.fail()) throw 20;

	vector<string> row;
	while(in.good()) {
		row = csv_read_row(in, delimiter);
	}
	in.close();

	return row;
}


vector<string> Parser::csv_read_row(istream &in, char delimiter)
{
    stringstream ss;
    bool inquotes = false;
    vector<string> row;//relying on RVO
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
            row.push_back( ss.str() );
            ss.str("");
        }
        else if (!inquotes && (c=='\r' || c=='\n') )
        {
            if(in.peek()=='\n') { in.get(); }
            row.push_back( ss.str() );
            return row;
        }
        else
        {
            ss << c;
        }
    }
}
