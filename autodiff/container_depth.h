template <class T>
struct container_depth {
  static const size_t depth = 0;
};

template <template <typename... Ts> class Container, typename... Ts>
struct container_depth<Container<Ts...>> {
  typedef typename Container<Ts...>::value_type inner_t;
  static const size_t depth = 1 + container_depth<inner_t>::depth;
};

template <template <typename T, int N, typename... Ts> class Container, typename T, int N, typename... Ts>
struct container_depth<Container<T, N, Ts...>> {
  typedef typename Container<T, N, Ts...>::value_type inner_t;
  static const size_t depth = 1 + container_depth<inner_t>::depth;
};

#include <vector>
#include <list>
static_assert(container_depth<std::vector<std::list<double>>>::depth == 2, "container_depth test fail");
//static_assert(container_depth<Vec<Vec<float, 3, Vec_ZE>, 2>>::depth == 2, "container_depth test fail");
//static_assert(container_depth<double>::depth == 0, "container_depth fail");
