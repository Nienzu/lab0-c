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
    /* What if malloc returned NULL? */
    if (q == NULL) {
        printf("No more memory for queue\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    } else if (q->head == NULL) {
        free(q);
        return;
    }
    list_ele_t *tmp;
    while (q->head != NULL) {
        tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
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
    list_ele_t *newh;
    if (q == NULL) {
        return false;
    }
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        printf("malloc return NULL when allocate new head\n");
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    newh->value = malloc(strlen(s) * sizeof(char) + 1);

    if (newh->value == NULL) {
        printf("malloc return NULL when allocate new value\n");
        free(newh);
        return false;
    }

    strcpy(newh->value, s);

    /* Assign tail */
    if (q->head == NULL) {
        newh->next = NULL;
        q->head = newh;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    if (q->tail == NULL) {
        q->tail = q->head;
    }
    q->size++;
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
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        printf("malloc return NULL when allocate new head\n");
        return false;
    }
    newt->value = malloc(strlen(s) * sizeof(char) + 1);
    if (newt->value == NULL) {
        printf("malloc return NULL when allocate new value \n");
        free(newt);
        return false;
    }
    strcpy(newt->value, s);
    newt->next = NULL;

    if (q->tail != NULL) {
        q->tail->next = newt;
        q->tail = newt;
    } else {
        q->tail = newt;
        q->head = newt;
    }
    q->size++;
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
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL) {
        return false;
    }
    if (sp != NULL) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    list_ele_t *tmp = q->head;
    if (q->head->next == NULL) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    q->size--;
    free(tmp->value);
    free(tmp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL) {
        return 0;
    } else {
        return q->size;
    }
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
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) {
        return;
    }
    list_ele_t *tmp = NULL;
    list_ele_t *newh = NULL;
    q->tail = q->head;
    while (q->head != NULL) {
        if (tmp == NULL) {
            tmp = q->head;
            q->head = q->head->next;
            tmp->next = NULL;
            newh = tmp;
        } else {
            tmp = q->head;
            q->head = q->head->next;
            tmp->next = newh;
            newh = tmp;
        }
    }
    q->head = newh;
}
