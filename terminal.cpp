/* 
    Terminal
    Copyright (C) 2014 Diego Fernandez Duran

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <terminal.h>

void Terminal::register_command(String cmd, void (*function)(short, char* [])) {
  struct t_command command;
  command.cmd = cmd;
  command.function = function;

  commands[commands_num] = command;
  commands_num++;
}
/*
String* split(String str) {
  short idx;
  short str_len = str.length();

  char* strings[] = NULL;

  while (-1 != (idx = str.indexOf(' ')) && (idx < str_len - 1)) { 
    substr = str.substring(0, idx);
    str = str.substring(idx + 1);
  }
}
*/
void Terminal::exec(String str) {
  str.toLowerCase();
  str.trim();

  String cmd;
  short argc = 0;
  char **argv = 0;
  String args;
  short idx;

  if ( -1 != (idx = str.indexOf(' '))) {
    // Space found
    cmd = str.substring(0, idx);
    
    // Split arguments
    if (idx < str.length() - 1) { 
      str = str.substring(idx + 1);

      short length = str.length();
      char* args = (char*) malloc(sizeof(char) * length);
            
      str.toCharArray(args, length + 1);

      // Allocate mem for the first argument
      argv = (char **) malloc(1 * sizeof(char *));
      
      char *pch;
      pch = strtok (args, " ");
      while (pch != NULL) {
        argv[argc] = pch;
        argc++;
        pch = strtok (NULL, " ");
        if (pch != NULL) {
          // Allocate for the next
          argv = (char **) realloc(argv, (argc + 1) * sizeof(char *));
        }
      }
    }

  } else {
    cmd = str;
  }

  for (int i = 0; i < commands_num; i++) {
    if (commands[i].cmd == cmd) {
      (*commands[i].function)(argc, argv);
      
      return;
    }
  }

  write("ERROR: Command " + cmd + " not found.");
}

void Terminal::read() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte != '\r') {
      currentString = currentString + (char) incomingByte;
    } else {
      exec(currentString);
      currentString = String();
    }
  }
}

void Terminal::write(String str) {
  Serial.println(str);
}

Terminal::Terminal() {
  Serial.begin(115200);
}
