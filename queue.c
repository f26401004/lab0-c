/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* return null if malloc failed */
    if (q == NULL) {
        return NULL;
    }
    /* reset the queue */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* just return if queue do not exist */
    if (q == NULL) {
        return;
    }
    /* use two pointer to traversal all the queue entry */
    list_ele_t *iter = q->head;
    list_ele_t *prev = iter;
    q->head = NULL;
    q->tail = NULL;
    while (iter) {
        prev = iter;
        iter = iter->next;
        prev->next = NULL;
        free(prev->value);
        free(prev);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* return false if queue do not exist */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* return false if malloc a new entry failed */
    if (newh == NULL) {
        return false;
    }
    char *buf = malloc((strlen(s) + 1) * sizeof(char));
    /* return false if malloc a new buffer to copy the string failed */
    if (buf == NULL) {
        /* [Important]: also need to free the newh entry */
        free(newh);
        return false;
    }
    q->size++;
    strcpy(buf, s);
    /* reset the newh entry */
    newh->value = buf;
    newh->next = NULL;
    /* insert the new entry to the queue head */
    if (q->head == NULL && q->tail == NULL) {
        q->head = q->tail = newh;
        return true;
    }
    newh->next = q->head;
    q->head = newh;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* return false if queue do not exist */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* return false if malloc a new entry failed */
    if (newh == NULL) {
        return false;
    }
    char *buf = malloc((strlen(s) + 1) * sizeof(char));
    /* return false if malloc a new buffer to copy the string failed */
    if (buf == NULL) {
        /* [Important]: also need to free the newh entry */
        free(newh);
        return false;
    }
    q->size++;
    strcpy(buf, s);
    /* reset the newh entry */
    newh->value = buf;
    newh->next = NULL;
    /* insert the new entry to the queue head */
    if (q->head == NULL && q->tail == NULL) {
        q->head = q->tail = newh;
        return true;
    }
    q->tail->next = newh;
    q->tail = newh;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* if queue do not exist or q->head do not exist or q->size equal to zero,
     * then just return false */
    if (q == NULL || q->head == NULL || q->size == 0) {
        return false;
    }
    /* minus the queue size first */
    q->size--;
    list_ele_t *iter = q->head;
    if (sp != NULL) {
        /* reset sp first */
        memset(sp, '\0', (int) sizeof(sp));
        memcpy(sp, iter->value, bufsize);
        // or : strncpy(sp, iter->value, bufsize - 1);
        /* [Important]: truncated the rest length of the sp */
        sp[bufsize - 1] = '\0';
    }
    q->head = q->head->next;
    /* free the memory space */
    iter->next = NULL;
    free(iter->value);
    free(iter);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* if queue do not exist or q->head do not exist or q->size equal to zero,
     * then just return zero */
    if (q == NULL || q->size == 0 || q->head == NULL) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* if queue do not exist or q->head do not exist or q->size equal to zero,
     * then just return */
    if (q == NULL || q->size == 0 || q->head == NULL) {
        return;
    }
    list_ele_t *prev = NULL;     // use prev to store previous entry
    list_ele_t *next = q->head;  // use next to store next entry
    list_ele_t *current =
        q->head;  // use current entry to reverse the next link
    /* traversal through the list and reverse the entry next pointer link */
    while (current) {
        next = next->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    /* [Important]: also need to reset the head and tail pointer link */
    q->tail = q->head;
    q->head = prev;
}
