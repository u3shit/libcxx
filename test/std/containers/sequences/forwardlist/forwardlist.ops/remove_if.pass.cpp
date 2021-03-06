//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <forward_list>

// template <class Predicate> void remove_if(Predicate pred);

#include <forward_list>
#include <iterator>
#include <cassert>
#include <cstddef>

#include "test_macros.h"
#include "min_allocator.h"
#include "counting_predicates.hpp"


bool g(int i)
{
    return i < 3;
}

struct PredLWG529 {
    PredLWG529 (int i) : i_(i) {};
    ~PredLWG529() { i_ = -32767; }
    bool operator() (const PredLWG529 &p) const { return p.i_ == i_; }

    bool operator==(int i) const { return i == i_;}
    int i_;
};

int main(int, char**)
{
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T> C;
        const T t1[] = {0, 5, 5, 0, 0, 0, 5};
        const T t2[] = {5, 5, 5};
        C c1(std::begin(t1), std::end(t1));
        C c2(std::begin(t2), std::end(t2));
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 4);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T> C;
        const T t1[] = {0, 0, 0, 0};
        C c1(std::begin(t1), std::end(t1));
        C c2;
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 4);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T> C;
        const T t1[] = {5, 5, 5};
        const T t2[] = {5, 5, 5};
        C c1(std::begin(t1), std::end(t1));
        C c2(std::begin(t2), std::end(t2));
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 0);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T> C;
        C c1;
        C c2;
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 0);
        assert(c1 == c2);
        assert(cp.count() == 0);
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T> C;
        const T t1[] = {5, 5, 5, 0};
        const T t2[] = {5, 5, 5};
        C c1(std::begin(t1), std::end(t1));
        C c2(std::begin(t2), std::end(t2));
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 1);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }

    { // LWG issue #526
    int a1[] = {1, 2, 1, 3, 5, 8, 11};
    int a2[] = {   2,    3, 5, 8, 11};
    std::forward_list<PredLWG529> c(a1, a1 + 7);
    c.remove_if(std::ref(c.front()));
    for (size_t i = 0; i < 5; ++i)
    {
        assert(!c.empty());
        assert(c.front() == a2[i]);
        c.pop_front();
    }
    assert(c.empty());
    }

#if TEST_STD_VER >= 11
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T, min_allocator<T>> C;
        const T t1[] = {0, 5, 5, 0, 0, 0, 5};
        const T t2[] = {5, 5, 5};
        C c1(std::begin(t1), std::end(t1));
        C c2(std::begin(t2), std::end(t2));
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 4);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T, min_allocator<T>> C;
        const T t1[] = {0, 0, 0, 0};
        C c1(std::begin(t1), std::end(t1));
        C c2;
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 4);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T, min_allocator<T>> C;
        const T t1[] = {5, 5, 5};
        const T t2[] = {5, 5, 5};
        C c1(std::begin(t1), std::end(t1));
        C c2(std::begin(t2), std::end(t2));
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 0);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T, min_allocator<T>> C;
        C c1;
        C c2;
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 0);
        assert(c1 == c2);
        assert(cp.count() == 0);
    }
    {
        typedef int T;
        typedef unary_counting_predicate<bool(*)(T), T> Predicate;
        typedef std::forward_list<T, min_allocator<T>> C;
        const T t1[] = {5, 5, 5, 0};
        const T t2[] = {5, 5, 5};
        C c1(std::begin(t1), std::end(t1));
        C c2(std::begin(t2), std::end(t2));
        Predicate cp(g);
        assert(c1.remove_if(std::ref(cp)) == 1);
        assert(c1 == c2);
        assert(cp.count() == static_cast<std::size_t>(std::distance(std::begin(t1), std::end(t1))));
    }
#endif

  return 0;
}
