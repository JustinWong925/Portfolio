// $Id: main.cpp,v 1.6 2014-07-09 11:50:34-07 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_pair = xpair<const string,string>;
using str_str_map = listmap<string,string>;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

string trim(string line){
   string result;
   size_t pre = line.find_first_not_of(" ");
   size_t post = line.find_last_not_of(" ");
   if(pre != string::npos && post != string::npos){
      size_t result_size = post - pre + 1;
	  result = line.substr(pre, result_size);
   }
   return result;
}

void parse_line(string line, str_str_map &map){
   line = trim(line);
   size_t linesize = line.size();
   size_t eq;
   eq = line.find_first_of("=");
   if(eq != string::npos){
      string key = line.substr(0,eq);
	  string value = line.substr((eq + 1),(linesize - eq - 1));
	  str_str_pair pair(key,value);
	  if(!key.empty() && value.empty()){
	     map.remove(pair);
		 //deletes pair
	  } else if (!key.empty() && !value.empty()){
	     //if there us already a pair, replace it
	     map.insert(pair);
		 cout << pair << endl;
	  } else if (key.empty() && value.empty()){
	     //print
	     map.print();
	  } else if (key.empty() && !value.empty()){
	     map.print_values(pair);
	  }
   } else if (!line.empty()){
      map.find(line);
   }
}

void readfile(int argc, char** argv, str_str_map &map){
   string line;
   size_t beg = 0;
   int linenr = 0;
   string filename;
   if(argc > 1){
      for(int i = 1; i < argc; ++i){
	     filename = argv[i];
		 ifstream infile(argv[i]);
		    if(infile.is_open()){
			   while(getline(infile, line)){
			   cout << filename << ": " <<++linenr<< ": "<<line<<endl;
			   if(line.find_first_of("#") != beg)
			      parse_line(line, map);
			   }
			} else {
			   cout << "Failed to open file" << endl;
			}
	  }
   } else if (argc == 1){
      while(cin){
	     getline(cin, line);
		 cout << "-: " << ++linenr << ": " << line << endl;
		 parse_line(line, map);
	  }
   }
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);

   str_str_map map;
   readfile(argc, argv, map);
  /* for (int argi = 0; argi < argc; ++argi) {
      str_str_pair pair (argv[argi], to_string<int> (argi));
      cout << "Before insert: " << pair << endl;
      test.insert (pair);
   }

   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = test.begin();
   test.erase (itor);

   cout << "EXIT_SUCCESS" << endl; */
   return EXIT_SUCCESS;
}

