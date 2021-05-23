/*
 *	Upanix - An x86 based Operating System
 *  Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/
 */

#include <stdcmocks.h>
#include <string.h>

void strreverse(char* str) {
  unsigned len = strlen(str) ;
  unsigned i ;
  char temp ;

  for(i = 0; i < len / 2; i++)
  {
    temp = str[i] ;
    str[i] = str[len - i - 1] ;
    str[len - i - 1] = temp ;
  }
}

void sleepms(unsigned ms) {
}

int getpid() {
  return 0;
}

int isprocessalive(int pid) {
  return 0;
}