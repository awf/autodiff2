#pragma once

// flat_view: Take a container [of container]* of leaf_type, and iterate through all the leaves.

#include "template_utils.h"
#include "container_depth.h"

template <class Iterator, class SubIter>
struct nested_iterator {
  typedef nested_iterator<Iterator, SubIter> this_t;

  Iterator i;
  Iterator end;  // Need this in order to check whether to ripple subiter

  // SubIter should be constructible from i->begin();
  // typedef decltype(std::declval<Iterator>()->begin()) subiter_t;

  SubIter subiter;
  SubIter subiter_end;

  nested_iterator() {}

  nested_iterator(Iterator i, Iterator end) :i(i), end(end)
  {
    reset_subiter();
  }

  void reset_subiter()
  {
    if (i != end) {
      subiter = i->begin();
      subiter_end = i->end();
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

#include <list>
#include <vector>
void test_nested_iterator() {
  std::list<int> a = { 1, 2 };
  std::list<int> b = { 3,4,5 };
  typedef std::vector<std::list<int>> veclist;
  auto c = veclist { a,b };

  nested_iterator<veclist::iterator, veclist::value_type::iterator> i{ c.begin(), c.end() };

  for (; i.i != i.end; ++i)
    std::cout << "[" << *i << "]" << std::endl;
}

// How it's done: the proxy class iterates over the outer container, setting up a flat_view
// of each element, and has an operator++ that increments the inner iters.

template <class T, size_t depth>
struct flat_view_proxy;

template <class Leaf>
struct flat_view_proxy<Leaf, 0> {
  // Just a leaf - wrap it in a one-shot iter
  Leaf* value;
  flat_view_proxy(Leaf& l) : value(&l) {}
  typedef Leaf* iterator;
  iterator begin() { return value; }
  iterator end() { return value + 1; }
};

template <class Container>
struct flat_view_proxy<Container, 1> {
  // Container, not nested, just use its iters
  typedef typename get_iterator_type<Container>::type iter_t;

  iter_t begin_;
  iter_t end_;

  flat_view_proxy(Container& c) :begin_(c.begin()), end_(c.end()) {}

  iter_t begin() { return begin_; }
  iter_t end() { return end_; }
};

template <class Container, size_t depth>
struct flat_view_proxy {
  // Should behave like a container, but with iters that step over subcontainer iters;
  typedef typename get_iterator_type<Container>::type container_iter_t; // If container is const, this will be a const_iterator
  typedef typename get_value_type<Container>::type value_t;
  
  typedef flat_view_proxy<value_t, depth-1> subcontainer_t;
  typedef typename get_iterator_type<subcontainer_t>::type subiter_t;

  typedef nested_iterator<container_iter_t, subiter_t> iterator;

  container_iter_t begin_;
  container_iter_t end_;

  flat_view_proxy(Container& c) : begin_(c.begin()), end_(c.end()) {}

  iterator begin() {
    return iterator{ begin_, end_ };
  }

  iterator end() {
    container_iter_t i = end_;
    container_iter_t end = end_; // fixme

    return iterator{ end_, end_ };
  }
};

template <class Leaf, class Container>
flat_view_proxy<Container, CONTAINER_DEPTH(Container, Leaf)> flat_view(Container& c)
{
  return flat_view_proxy<Container, CONTAINER_DEPTH(Container, Leaf)>(c);
}

#include <iostream>
#include "Vec.h"
void test_deep_iterator()
{
  test_nested_iterator();

  auto a = vec('i', 't');
  auto b = vec('e', 'r');
  auto const& c = vec(a, b);

  std::cout << "TEST DEEP ITER: iter=";
  for (auto p : flat_view<char>(c))
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
}
