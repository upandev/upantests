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

#include <TestRunner.h>
#include <TestSuite.h>

TestRunner::~TestRunner() {
  for(auto s : _testSuites) {
    delete s;
  }
  _testSuites.clear();
  _testSuiteMap.clear();
}

void TestRunner::add(ITestSuite& testSuite) {
  if (_testSuiteMap.find(testSuite.name()) != _testSuiteMap.end()) {
    throw std::invalid_argument("TestSuite with name '" + testSuite.name() + "' already registered");
  }
  _testSuiteMap.insert(TestSuiteMap::value_type(testSuite.name(), &testSuite));
  _testSuites.push_back(&testSuite);
}

void TestRunner::run() {
  for(auto s : _testSuites) {
    s->run();
  }
}