#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

List_ptr create_list(void)
{
  List_ptr linkedlist = malloc(sizeof(LinkedList));
  if (linkedlist == NULL)
  {
    printf("Memory is not available");
    exit(1);
  }
  linkedlist->first = NULL;
  linkedlist->last = NULL;
  linkedlist->length = 0;
  return linkedlist;
}

Node_ptr create_node(Element value)
{
  Node_ptr new_node = malloc(sizeof(Node));
  if (new_node == NULL)
  {
    printf("Memory is not available");
    exit(1);
  }
  new_node->element = value;
  new_node->next = NULL;

  return new_node;
}

Status insert_at(List_ptr list, Element value, int position)
{
  if (list->length < position || position < 0)
  {
    return Failure;
  }

  if (position == 0)
  {
    return add_to_start(list, value);
  }

  if (position == list->length)
  {
    return add_to_list(list, value);
  }

  Node_ptr p_walk = list->first;
  Node_ptr previous_node = list->first;
  int counter = 0;
  while (counter != position)
  {
    previous_node = p_walk;
    p_walk = p_walk->next;
    counter++;
  }
  Node_ptr new_node = create_node(value);
  previous_node->next = new_node;
  new_node->next = p_walk;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element value)
{
  Node_ptr previous_first = list->first;
  if (list->first == NULL)
  {
    list->first = create_node(value);
    list->last = list->first;
    list->length++;
    return Success;
  }
  list->first = create_node(value);
  list->first->next = previous_first;
  list->length++;
  return Success;
}

Status add_to_list(List_ptr list, Element value)
{
  Node_ptr previous_last = list->last;
  if (list->first == NULL)
  {
    return add_to_start(list, value);
  }
  list->last = create_node(value);
  previous_last->next = list->last;
  list->length++;
  return Success;
}

Status add_unique(List_ptr list, Element value, Matcher matcher)
{
  if (list->first == NULL)
  {
    return Failure;
  }
  int position = search(list, value, matcher);
  if (position == list->length)
  {
    return add_to_list(list, value);
  }
  return Failure;
}

Element remove_at(List_ptr list, int position)
{
  if (list->length <= position || position < 0)
  {
    return NULL;
  }

  if (position == 0)
  {
    return remove_from_start(list);
  }

  if (list->length - 1 == position)
  {
    return remove_from_end(list);
  }

  int counter = 0;
  Node_ptr p_walk = list->first;
  Node_ptr temp_node = list->first;
  while (counter < position)
  {
    temp_node = p_walk;
    p_walk = p_walk->next;
    counter++;
  }
  temp_node->next = p_walk->next;
  list->length--;
  Element removed_element = p_walk->element;
  free(p_walk);
  return removed_element;
}

Element remove_from_start(List_ptr list)
{
  if (list->first == NULL)
  {
    return NULL;
  }
  
  Node_ptr previous_first = list->first;
  Element previous_first_element = list->first->element;
  list->first = list->first->next;
  list->length--;
  free(previous_first);
  return previous_first_element;
}

Element remove_from_end(List_ptr list)
{
  if (list->first == NULL)
  {
    return NULL;
  }
  
  if (list->length == 1)
  {
    return remove_from_start(list);
  }

  int counter = 0;
  Node_ptr p_walk = list->first;
  Node_ptr temp_node = list->first;
  list->length--;
  while (counter < list->length)
  {
    temp_node = p_walk;
    p_walk = p_walk->next;
    counter++;
  }
  list->last = temp_node;
  list->last->next = NULL;
  Element removed_element = p_walk->element;
  free(p_walk);
  return removed_element;
}

int search(List_ptr list, Element value, Matcher matcher)
{
  int position = 0;
  Node_ptr iterator = list->first;
  while (iterator != NULL)
  {
    if ((*matcher)(iterator->element, value))
    {
      return position;
    }
    position++;
    iterator = iterator->next;
  }
  return position;
}

Element remove_first_occurrence(List_ptr list, Element value, Matcher matcher)
{
  if (list->first == NULL)
  {
    return NULL;
  }
  int position = search(list, value, matcher);
  return remove_at(list, position);
}

List_ptr remove_all_occurrences(List_ptr list, Element value, Matcher matcher)
{
  List_ptr removed_elemenet_list = create_list();

  int position = search(list, value, matcher);
  while (position < list->length)
  {
    Element element = remove_at(list, position);
    add_to_list(removed_elemenet_list, element);
    position = search(list, value, matcher);
  }
  
  return removed_elemenet_list;
}

void display(List_ptr list, Print print)
{
  Node_ptr iterator = list->first;
  while (iterator != NULL)
  {
    (*print)(iterator->element);
    iterator = iterator->next;
  }
  printf("\n");
}

Status clear_list(List_ptr list)
{
  if (list == NULL)
  {
    return Failure;
  }
  while (list->first != NULL)
  {
    remove_from_start(list);
  }
  return Success;
}

void destroy_list(List_ptr list)
{
  clear_list(list);
  free(list);
}

List_ptr map(List_ptr src, Mapper mapper)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = src->first;
  while (p_walk != NULL)
  {
    Element element = (*mapper)(p_walk->element);
    add_to_list(new_list, element);
    p_walk = p_walk->next;
  }
  return new_list;
}

List_ptr filter(List_ptr src, Predicate predicate)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = src->first;

  while(p_walk != NULL)
  {
    if ((*predicate)(p_walk->element))
    {
      add_to_list(new_list, p_walk->element);
    }
    p_walk = p_walk->next;
  }
  return new_list;
}

Element reduce(List_ptr src, Element init, Reducer reducer)
{
  Node_ptr p_walk = src->first;

  while(p_walk != NULL)
  {
    init = (*reducer)(p_walk->element, init);
    p_walk = p_walk->next;
  }
  return init;
}

void forEach(List_ptr src, ElementProcessor processor)
{
  Node_ptr p_walk = src->first;
  while (p_walk != NULL)
  {
    (*processor)(p_walk->element);
    p_walk = p_walk->next;
  }
}

List_ptr reverse(List_ptr src)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = src->first;

  while(p_walk != NULL)
  {
    add_to_start(new_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return new_list;
}