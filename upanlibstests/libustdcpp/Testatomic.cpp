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
#include <atomicop.cpp>
#include <mutex.cpp>

class Testatomic : public TestSuite<Testatomic> {
public:
  Testatomic() : TestSuite("ustdcpp_atomic") {
    add("testAtomicOp", &Testatomic::testAtomicOp);
    add("testAtomicUint32", &Testatomic::testAtomicUint32);
  }

  void testAtomicOp() {
    __volatile__ uint32_t lock = 0;

    ASSERT_CONDITION(lock == 0) ;
    ASSERT_CONDITION(upan::atomic::op::swap(lock, 1) == 0) ;
    ASSERT_CONDITION(lock == 1) ;
    ASSERT_CONDITION(upan::atomic::op::swap(lock, 0) == 1) ;
    ASSERT_CONDITION(lock == 0) ;
    ASSERT_CONDITION(upan::atomic::op::add(lock, 10) == 0) ;
    ASSERT_CONDITION(lock == 10) ;
    ASSERT_CONDITION(upan::atomic::op::add(lock, 10) == 10) ;
    ASSERT_CONDITION(lock == 20) ;
  }

  void testAtomicUint32() {
    upan::atomic::integral<uint32_t> val(100);
    ASSERT_CONDITION(val.get() == 100);
    ASSERT_CONDITION(val.set(101) == 100);
    ASSERT_CONDITION(val.get() == 101);
    ASSERT_CONDITION(val.add(10) == 101);
    ASSERT_CONDITION(val.get() == 111);
    ASSERT_CONDITION(val.inc() == 111);
    ASSERT_CONDITION(val.get() == 112);
    ASSERT_CONDITION(val.dec() == 112);
    ASSERT_CONDITION(val.get() == 111);
  }
};

REGISTER_TEST_SUITE(Testatomic);