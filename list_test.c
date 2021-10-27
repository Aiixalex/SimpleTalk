#include "list.h"
#include <stdio.h>
#include <assert.h>

void print_list_int_items(List* pList) {
    if(pList->size == 0) {
        printf("Empty List.\n");
        return;
    }

    Node* pNode = pList->head;
    while(pNode != NULL) {
        printf("%d ", *(int*)(pNode->item));
        pNode = pNode->next;
    }
    printf("\n");
}

void insert_after_and_print(List* pList, void* pItem) {
    int flag = List_insert_after(pList, pItem);
    assert(flag == 0 || flag == -1);

    if(flag == 0) {
        printf("List_insert_after success.\n");
    } else if(flag == -1) {
        printf("List_insert_after fail.\n");
    }
}

void insert_before_and_print(List* pList, void* pItem) {
    int flag = List_insert_before(pList, pItem);
    assert(flag == 0 || flag == -1);

    if(flag == 0) {
        printf("List_insert_before success.\n");
    } else if(flag == -1) {
        printf("List_insert_before fail.\n");
    }
}

void append_and_print(List* pList, void* pItem) {
    int flag = List_append(pList, pItem);
    assert(flag == 0 || flag == -1);

    if(flag == 0) {
        printf("List_append success.\n");
    } else if(flag == -1) {
        printf("List_append fail.\n");
    }
}

void prepend_and_print(List* pList, void* pItem) {
    int flag = List_prepend(pList, pItem);
    assert(flag == 0 || flag == -1);

    if(flag == 0) {
        printf("List_prepend success.\n");
    } else if(flag == -1) {
        printf("List_prepend fail.\n");
    }
}

void remove_and_print(List* pList) {
    int* pItem = (int*)(List_remove(pList));
    printf("Remove int %d\n", *pItem);
}

void trim_and_print(List* pList) {
    int* pItem = (int*)(List_trim(pList));
    printf("Trim int %d\n", *pItem);
}

bool match(void* pItem, void* pComparisonArg) {
    int a = *(int*)pItem;
    int b = *(int*)pComparisonArg;
    if(a == b) return true;
    else return false;
}

int main() {
    List* l = List_create();

    assert(l->size == 0);
    assert(l->curr == NULL);
    assert(l->head == NULL);
    assert(l->tail == NULL);
    assert(l->oob == LIST_NOT_OOB);
    print_list_int_items(l);

    int i1 = 10;
    int* pItem_1 = &i1;
    insert_after_and_print(l, pItem_1);
    print_list_int_items(l);
    assert(l->size == 1);
    assert(*(int*)(l->curr->item) == 10);
    assert(l->head == l->tail);
    assert(l->oob == LIST_NOT_OOB);

    int i2 = 100;
    int* pItem_2 = &i2;
    insert_after_and_print(l, pItem_2);
    print_list_int_items(l);
    assert(l->size == 2);
    assert(*(int*)(l->curr->item) == 100);
    assert(*(int*)(l->curr->prev->item) == 10);
    assert(l->oob == LIST_NOT_OOB);

    int i3 = 50;
    int* pItem_3 = &i3;
    insert_before_and_print(l, pItem_3);
    print_list_int_items(l);
    assert(l->size == 3);
    assert(*(int*)(l->curr->item) == 50);
    assert(l->oob == LIST_NOT_OOB);

    l->curr = NULL;
    l->oob = LIST_OOB_START;
    int i4 = 5;
    int* pItem_4 = &i4;
    insert_before_and_print(l, pItem_4);
    print_list_int_items(l);
    assert(l->size == 4);
    assert(*(int*)(l->curr->item) == 5);
    assert(l->oob == LIST_NOT_OOB);

    l->curr = NULL;
    l->oob = LIST_OOB_END;
    int i5 = 500;
    int* pItem_5 = &i5;
    insert_before_and_print(l, pItem_5);
    print_list_int_items(l);
    assert(l->size == 5);
    assert(*(int*)(l->curr->item) == 500);
    assert(l->oob == LIST_NOT_OOB);

    int i6 = 1000;
    int* pItem_6 = &i6;
    append_and_print(l, pItem_6);
    print_list_int_items(l);
    assert(l->size == 6);
    assert(*(int*)(l->curr->item) == 1000);
    assert(l->oob == LIST_NOT_OOB);

    int i7 = -5;
    int* pItem_7 = &i7;
    prepend_and_print(l, pItem_7);
    print_list_int_items(l);
    assert(l->size == 7);
    assert(*(int*)(l->curr->item) == -5);
    assert(*(int*)(l->head->item) == -5);
    assert(*(int*)(l->head->next->item) == 5);
    assert(*(int*)(l->head->next->next->item) == 10);
    assert(*(int*)(l->tail->item) == 1000);
    assert(l->oob == LIST_NOT_OOB);

    l->curr = l->curr->next;
    assert(*(int*)(l->curr->item) == 5);
    print_list_int_items(l);
    l->curr = l->curr->next;
    assert(*(int*)(l->curr->item) == 10);
    remove_and_print(l);
    print_list_int_items(l);
    assert(l->size == 6);
    assert(*(int*)(l->curr->item) == 50);
    assert(l->oob == LIST_NOT_OOB);

    trim_and_print(l);
    print_list_int_items(l);
    assert(l->size == 5);
    assert(*(int*)(l->curr->item) == 500);
    assert(l->oob == LIST_NOT_OOB);

    List* l2 = List_create();
    int i8 = 1030;
    int* pItem_8 = &i8;
    insert_before_and_print(l2, pItem_8);
    List_concat(l, l2);
    print_list_int_items(l);

    assert(List_search(l, &match, pItem_8) == l->tail);
    int i9 = 1050;
    int* pItem_9 = &i9;
    assert(List_search(l, &match, pItem_9) == NULL);
}