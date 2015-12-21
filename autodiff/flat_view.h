#pragma once

// flat_view: Take a container [of container]* of leaf_type, and iterate through all the leaves.

#include "template_utils.h"
#include "container_depth.h"

template <class Iter, class SubIter>
struct nested_iterator {
  typedef nested_iterator<Iter, SubIter> this_t;

  Iter i;
  Iter end;  // Need this in order to check whether to ripple subiter

  // SubIter should be constructible from i->begin();
  // typedef decltype(std::declval<Iter>()->begin()) subiter_t;

  SubIter subiter;
  SubIter subiter_end;

  nested_iterator() {}

  nested_iterator(Iter i, Iter end) :i(i), end(end)
  {
    reset_subiter();
  }

  void reset_subiter()
  {
    if (i != end) {
      subiter = SubIter{ i->begin(), i->end() };
      subiter_end = SubIter{ i->end(), i->end() };
    }
  }

  // prefix
  this_t operator++()
  {
    ++subiter;
    if (subiter == subiter_end) {
      ++i;
      reset_subiter();
    }
    return *this;
  }

  decltype(*subiter) operator*() { return *subiter; }

  bool operator==(const this_t& that)
  {
    return i == that.i && (i == end || subiter == that.subiter);
  }
  bool operator!=(const this_t& that)
  {
    return !(*this == that);
  }
};

template <class Container, size_t depth>
struct define_flat_view;

template <class T>
struct define_flat_view<T, 0> {
  T& t;
  template <class U>
  define_flat_view(U&& t) :t(t) {}
  T* begin() { return &t; }
  T* end() { return 1+&t; }
};

template <class Container>
struct define_flat_view<Container, 1> {
  typedef typename get_iterator_type<Container>::type container_iter_t;
  // Adapt container iter to add a 2-argument constructor
  struct iterator : public container_iter_t {
    iterator() {}

    template <class U>
    iterator(U&& value, U&& end) :container_iter_t(value) {}
  };

  iterator begin_;
  iterator end_;

  template <class T>
  define_flat_view(T&& that) :
    begin_(that.begin(), that.end()),
    end_(that.end(), that.end())
  {
  }

  iterator begin() { return begin_; }
  iterator end() { return end_; }
};

template <class Container, size_t depth>
struct define_flat_view {
  typedef typename get_iterator_type<Container>::type container_iterator;
  typedef typename get_value_type<Container>::type value_t;
  typedef typename define_flat_view<value_t, depth - 1>::iterator subiter_t;
  typedef nested_iterator<container_iterator, subiter_t> iterator;

  iterator begin_;
  iterator end_;

  template <class T>
  define_flat_view(T&& that) :
    begin_(that.begin(), that.end()),
    end_(that.end(), that.end())
  {
  }

  iterator begin() { return begin_; }
  iterator end() { return end_; }
};



#include <list>
#include <vector>
void test_nested_iterator() {
  std::list<int> a = { 1, 2 };
  std::list<int> b = { 3,4,5 };
  typedef std::vector<std::list<int>> veclist;
  auto c = veclist{ a,b };
  auto d = veclist{ b,a };
  typedef std::list<veclist> A;
  A l = { c,d };

  //nested_iterator<A::value_type::iterator, define_flat_view<A::value_type,1>::iterator> ii{ c.begin(), c.end() };
  define_flat_view<A, 3> fv{ l };

  std::cout << "[";
  for (auto i : fv)
    std::cout << i << " ";
  std::cout << "] should have been [ 1 2 3 4 5 3 4 5 1 2 ]\n";
}

template <class Leaf, class Container>
typename define_flat_view<typename std::remove_reference<Container>::type, CONTAINER_DEPTH(Container, Leaf)> flat_view(Container&& c)
{
  return typename define_flat_view<typename std::remove_reference<Container>::type, CONTAINER_DEPTH(Container, Leaf)>{ c };
}


#include <iostream>
#include "Vec.h"
#include "Mat.h"

static_assert(container_depth<Vec<char, 2>, char>::depth == 1, "OIK");
static_assert(container_depth<const Vec<Vec<char, 2>, 2>, char>::depth == 2, "OIK");

void test_deep_iterator()
{
  test_nested_iterator();

  auto a = vec('i', 't');
  auto b = vec('e', 'r');
  auto const& c = vec(a, b);

  define_flat_view<std::remove_reference<decltype(c)>::type, 2>::iterator i{ c.begin(), c.end() };

  std::cout << "TEST DEEP ITER: iter=";
  for (auto p : flat_view<const char>(c))
    std::cout << p;
  std::cout << std::endl;

  std::cout << "TEST DEEP ITER: it=";
  for (auto p : flat_view<char>(a))
    std::cout << p;
  std::cout << std::endl;

  std::cout << "TEST DEEP ITER: d=";
  char d = 'd';
  for (auto p : flat_view<char>(d))
    std::cout << p;
  std::cout << std::endl;

  // xxfixme
  Vec<Vec<Vec<Real,4>,3>,2> f;
  double v = 1.1;
  for (auto& a : flat_view<Real>(f))
    a = (v += .3);

  std::cout << "4x3x2:";
  for (auto a : flat_view<Real>(f))
    std::cout << " " << a ;
  std::cout << std::endl;
#if 0
#endif
}

