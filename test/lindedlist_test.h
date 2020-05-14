#ifndef __LINKEDLIST_TEST_H_
#define __LINKEDLIST_TEST_H_

#include "../linkedlist.h"

void describe(Char_ptr message);
void it(Char_ptr message, Status status);

void print_int(Element number);
Status is_int_equal(Element num1, Element num2);
Element create_int_element(int value);

Status assert_empty_list();
Status assert_list(List_ptr list1, List_ptr list2, Matcher matcher);
#endif