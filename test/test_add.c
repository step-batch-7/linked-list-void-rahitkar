#include "../linkedlist.h"
#include "linkedlist_test.h"
#include "test_add.h"

void test_add_functions()
{
  describe("add_to_start");
  List_ptr list1 = create_list();
  add_to_start(list1, create_int_element(2));

  List_ptr list2 = create_list();
  list2->first = create_node(create_int_element(2));
  list2->last = list2->first;
  list2->length++;
  it("should return a list with one node added to start for given empty list", assert_list(list1, list2, &is_int_equal));

  add_to_start(list1, create_int_element(4));

  Node_ptr previous_first = list2->first;
  list2->first = create_node(create_int_element(4));
  list2->first->next = previous_first;
  list2->length++;
  it("Should return a list with two nodes with element 4 in first and element 2 in last", assert_list(list1, list2, &is_int_equal));

  describe("add_to_end");
  list1 = create_list();
  add_to_list(list1, create_int_element(2));

  list2 = create_list();
  list2->first = create_node(create_int_element(2));
  list2->last = list2->first;
  list2->length++;
  it("should return a list with one node added to last for given empty list", assert_list(list1, list2, &is_int_equal));

  add_to_list(list1, create_int_element(4));

  list2->last = create_node(create_int_element(4));
  list2->first->next = list2->last;
  list2->length++;
  it("Should return a list with two nodes with element 2 in first and element 4 in last", assert_list(list1, list2, &is_int_equal));

  describe("insert_at");
  list1 = create_list();
  insert_at(list1, create_int_element(2), 0);

  list2 = create_list();
  list2->first = create_node(create_int_element(2));
  list2->last = list2->first;
  list2->length++;
  it("should return a list with one node added in position zero for given empty list", assert_list(list1, list2, &is_int_equal));

  insert_at(list1, create_int_element(4), 1);

  list2->last = create_node(create_int_element(4));
  list2->first->next = list2->last;
  list2->length++;
  it("Should return a list with two nodes with element 2 in first and element 4 in last", assert_list(list1, list2, &is_int_equal));

  insert_at(list1, create_int_element(6), 1);

  list2->first->next = create_node(create_int_element(6));
  list2->first->next->next = list2->last;
  list2->length++;
  it("Should return a list with three nodes with element 2 in first element 6 in middle and element 4 in last", assert_list(list1, list2, &is_int_equal));

  describe("add_unique");
  add_unique(list1, create_int_element(10), &is_int_equal);

  list2->last = create_node(create_int_element(10));
  list2->first->next->next->next = list2->last;
  list2->length++;
  it("should add a node at last with given unique given value", assert_list(list1, list2, &is_int_equal));

  add_unique(list1, create_int_element(10), &is_int_equal);
  it("should not add a node with given not unique value", assert_list(list1, list2, &is_int_equal));
}