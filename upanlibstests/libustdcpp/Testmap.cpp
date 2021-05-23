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

#include <TestSuite.h>
#include <stdcmocks.h>
#include <map.h>

class Testmap : public TestSuite<Testmap> {
public:
  Testmap() : TestSuite("ustdcpp_map") {
    add("testMapFwdRwd", &Testmap::testMapFwdRwd);
    add("testMap", &Testmap::testMap);
    add("testMapReverseEntry", &Testmap::testMapReverseEntry);
  }

  void testMapFwdRwd() {
    upan::map<int, int> m;
    m.insert(upan::map<int, int>::value_type(1, 1));
    m.insert(upan::map<int, int>::value_type(2, 1));
    m.insert(upan::map<int, int>::value_type(3, 1));

    m.insert(upan::map<int, int>::value_type(6, 1));
    m.insert(upan::map<int, int>::value_type(5, 1));
    m.insert(upan::map<int, int>::value_type(4, 1));

    int i = 1;
    for (auto it = m.begin(); it != m.end(); ++it) {
      auto n = it._node;
      ASSERT_CONDITION(n->element().first == i);
      if (i == 2) {
        ASSERT_CONDITION(n->balance_factor() == 1);
      } else {
        ASSERT_CONDITION(n->balance_factor() == 0);
      }
      ++i;
    }

    ASSERT_CONDITION(m.verify_balance_factor() == true);
  }

  void testMap() {
    upan::map<int, int> m;

    for (int i = 0; i < 1000; ++i)
      m.insert(upan::map<int, int>::value_type(i, i));

    ASSERT_CONDITION(m.height() == 10);

    for (int i = 0; i < 1000; ++i)
      ASSERT_CONDITION(m[i] == i);
    for (int i = 0; i < 2000; ++i)
      m[i] = i;
    for (int i = 0; i < 2000; ++i) {
      auto it = m.find(i);
      ASSERT_CONDITION(it != m.end());
      ASSERT_CONDITION((*it).first == i);
      ASSERT_CONDITION(it->second == i);
    }
    int i = 0;
    for (const auto &it : m) {
      ASSERT_CONDITION(it.first == i);
      ASSERT_CONDITION(it.second == i);
      ++i;
    }
    ASSERT_CONDITION(i == 2000);
    ASSERT_CONDITION(m.height() == 11);

    for (int i = 500; i < 1800; ++i)
      ASSERT_CONDITION(m.erase(i) == true);

    for (int i = 500; i < 1800; ++i)
      ASSERT_CONDITION(m.find(i) == m.end());

    ASSERT_CONDITION(m.height() == 10);
    ASSERT_CONDITION(m.size() == 700);

    for (int i = 2000; i < 3000; ++i) {
      ASSERT_CONDITION(m.find(i) == m.end());
      m[i] = i;
      ASSERT_CONDITION(m.find(i) != m.end());
    }

    ASSERT_CONDITION(m.height() == 11);

    i = 0;
    for (const auto &it : m) {
      ASSERT_CONDITION(it.first == i);
      ASSERT_CONDITION(it.second == i);
      ++i;
      if (i == 500)
        i += 1300;
    }

    ASSERT_CONDITION(i == 3000);
    ASSERT_CONDITION(m.size() == 1700);

    ASSERT_CONDITION(m.verify_balance_factor() == true);
  }

  void testMapReverseEntry() {
    upan::map<int, int> m;

    for (int i = 1000; i > 0; --i)
      m.insert(upan::map<int, int>::value_type(i, i));

    ASSERT_CONDITION(m.height() == 10);

    for (int i = 1; i <= 1000; ++i)
      ASSERT_CONDITION(m[i] == i);
    for (int i = 2000; i > 0; --i)
      m[i] = i;
    for (int i = 1; i <= 2000; ++i) {
      auto it = m.find(i);
      ASSERT_CONDITION(it != m.end());
      ASSERT_CONDITION((*it).first == i);
      ASSERT_CONDITION(it->second == i);
    }
    int i = 1;
    for (const auto &it : m) {
      ASSERT_CONDITION(it.first == i);
      ASSERT_CONDITION(it.second == i);
      ++i;
    }
    ASSERT_CONDITION(i == 2001);
    ASSERT(m.height(), ==, 11);

    for (int i = 500; i < 1800; ++i)
      ASSERT_CONDITION(m.erase(i) == true);

    for (int i = 500; i < 1800; ++i)
      ASSERT_CONDITION(m.find(i) == m.end());

    ASSERT_CONDITION(m.height() == 10);
    ASSERT_CONDITION(m.size() == 700);

    for (int i = 3000; i > 2000; --i) {
      ASSERT_CONDITION(m.find(i) == m.end());
      m[i] = i;
      ASSERT_CONDITION(m.find(i) != m.end());
    }

    ASSERT_CONDITION(m.height() == 11);

    i = 1;
    for (const auto &it : m) {
      ASSERT_CONDITION(it.first == i);
      ASSERT_CONDITION(it.second == i);
      ++i;
      if (i == 500)
        i += 1300;
    }

    ASSERT_CONDITION(i == 3001);
    ASSERT_CONDITION(m.size() == 1700);

    ASSERT_CONDITION(m.verify_balance_factor() == true);
  }
};

REGISTER_TEST_SUITE(Testmap)