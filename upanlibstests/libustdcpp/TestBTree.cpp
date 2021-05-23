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
#include <BTree.h>
//Include the source code that is being tested here
#include <BTree.cpp>

class TestBTree : TestSuite<TestBTree> {
public:
  TestBTree() : TestSuite("ustdcpp_BTree") {
    add("testBTree1", &TestBTree::testBTree1);
    add("testBTree2", &TestBTree::testBTree2);
    add("testBTree3", &TestBTree::testBTree3);
  }

  class TestKey : public BTreeKey {
  public:
    int m_key;

  public:
    TestKey(int key) : m_key(key) {}

    virtual bool operator<(const BTreeKey &rKey) const {
      const TestKey &r = static_cast<const TestKey &>(rKey);

      return m_key < r.m_key;
    }

    virtual void Visit() { printf("\n Key: %d", m_key); }
  };

  class TestValue : public BTreeValue {
  public:
    TestValue(int val) : m_value(val) {}

    ~TestValue() {}

    virtual void Visit() { printf("\n Value: %d", m_value); }

    int m_value;
  };

  class TestInOrderVisitor : public BTree::InOrderVisitor {
  public:
    mutable int m_bAbort;
    mutable int m_iCount;
    const int MaxElements;
    int *m_arrKey;
    int *m_arrVal;

    TestInOrderVisitor(int n, int *k, int *v) : m_bAbort(false), m_iCount(0), MaxElements(n), m_arrKey(k),
                                                m_arrVal(v) {}

    void operator()(const BTreeKey &rKey, BTreeValue *pValue) {
      const TestKey &key = static_cast<const TestKey &>(rKey);
      const TestValue *value = static_cast<const TestValue *>(pValue);

      ASSERT(m_iCount, < , MaxElements);
      ASSERT(key.m_key, == , m_arrKey[m_iCount]);
      ASSERT(value->m_value, == , m_arrVal[m_iCount]);

      m_iCount++;
    }

    bool Abort() const { return m_bAbort; }
  };

  void testBTree1() {
    BTree tree;
    BTree::DestroyKeyValue d;
    tree.SetDestoryKeyValueCallBack(&d);
    int k[102], v[102];
    for (int i = 0; i < 102; i++) {
      TestKey *pKey = new TestKey(i);
      TestValue *pValue = new TestValue(i * 10);
      k[i] = i;
      v[i] = i * 10;
      ASSERT(tree.Insert(pKey, pValue), ==, true);
    }
    int key = 63;
    TestValue *pValue = (TestValue *) tree.Find(TestKey(key));
    ASSERT(pValue, !=, NULL);
    ASSERT(pValue->m_value, ==, 630);
    TestInOrderVisitor t(102, k, v);
    tree.InOrderTraverse(t);
  }

  void testBTree2() {
    BTree tree;
    BTree::DestroyKeyValue d;
    tree.SetDestoryKeyValueCallBack(&d);
    const int N = 522;
    int k[N], v[N];

    auto seed = clock();
    for (int i = 0; i < N; i++) {
      k[i] = (seed * (i + 1))  % N;
      v[i] = (seed * 3 * (i + 1)) % N;

      TestKey *pKey = new TestKey(k[i]);
      TestValue *pValue = new TestValue(v[i]);

      ASSERT(tree.Insert(pKey, pValue), ==, true);
    }

    for (int i = 0; i < N; i++)
      for (int j = i + 1; j < N; j++) {
        if (k[i] > k[j]) {
          int t = k[i];
          k[i] = k[j];
          k[j] = t;

          t = v[i];
          v[i] = v[j];
          v[j] = t;
        }
      }

    TestInOrderVisitor t(N, k, v);
    tree.InOrderTraverse(t);
  }

  static void remove_arr(int *arr, int size, int index) {
    for (int i = index; i < size - 1; i++)
      arr[i] = arr[i + 1];
  }

  void testBTree3() {
    BTree tree;
    BTree::DestroyKeyValue d;
    tree.SetDestoryKeyValueCallBack(&d);
    const int N = 322;
    int k[N], v[N];

    for (int i = 0; i < N; i++) {
      k[i] = i;
      v[i] = i * 10;

      TestKey *pKey = new TestKey(k[i]);
      TestValue *pValue = new TestValue(v[i]);

      ASSERT(tree.Insert(pKey, pValue), ==, true);
    }

    TestInOrderVisitor tiv(N, k, v);
    tree.InOrderTraverse(tiv);

    int size = N;
    int pos1 = N - 122;
    TestKey t1(k[pos1]);
    ASSERT(tree.Delete(t1), ==, true);
    remove_arr(k, size, pos1);
    remove_arr(v, size, pos1);
    --size;

    TestInOrderVisitor tiv1(size, k, v);
    tree.InOrderTraverse(tiv1);

    for (int i = 0; i < 200; i++) {
      int pos = clock() % size;
      TestKey t(k[pos]);
      ASSERT(tree.Delete(t), == , true);

      remove_arr(k, size, pos);
      remove_arr(v, size, pos);
      --size;
    }

    TestInOrderVisitor tiv2(size, k, v);
    tree.InOrderTraverse(tiv2);
  }
};

REGISTER_TEST_SUITE(TestBTree)