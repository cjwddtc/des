#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdio.h>
#include <time.h>

template <typename value_type, size_t x, size_t y>
using two_array = std::array<std::array<value_type, y>, x>;
unsigned char s_array[8][64] = {
    {14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0, 7,
     4,  1,  14, 8, 13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5, 0,
     0,  15, 7,  4, 14, 2,  13, 1,  10, 6,  12, 11, 9,  5,  3, 8,
     15, 12, 8,  2, 4,  9,  1,  7,  5,  11, 3,  14, 10, 0,  6, 13},

    {15, 1,  8,  14, 6,  11, 3,  4,  9,  7, 2,  13, 12, 0, 5,  10,
     0,  14, 7,  11, 10, 4,  13, 1,  5,  8, 12, 6,  9,  3, 2,  15,
     3,  13, 4,  7,  15, 2,  8,  14, 12, 0, 1,  10, 6,  9, 11, 5,
     13, 8,  10, 1,  3,  15, 4,  2,  11, 6, 7,  12, 0,  5, 14, 9},

    {10, 0,  9,  14, 6, 3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
     13, 6,  4,  9,  8, 15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
     13, 7,  0,  9,  3, 4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,
     1,  10, 13, 0,  6, 9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12},

    {7,  13, 14, 3, 0,  6,  9,  10, 1,  2, 8, 5,  11, 12, 4,  15,
     10, 6,  9,  0, 12, 11, 7,  13, 15, 1, 3, 14, 5,  2,  8,  4,
     13, 8,  11, 5, 6,  15, 0,  3,  4,  7, 2, 12, 1,  10, 14, 9,
     3,  15, 0,  6, 10, 1,  13, 8,  9,  4, 5, 11, 12, 7,  2,  14},

    {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0, 14, 9,
     4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3, 0,  14,
     14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9, 8,  6,
     11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3},

    {12, 1,  10, 15, 9, 2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
     9,  14, 15, 5,  2, 8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
     10, 15, 4,  2,  7, 12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8,
     4,  3,  2,  12, 9, 5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13},

    {4,  11, 2,  14, 15, 0, 8,  13, 3,  12, 9, 7,  5,  10, 6, 1,
     1,  4,  11, 13, 12, 3, 7,  14, 10, 15, 6, 8,  0,  5,  9, 2,
     13, 0,  11, 7,  4,  9, 1,  10, 14, 3,  5, 12, 2,  15, 8, 6,
     6,  11, 13, 8,  1,  4, 10, 7,  9,  5,  0, 15, 14, 2,  3, 12},

    {13, 2,  8,  4, 6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
     7,  11, 4,  1, 9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
     1,  15, 13, 8, 10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2,
     2,  1,  14, 7, 4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11}};
two_array<unsigned long, 8, 64> s_box_array;
std::array<unsigned char, 32> p_box_data = {
    16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
    2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25};
two_array<unsigned long, 4, 256> p_box_array;
std::array<unsigned char, 48> extend_data = {
    32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,  8,  9,  10, 11,
    12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
two_array<unsigned long long, 4, 256> extend_array;

unsigned char key_shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
std::array<unsigned char, 28> p1_l = {57, 49, 41, 33, 25, 17, 9,  1,  58, 50,
                                      42, 34, 26, 18, 10, 2,  59, 51, 43, 35,
                                      27, 19, 11, 3,  60, 52, 44, 36};
std::array<unsigned char, 28> p1_r = {63, 55, 47, 39, 31, 23, 15, 7,  62, 54,
                                      46, 38, 30, 22, 14, 6,  61, 53, 45, 37,
                                      29, 21, 13, 5,  28, 20, 12, 4};
std::array<unsigned char, 48> p2 = {
    14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10, 23, 19, 12, 4,
    26, 8,  16, 7,  27, 20, 13, 2,  41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

two_array<unsigned long long, 8, 256> p2_array;
two_array<unsigned long, 8, 256> p1_l_array;
two_array<unsigned long, 8, 256> p1_r_array;

namespace no_use {
template <size_t IN, size_t n> struct t_log_ { static size_t value; };
template <size_t IN, size_t n>
size_t t_log_<IN, n>::value = t_log_<IN / 2, n + 1>::value;
template <size_t n> struct t_log_<0, n> { static size_t value; };
template <size_t n> size_t t_log_<0, n>::value = n;
}
template <size_t IN> size_t t_log = no_use::t_log_<IN - 1, 0>::value;
namespace no_use {
template <size_t x, size_t y, typename in_type, typename out_type,
          size_t count_ = 0>
struct tran {
  static inline out_type f(const in_type in,
                           const two_array<out_type, x, y> &array) {
    return array[count_][in & ((0x1 << t_log<y>)-1)] |
           tran<x, y, in_type, out_type, count_ + 1>::f(in >> t_log<y>, array);
  };
};
template <size_t x, size_t y, typename in_type, typename out_type>
struct tran<x, y, in_type, out_type, x> {
  static inline out_type f(const in_type in,
                           const two_array<out_type, x, y> &array) {
    return 0;
  };
};
}

template <size_t x, size_t y, typename in_type, typename out_type>
static inline out_type map(const in_type in,
                           const two_array<out_type, x, y> &array) {
  return no_use::tran<x, y, in_type, out_type>::f(in, array);
}

// init map by data
template <size_t x, size_t y, typename out_type, size_t size>
static inline void init(std::array<unsigned char, size> source,
                        two_array<out_type, x, y> &map) {
  std::multimap<unsigned char, signed char> cache;
  for (signed char i = 0; i < size; i++) {
    cache.insert(
        std::make_pair(source[i], i - (source[i] & (1 << t_log<y>)-1)));
  }
  for (out_type i = 0; i < 256; i++)
    for (unsigned n = 0; n < x; n++)
      for (unsigned j = 0; j < t_log<y>; j++)
        for (auto it = cache.equal_range(n * t_log<y> + j).first;
             it != cache.equal_range(n * t_log<y> + j).second; it++)
          map[n][i] |= it->second > 0 ? (i & 0x1u << j) << it->second
                                      : (i & 0x1u << j) >> -it->second;
}
template <typename T> static inline void dec_all(T &a) {
  std::transform(
      a.begin(), a.end(), a.begin(),
      std::bind(std::minus<unsigned char>(), std::placeholders::_1, 1));
}

void init_s() {
  for (unsigned i = 1; i < 8; i++) {
    for (unsigned j = 0; j < 64; j++) {
      s_box_array[i][j] = s_array[i][j];
      s_box_array[i][j] <<= 4 * i;
    }
  }
}

void init() {
  dec_all(p_box_data);
  dec_all(p1_l);
  dec_all(p1_r);
  dec_all(p2);
  dec_all(extend_data);
  init(extend_data, extend_array);
  init(p_box_data, p_box_array);
  init(p1_l, p1_l_array);
  init(p1_r, p1_r_array);
  init(p2, p2_array);
  init_s();
}

unsigned long f(unsigned long value, unsigned long long key) {
  return map(map(map(value, extend_array) ^ key, s_box_array), p_box_array);
}

unsigned long long des(unsigned long long value, unsigned long long keys[16]) {
  unsigned long left = value;
  unsigned long right = value >> 32;
  unsigned long tmp;
  for (unsigned i = 0; i < 16; i++) {
    tmp = left;
    left = right;
    right = tmp ^ f(right, keys[i]);
  }
  value = right;
  value <<= 32;
  return left | value;
}

unsigned long long ddes(unsigned long long value, unsigned long long keys[16]) {
  unsigned long left = value;
  unsigned long right = value >> 32;
  unsigned long tmp;
  for (int i = 15; i >= 0; i--) {
    tmp = right;
    right = left;
    left = tmp ^ f(right, keys[i]);
  }
  value = right;
  value <<= 32;
  return left | value;
}

void gen_sub_key(unsigned long long key, unsigned long long keys[16]) {
  unsigned long long left = map(key, p1_l_array);
  left |= left << 28;
  unsigned long long right = map(key, p1_r_array);
  right |= right << 28;
  for (unsigned i = 0; i < 16; i++) {
    left >>= key_shift[i];
    right >>= key_shift[i];
    unsigned long long key_ = (left & 0xfffffff) | right << 28;
    keys[i] = map(key_, p2_array);
  }
  return;
}

void bmp_tran_des(std::iostream &stream, unsigned long long keys[16]) {
  char a[14];
  stream.seekg(0, std::ios_base::beg);
  stream.read(a, 14);
  unsigned long m = *(unsigned long *)&a[2];
  unsigned long n = *(unsigned long *)&a[10];
  stream.seekg(n, std::ios_base::beg);
  char *ptr = (char *)malloc(m - n);
  stream.read(ptr, m - n);
  *(unsigned long long *)ptr = des(*(unsigned long long *)ptr, keys);
  unsigned long long *lptr =
      (unsigned long long *)(ptr + ((m - n - 1) & 0x7) + 1);
  for (unsigned i = 0; i<(m - n - 1)>> 3; i++) {
    *lptr++ = des(*lptr, keys);
  }
  stream.seekp(n, std::ios_base::beg);
  stream.write(ptr, m - n);
  return;
}

void bmp_tran_ddes(std::iostream &stream, unsigned long long keys[16]) {
  char a[14];
  stream.seekg(0, std::ios_base::beg);
  stream.read(a, 14);
  unsigned long m = *(unsigned long *)&a[2];
  unsigned long n = *(unsigned long *)&a[10];
  stream.seekg(n, std::ios_base::beg);
  char *ptr = (char *)malloc(m - n);
  stream.read(ptr, m - n);
  unsigned long long *lptr =
      (unsigned long long *)(ptr + ((m - n - 1) & 0x7) + 1);
  for (unsigned i = 0; i<(m - n - 1)>> 3; i++) {
    *lptr++ = ddes(*lptr, keys);
  }
  *(unsigned long long *)ptr = ddes(*(unsigned long long *)ptr, keys);
  stream.seekp(n, std::ios_base::beg);
  stream.write(ptr, m - n);
  return;
}

int main() {
  init();
  unsigned long long keys[16];
  gen_sub_key(0x0, keys);
  std::fstream f("asd.bmp");
  bmp_tran_ddes(f, keys);
  f.close(); /*
  unsigned long long m = 0x1;
  scanf("%llx", &m);
  printf("%llx", ddes(des(m, keys), keys));*/
  return 0;
}
