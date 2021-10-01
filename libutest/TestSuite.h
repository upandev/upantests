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

#pragma once

#include <ITestSuite.h>
#include <TestRunner.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

template <class T>
class TestSuite : public ITestSuite {
private:
  //static_assert(std::is_base_of<TestSuite<T>, T>::value, "Derived not derived from BaseClass");
  typedef void (T::*_TestCase)();
  static bool _single_instance;

public:
  typedef T SuiteType;

  TestSuite(const std::string& name) : _name(name) {
    if (_single_instance) {
      throw std::invalid_argument("Only instance of TestSuite '" + name + "' allowed");
    }
    _single_instance = true;
    TestRunner::Instance().add(*this);
  }

  virtual ~TestSuite() {
    _testCases.clear();
    _testCaseMap.clear();
  }

  std::string name() const override {
    return _name;
  }

  void add(const std::string& name, _TestCase testCase) {
    if (_testCaseMap.find(name) != _testCaseMap.end()) {
      throw std::invalid_argument("TestCase with name '" + name + "' already registered");
    }
    auto v = typename TestCaseMap::value_type(name, testCase);
    _testCaseMap.insert(v);
    _testCases.push_back(v);
  }

  void run() override {
    printf("\n running %s...", name().c_str());
    for(auto testCase : _testCases) {
      printf("\n  %s... ", testCase.first.c_str());
      try {
        (dynamic_cast<T *>(this)->*(testCase.second))();
        printf("Passed");
      } catch(const std::exception& e) {
        printf("FAILED");
        printf("\n  %s", e.what());
      }
    }
  }

private:
  typedef std::map<std::string, _TestCase> TestCaseMap;
  std::vector<typename TestCaseMap::value_type> _testCases;
  TestCaseMap _testCaseMap;
  const std::string _name;
};

template <class T>
bool TestSuite<T>::_single_instance = false;

#define REGISTER_TEST_SUITE(T) static TestSuite<T>::SuiteType* _##T = new TestSuite<T>::SuiteType();

#define ASSERT_CONDITION(COND) if(!(COND)) { \
char buf[4096];                              \
snprintf(buf, 4095, "error@%d", __LINE__);         \
throw std::runtime_error(buf);\
}

#define ASSERT(AV, COMP, EV) \
if(!((AV) COMP (EV))) {      \
char buf[4096];                              \
snprintf(buf, 4095, "Actual Value: %x, Expected Value: %x - error@%d", AV, EV, __LINE__) ; \
throw std::runtime_error(buf);\
}
