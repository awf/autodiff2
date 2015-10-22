
// variadic copy functions

template <typename Iter, typename T>
void copy(Iter p, T t)
{
  *p = t;
}

template <typename Iter, typename T, typename... Ts>
void copy(Iter p, T t, Ts... ts)
{
  *p++ = t;
  copy(p, ts...);
}

