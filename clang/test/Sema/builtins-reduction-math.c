// RUN: %clang_cc1 %s -pedantic -verify -triple=x86_64-apple-darwin9

typedef float float4 __attribute__((ext_vector_type(4)));
typedef int int3 __attribute__((ext_vector_type(3)));
typedef unsigned unsigned4 __attribute__((ext_vector_type(4)));

struct Foo {
  char *p;
};

void test_builtin_reduce_max(int i, float4 v, int3 iv) {
  struct Foo s = __builtin_reduce_max(iv);
  // expected-error@-1 {{initializing 'struct Foo' with an expression of incompatible type 'int'}}

  i = __builtin_reduce_max(v, v);
  // expected-error@-1 {{too many arguments to function call, expected 1, have 2}}

  i = __builtin_reduce_max();
  // expected-error@-1 {{too few arguments to function call, expected 1, have 0}}

  i = __builtin_reduce_max(i);
  // expected-error@-1 {{1st argument must be a vector type (was 'int')}}
}

void test_builtin_reduce_min(int i, float4 v, int3 iv) {
  struct Foo s = __builtin_reduce_min(iv);
  // expected-error@-1 {{initializing 'struct Foo' with an expression of incompatible type 'int'}}

  i = __builtin_reduce_min(v, v);
  // expected-error@-1 {{too many arguments to function call, expected 1, have 2}}

  i = __builtin_reduce_min();
  // expected-error@-1 {{too few arguments to function call, expected 1, have 0}}

  i = __builtin_reduce_min(i);
  // expected-error@-1 {{1st argument must be a vector type (was 'int')}}
}
