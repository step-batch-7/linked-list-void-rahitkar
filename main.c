#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

typedef Element (*Take_input)(void);

void print_int(Element number)
{
  printf(" %d", *(int *)number);
}

Status is_int_equal(Element num1, Element num2)
{
  return *(int *)num1 == *(int *)num2;
}

void show_menu()
{
  printf("Main Menu\n---------\n(a) add a number to the end of the list\n(b) add a number to the start of the list\n(c) insert a number at a given position in the list\n(d) add a unique item on the list at the end(if it alreay exists, do not insert)\n(e) remove a number from the beginning of the list\n(f) remove a number from the end of the list\n(g) remove a number from a given position in the list\n(h) remove first occurrence of a number\n(i) remove all occurrences of a number\n(j) clear the whole list\n(k) check if a number exists in the list\n(l) display the list of numbers\n(m) exit\n\nPlease enter the alphabet of the operation you would like to perform ");
}

void* take_int_input()
{
  int input;
  int *number = malloc(sizeof(int));
  printf("enter your number ");
  scanf("%d", &input);
  *number = input;
  return number;
}

void* take_char_input()
{
  char input;
  char *number = malloc(sizeof(char));
  printf("enter your number ");
  scanf(" %c", &input);
  *number = input;
  return number;
}

int take_position_input()
{
  int position;
  printf("enter position ");
  scanf("%d", &position);
  return position;
}

void show_result(Status result, Char_ptr message)
{
  if (result)
  {
    printf("element %s\n", message);
    return;
  }
  printf("element not %s\n", message);
  return;
}

void oparate_on(List_ptr list, char option, Take_input input, Print print, Matcher matcher)
{
  Element element;
  int result,  position;
  switch (option)
  {
  case 'a':
    element = input();
    show_result(add_to_list(list, element), "added");
    break;

  case 'b':
    element = input();
    show_result(add_to_start(list, element), "added");
    break;

  case 'c':
    element = input();
    position = take_position_input();
    show_result(insert_at(list, element, position), "added");
    break;

  case 'd':
    element = input();
    show_result(add_unique(list, element, matcher), "added");
    break;

  case 'e':
    (*print)(remove_from_start(list));
    break;

  case 'f':
    (*print)(remove_from_end(list));
    break;

  case 'g':
    position = take_position_input();
    (*print)(remove_at(list, position));
    break;

  case 'h':
    element = input();
    (*print)(remove_first_occurrence(list, element, matcher));
    break;

  case 'i':
    element = input();
    List_ptr removed_element_list = remove_all_occurrences(list, element, matcher);
    display(removed_element_list, print);
    break;

  case 'j':
    show_result(clear_list(list), "cleared");
    break;

  case 'k':
    element = input();
    result = search(list, element, matcher) < list->length ? 1 : 0;
    show_result(result, "exits");
    break;

  case 'l':
    display(list, print);
    break;

  case 'm':
    printf("closing the  main menu\n");
    break;

  default:
    printf("option not listed\n");
    break;
  }
}

int main(void)
{
  char option;
  List_ptr list = create_list();
  while (option != 'm')
  {
    show_menu();
    scanf(" %c", &option);
    oparate_on(list, option, &take_int_input, &print_int, &is_int_equal);
  }
  destroy_list(list);
  return 0;
}