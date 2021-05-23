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
#include <atomicop.cpp>
#include <mutex.cpp>

class Testatomic : public TestSuite<Testatomic> {
public:
  Testatomic() : TestSuite("ustdcpp_atomic") {
    add("testAtomicSwap", &Testatomic::testAtomicSwap);
  }

  void testAtomicSwap() {
    upan::mutex m ;

    ASSERT_CONDITION(m._lock == 0) ;
    ASSERT_CONDITION(upan::atomic::swap(m._lock, 1) == 0) ;
    ASSERT_CONDITION(m._lock == 1) ;
    ASSERT_CONDITION(upan::atomic::swap(m._lock, 0) == 1) ;
    ASSERT_CONDITION(m._lock == 0) ;
    ASSERT_CONDITION(upan::atomic::swap(m._lock, 1) == 0) ;
    ASSERT_CONDITION(m._lock == 1) ;
  }
};

REGISTER_TEST_SUITE(Testatomic);