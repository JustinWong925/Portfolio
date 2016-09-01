//Justin Wong jujwong
//cmps109 asg5
// $Id: cix-client.cpp,v 1.7 2014-07-25 12:12:51-07 - - $

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "cix_protocol.h"
#include "logstream.h"
#include "signal_action.h"
#include "sockets.h"

logstream log (cout);

unordered_map<string,cix_command> command_map {
   {"exit", CIX_EXIT},
   {"help", CIX_HELP},
   {"ls"  , CIX_LS  },
   {"get" , CIX_GET },
   {"put" , CIX_PUT },
   {"rm"  , CIX_RM },
};

void cix_help() {
   static vector<string> help = {
      "exit         - Exit the program.  Equivalent to EOF.",
      "get filename - Copy remote file to local host.",
      "help         - Print help summary.",
      "ls           - List names of files on remote server.",
      "put filename - Copy local file to remote host.",
      "rm filename  - Remove file from remote server.",
   };
   for (const auto& line: help) cout << line << endl;
}

//remove function on server
//C->S
void cix_rm(client_socket& server, string filename) {
   cix_header header;
   header.cix_command = CIX_RM;
   for(size_t i = 0; i < filename.size(); ++i) {
      header.cix_filename[i] = filename[i];
   }
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.cix_command != CIX_ACK) {
      log << "sent CIX_RM, server did not return CIX_ACK" << endl;
      log << "server returned " << header << endl;
   } else log << "file removed: " << filename << endl;
}

// Copy the file with the name filename on the remote server 
//and creates or overwrite a file of the 
//same name in the current directory. C->S
void cix_get(client_socket& server, string filename) {
   cix_header header;
   header.cix_command = CIX_GET;
   for(size_t i = 0; i < filename.size(); ++i) {
      header.cix_filename[i] = filename[i];
   }
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.cix_command != CIX_ACK) {
      log << "sent CIX_GET, server did not return CIX_ACK" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.cix_nbytes+1];
      recv_packet (server, buffer, header.cix_nbytes);
      log << "received " << header.cix_nbytes << " bytes" << endl;
      buffer[header.cix_nbytes] = '\0';
      cout << buffer;
      ofstream file("newfile");
      file.write(buffer, header.cix_nbytes);
   }

}
// requests ls output from server C->S
void cix_ls (client_socket& server) {
   cix_header header;
   header.cix_command = CIX_LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.cix_command != CIX_LSOUT) {
      log << "sent CIX_LS, server did not return CIX_LSOUT" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.cix_nbytes + 1];
      recv_packet (server, buffer, header.cix_nbytes);
      log << "received " << header.cix_nbytes << " bytes" << endl;
      buffer[header.cix_nbytes] = '\0';
      cout << buffer;
   }
}

// Copies a local file into the socket and 
//causes the remote server to
// create that file in its directory. C -> S
void cix_put(client_socket& server, string filename) {
   cix_header header;
   header.cix_command = CIX_PUT;
   for(size_t i = 0; i < filename.size(); ++i) {
      header.cix_filename[i] = filename[i];
   }
   
   ifstream file(header.cix_filename);
   if(file != NULL) {
      file.seekg(0, file.end);
      header.cix_nbytes = file.tellg();
      cout << "nbytes: " << header.cix_nbytes << endl;
      file.seekg(0, file.beg); 
      void* bufptr = &header + 64;  
      char* buffer = new(bufptr) char(header.cix_nbytes);
      cout << "buffer size: " << sizeof(buffer) << endl;
      cout << "header addr: " << &header << endl;    
      cout << "buffer addr: " << &buffer << endl; 
      file.read(buffer, header.cix_nbytes);
      cout << buffer << endl; 
      log << "sending header " << header << endl;
      send_packet (server, &header, sizeof header);
      recv_packet (server, &header, sizeof header);
      log << "received header " << header << endl;
      log << "sending payload " << buffer << endl;
      send_packet(server, buffer, header.cix_nbytes);
   } else log << "no such file: " << filename << endl;
}

void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

bool SIGINT_throw_cix_exit {false};
void signal_handler (int signal) {
   log << "signal_handler: caught " << strsignal (signal) << endl;
   switch (signal) {
      case SIGINT: case SIGTERM: SIGINT_throw_cix_exit = true; break;
      //case SIGINT: case SIGTERM: throw cix_exit();
      default: break;
   }
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);     
   signal_action (SIGINT, signal_handler);
   signal_action (SIGTERM, signal_handler);
   if (args.size() > 2) usage();                    
   string host = get_cix_server_host (args, 0);     
   in_port_t port = get_cix_server_port (args, 1); 
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         string temp;
         vector<string> com_args; 
         getline (cin, line);
         if (cin.eof()) throw cix_exit();
         if (SIGINT_throw_cix_exit) throw cix_exit();
         temp = line; 
         while (temp.find(" ") != string::npos) {
            com_args.push_back(temp.substr(0, temp.find(' '))); 
            temp = temp.substr(temp.find(' ') + 1);
         }  com_args.push_back(temp);
  
         log << "command " << com_args[0] << endl;
         const auto& itor = command_map.find (com_args[0]);
         cix_command cmd = itor == command_map.end()
                         ? CIX_ERROR : itor->second;
         switch (cmd) {
            case CIX_EXIT:
               throw cix_exit();
               break;
            case CIX_HELP:
               cix_help();
               break;
            case CIX_LS:
               if(com_args.size() > 1) { 
                  log << line << ": invalid command" << endl;
               }else cix_ls (server);
               break;
            case CIX_PUT: // (C -> S)
               if(com_args.size() != 2) {
                  log << line << ": invalid usage" << endl;
                  break;
               }
               if(com_args[1].find("/") != string::npos || 
                  com_args[1].size() > 58) {
      
                  log << com_args[1] << ": invalid filename" << endl;
                  break;
               }
               cix_put (server, com_args[1]);
               break;
            case CIX_GET:
              if(com_args.size() != 2) {
                  log << line << ": invalid usage" << endl;
                  break;
               }
               if(com_args[1].find("/") != string::npos || 
                  com_args[1].size() > 58) {
      
                  log << com_args[1] << ": invalid filename" << endl;
                  break;
               }
               cix_get (server, com_args[1]);
               break;   
             case CIX_RM:
              if(com_args.size() != 2) {
                  log << line << ": invalid usage" << endl;
                  break;
               }
               if(com_args[1].find("/") != string::npos || 
                  com_args[1].size() > 58) {
      
                  log << com_args[1] << ": invalid filename" << endl;
                  break;
               }
               cix_rm (server, com_args[1]);
               break;
            default:
               log << com_args[0] << ": invalid command" << endl;
               break;
         } com_args.clear();
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   return 0;
}

