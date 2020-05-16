#include "../linkedlist.h"
#include "linkedlist_test.h"
#include "test_list_methods.h"

Element int_sqr(Element num)
{
  Int_ptr result = malloc(sizeof(int));
  *result = (*(Int_ptr)num * *(Int_ptr)num);
  return result;
}

Status is_even(Element num)
{
  return !(*(Int_ptr)num % 2);
}

Element int_sum(Element num, Element cotext)
{
  Int_ptr result = malloc(sizeof(int));
  *result = *(Int_ptr)num + *(Int_ptr)cotext;
  return result;
}

void increment(Element num)
{
  *(int*)num = *(int*)num +1;
}

void test_map(List_ptr list, Mapper mapper)
{
  int expected[] = {1, 4, 9, 16};

  List_ptr new_list = map(list, mapper);

  describe("map");
  it("should return a new list created by mapped from the given list elements", assert_list(create_linked_list(expected, 4, sizeof(int)), new_list, &is_int_equal));
}

void test_filter(List_ptr list, Predicate predicate)
{
  int expected[] = {2, 4};

  List_ptr new_list = filter(list, predicate);

  describe("filter");
  it("should return a new list created by sorted by filter from the given list elements", assert_list(create_linked_list(expected, 2, sizeof(int)), new_list, &is_int_equal));
}

void test_reduce(List_ptr list, Reducer reducer)
{
  Element expected_element = create_int_element(10);

  Element init = create_int_element(0);
  describe("reduce");
  it("should return a element created by reducer", is_int_equal(reduce(list, init, reducer), expected_element));
}

void test_forEach(List_ptr list, ElementProcessor processor)
{
  int expected[] = {2, 3, 4, 5};

  forEach(list, processor);

  describe("forEach");
  it("should modifie given list by processor function on given list element", assert_list(list,create_linked_list(expected, 4, sizeof(4)), &is_int_equal));
}

void test_reverse(List_ptr list)
{
  int expected[] = {5, 4, 3, 2};

  List_ptr reversed_list = reverse(list);

  describe("reverse");
  it("should return a reversed new list", assert_list(reversed_list, create_linked_list(expected, 4, sizeof(int)), &is_int_equal));  
}

void test_list_method_functions()
{
  int numbers[] = {1, 2, 3, 4};

  List_ptr list = create_linked_list(numbers, 4, sizeof(4));

  test_map(list, &int_sqr);
  test_filter(list, &is_even);
  test_reduce(list, &int_sum);
  test_forEach(list, &increment);
  test_reverse(list);
}