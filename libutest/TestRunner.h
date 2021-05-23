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

#pragma once

#include <vector>
#include <map>
#include <string>

class ITestSuite;

class TestRunner {
private:
  TestRunner() {}

public:
  ~TestRunner();

  static TestRunner& Instance() {
    static TestRunner instance;
    return instance;
  }

  void add(ITestSuite& testSuite);
  void run();

private:
  typedef std::map<std::string, ITestSuite*> TestSuiteMap;
  std::vector<ITestSuite*> _testSuites;
  TestSuiteMap _testSuiteMap;
};