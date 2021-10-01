/*
 *	Upanix - An x86 based Operating System
 *  Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa.prajwal@gmail.com'
 *
 *  I am making my contributions/submissions to this project solely in
 *  my personal capacity and am not conveying any rights to any
 *  intellectual property of any third parties.
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

#include <TestSuite.h>
#include <stdcmocks.h>
#include <list.h>

class Testlist : TestSuite<Testlist> {
public:
  Testlist() : TestSuite("ustdcpp_list") {
    add("testListBasic", &Testlist::testListBasic);
    add("testListPtr", &Testlist::testListPtr);
  }

  void testListBasic() {
    upan::list<int> l ;

    l.push_back(100) ;
    l.push_back(200) ;
    l.push_back(300) ;

    l.insert(++l.begin(), 400) ;

    int arr[ ] = { 100, 400, 200, 300 } ;
    int i = 0 ;

    for(auto it : l)
      ASSERT_CONDITION(arr[ i++ ] == it) ;

    ASSERT_CONDITION(l.size() == 4) ;
    ASSERT_CONDITION(l.front() == 100) ;
    l.pop_front() ;
    ASSERT_CONDITION(l.size() == 3) ;
    ASSERT_CONDITION(l.front() == 400);
    ASSERT_CONDITION(l.back() == 300);
  }

  void testListPtr() {
    upan::list<int*> l ;

    l.push_back(new int(100)) ;
    l.push_back(new int(200)) ;
    l.push_back(new int(300)) ;

    l.insert(++l.begin(), new int(400)) ;

    int arr[ ] = { 100, 400, 200, 300 } ;
    int i = 0 ;

    for(auto it : l)
      ASSERT_CONDITION(arr[ i++ ] == *it);

    ASSERT_CONDITION(l.size() == 4) ;
    int* v = l.front();
    ASSERT_CONDITION(*v == 100) ;
    l.pop_front();
    delete v ;
    ASSERT_CONDITION(l.size() == 3);
    ASSERT_CONDITION(*l.front() == 400);
    ASSERT_CONDITION(*l.back() == 300);

    i = 1;
    for(auto it = l.begin(); it != l.end();)
    {
      ASSERT_CONDITION(arr[ i++ ] == **it);
      delete *it;
      l.erase(it++);
    }

    ASSERT_CONDITION(l.size() == 0);
  }
};

REGISTER_TEST_SUITE(Testlist)