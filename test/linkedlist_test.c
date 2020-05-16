#include <stdio.h>

#include "linkedlist_test.h"

#define SUCCESS_SYMBOL "    ✅ "
#define FAILURE_SYMBOL "    ❌ "

void describe(Char_ptr message)
{
  printf("%s\n", message);
}

void it(Char_ptr message, Status status)
{
  if (status)
  {
    printf(SUCCESS_SYMBOL);
    printf("%s\n", message);
    return;
  }
  printf(FAILURE_SYMBOL);
  printf("%s\n", message);
}

void print_int(Element number)
{
  printf(" %d", *(int *)number);
}

Status is_int_equal(Element num1, Element num2)
{
  return *(int *)num1 == *(int *)num2;
}

Status assert_empty_list()
{
  List_ptr list = create_list();

  return list->first == NULL && list->last == NULL && list->length == 0;
}

Element create_int_element(int value)
{
  Int_ptr element = malloc(sizeof(int));
  *element = value;
  return element;
}

List_ptr create_linked_list(void* src, int length, int data_size)
{
  List_ptr new_list = create_list();
  while (new_list->length < length)
  {
    add_to_list(new_list, src + (new_list->length * data_size));
  }
  return new_list;
}

Status assert_list(List_ptr list1, List_ptr list2, Matcher matcher)
{
  if (list1->length != list2->length)
  {
    return Failure;
  }

  Node_ptr p_walk1 = list1->first;
  Node_ptr p_walk2 = list2->first;
  while (p_walk1 != NULL)
  {
    if (!(*matcher)(p_walk1->element, p_walk2->element))
    {
      return Failure;
    }
    p_walk1 = p_walk1->next;
    p_walk2 = p_walk2->next;
  }
  return Success;
}
