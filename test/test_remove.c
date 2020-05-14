#include "../linkedlist.h"
#include "lindedlist_test.h"
#include "test_remove.h"

void test_remove_functions()
{
  describe("remove_from_start");
  List_ptr list1 = create_list();
  add_to_start(list1, create_int_element(2));
  Element removed_element = remove_from_start(list1);

  List_ptr list2 = create_list();
  it("should return removed element and should modifie given single node list", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(2)));

  add_to_start(list1, create_int_element(4));
  add_to_start(list1, create_int_element(6));
  removed_element = remove_from_start(list1);

  add_to_start(list2, create_int_element(4));
  it("Should return removed element and modifie given list as single node with element 4 in first", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(6)));

  describe("remove_from_end");
  list1 = create_list();
  add_to_start(list1, create_int_element(4));
  removed_element = remove_from_end(list1);

  list2 = create_list();
  it("should return removed element and should modifie the given list with single node", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(4)));

  add_to_start(list1, create_int_element(4));
  add_to_start(list1, create_int_element(6));
  removed_element = remove_from_end(list1);

  add_to_start(list2, create_int_element(6));
  it("Should return removed element and should modifie given list as single node with element 6 in it", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(4)));

  describe("remove_at");
  list1 = create_list();
  add_to_start(list1, create_int_element(4));
  removed_element = remove_at(list1, 0);

  list2 = create_list();
  it("should return removed element and should modifie the given list with single node", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(4)));

  add_to_start(list1, create_int_element(4));
  add_to_start(list1, create_int_element(6));
  removed_element = remove_at(list1, 1);

  add_to_start(list2, create_int_element(6));
  it("Should return removed element and should modifie given list as single node with element 6 in it", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(4)));

  add_to_start(list1, create_int_element(4));
  add_to_start(list1, create_int_element(8));
  removed_element = remove_at(list1, 1);

  add_to_start(list2, create_int_element(8));
  it("Should return removed element and should modifie given list which will have two nodes after modification", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(4)));

  describe("remove_first_occurrence");
  add_to_start(list1, create_int_element(6));
  removed_element = remove_first_occurrence(list1, create_int_element(6), &is_int_equal);

  it("should remove and return first matched element from given list", assert_list(list1, list2, &is_int_equal) && is_int_equal(removed_element, create_int_element(6)));

  removed_element = remove_first_occurrence(list1, create_int_element(10), &is_int_equal);

  it("should return null and should not remove any element for given element which doesn't match with list elements", assert_list(list1, list2, &is_int_equal) && removed_element == NULL);

  describe("remove_all_occurrences");
  add_to_start(list1, create_int_element(6));
  List_ptr removed_elements = remove_all_occurrences(list1, create_int_element(6), &is_int_equal);

  remove_from_end(list2);

  List_ptr expected_removed_elements = create_list();
  add_to_list(expected_removed_elements, create_int_element(6));
  add_to_list(expected_removed_elements, create_int_element(6));

  it("should remove and return all matched elements from given list", assert_list(list1, list2, &is_int_equal) && assert_list(removed_elements, expected_removed_elements, &is_int_equal));

  remove_all_occurrences(list1, create_int_element(10), &is_int_equal);

  it("should return null and should not remove any element for given element which doesn't match with list elements", assert_list(list1, list2, &is_int_equal));
}