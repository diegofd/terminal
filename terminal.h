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


#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <Arduino.h>

class Terminal
{
  private:

    struct t_command {
        String cmd;
        void (*function)(short, char* []);
    };

    static const short COMMANDS_MAX = 10;
    short commands_num = 0;
    struct t_command commands[COMMANDS_MAX];

    String currentString;
    int incomingByte;

  public:
    void register_command(String cmd, void (*function)(short, char* []) );
    void exec(String str);
    void string(String str);
    void read();
    void write(String str);
    Terminal();
};

#endif // __TERMINAL_H__