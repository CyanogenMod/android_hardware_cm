#ifndef _LIST_H_
#define _LIST_H_

#include "container.h"

struct list_node {
	struct list_node *next;
	struct list_node *prev;
};

struct list {
	struct list_node *head;
	struct list_node *tail;
};

#define LIST_INIT(name) { 0, 0 }

#define LIST(name) \
	struct list name = LIST_INIT(name)

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

static inline void list_init(struct list *list)
{
	list->head = 0;
	list->tail = 0;
}

static inline void list_append(struct list *list, struct list_node *item)
{
	item->next = 0;
	item->prev = list->tail;
	if (list->tail != 0)
		list->tail->next = item;
	else
		list->head = item;
	list->tail = item;
}

static inline void list_prepend(struct list *list, struct list_node *item)
{
	item->prev = 0;
	item->next = list->head;
	if (list->head == 0)
		list->tail = item;
	list->head = item;
}

static inline void list_insert(struct list *list, struct list_node *after, struct list_node *item)
{
	if (after == 0) {
		list_prepend(list, item);
		return;
	}
	item->prev = after;
	item->next = after->next;
	after->next = item;
	if (item->next)
		item->next->prev = item;
	if (list->tail == after)
		list->tail = item;
}

static inline void list_remove(struct list *list, struct list_node *item)
{
	if (item->next)
		item->next->prev = item->prev;
	if (list->head == item) {
		list->head = item->next;
		if (list->head == 0)
			list->tail = 0;
	} else {
		item->prev->next = item->next;
		if (list->tail == item)
			list->tail = item->prev;
	}
	item->prev = item->next = 0;
}

static inline struct list_node *list_pop(struct list *list)
{
	struct list_node *item;
	item = list->head;
	if (item == 0)
		return 0;
	list_remove(list, item);
	return item;
}

static inline struct list_node *list_last(struct list *list)
{
	return list->tail;
}

static inline struct list_node *list_first(struct list *list)
{
	return list->head;
}

#define list_push list_append

#define for_list_node(_list, _iter) \
  for (_iter = (_list)->head; (_iter) != 0; _iter = (_iter)->next)

#define for_list_node_after(_node, _iter) \
  for (_iter = (_node)->next; (_iter) != 0; _iter = (_iter)->next)

#define for_list_node_safe(_list, _iter, _bkup) \
  for (_iter = (_list)->head; (_iter) != 0 && ((_bkup = (_iter)->next) || 1); _iter = (_bkup))

#define for_list_node_safe_after(_node, _iter, _bkup) \
  for (_iter = (_node)->next; (_iter) != 0 && ((_bkup = (_iter)->next) || 1); _iter = (_bkup))

#endif
