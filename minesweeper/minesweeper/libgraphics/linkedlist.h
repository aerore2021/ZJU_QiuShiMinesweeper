/*
 * File: LinkedList.h
 * -------------
 * This file provides an interface to a simple linked list abstraction.             这个文件提供了一个简单的链表抽象的接口。
 *                                                                                  意思就是我们做链表操作不用像pta里那么麻烦了。    
 *typedef struct linkedlistCDT *linkedlistADT;                                              
 *
 *linkedlistADT NewLinkedList(void);
 *void FreeLinkedList(linkedlistADT linkedlist);
 *linkedlistADT SearchNode(linkedlistADT linkedlist, void *obj,
 *                         bool (*equalfunptr)(void *obj1, void *obj2));
 *void InsertNode(linkedlistADT linkedlist, linkedlistADT nodeptr, void *obj);
 *linkedlistADT DeleteNode(linkedlistADT linkedlist, void *obj,
 *                         bool (*equalfunptr)(void *obj1, void *obj2));
 *void TraverseLinkedList(linkedlistADT linkedlist,
 *                        void (*traversefunptr)(void *obj));
 *void *ithNodeobj(linkedlistADT head, int index);
 *linkedlistADT NextNode(linkedlistADT head, linkedlistADT nodeptr);
 *void *NodeObj(linkedlistADT head, linkedlistADT nodeptr);
 */

#ifndef _LinkedList_h
#define _LinkedList_h

#include "boolean.h"

/*
 * Type: linkedlistADT                                                              类型：linkedlistADT
 * --------------                                                                   --------------
 * This line defines the abstract linked list type as a pointer to                  这一行将抽象链表类型定义为指向其具体对应物的指针。
 * its concrete counterpart.  Clients have no access to the                         客户无权访问基础表示。
 * underlying representation.                                                      
 */

typedef struct linkedlistCDT *linkedlistADT;

/*
 * Function: NewLinkedList                                                          函数：NewLinkedList
 * Usage: linkedlist = NewLinkedList();                                             使用：linkedlist = NewLinkedList();
 * --------------------------                                                       --------------------------
 * This function allocates and returns an empty linked list (including a head       该函数分配并返回一个空链表（仅包括一个头节点）。
 * node only).
 */

linkedlistADT NewLinkedList(void);

/*
 * Function: FreeLinkedList                                                         函数：FreeLinkedList
 * Usage: FreeLinkedList(linkedlist);                                               使用：FreeLinkedList(linkedlist);
 * ------------------------                                                         ------------------------
 * This function frees the storage associated with linked list.                     此函数释放与链表关联的存储空间。
 */

void FreeLinkedList(linkedlistADT linkedlist);

/*
 * Function: SearchNode                                                             函数：SearchNode
 * Usage: nodeptr = SerachNode(linkedlist, obj, equalfunptr);                       使用：nodeptr = SerachNode(linkedlist, obj, equalfunptr);
 * ---------------------------                                                      ---------------------------
 * This function searches the obj in the linked list, return the node pointer if    该函数在链表中查找目标，如果找到则返回节点指针，否则返回NULL。    
 * find out the obj, renturn NULL otherwise.
 */

linkedlistADT SearchNode(linkedlistADT linkedlist, void *obj, bool (*equalfunptr)(void *obj1, void *obj2));

/*
 * Function: InsertNode                                                             函数：InsertNode
 * Usage: InsertNode(linkedlist, nodeptr, obj);                                     使用：InsertNode(linkedlist, nodeptr, obj);
 * ----------------------------                                                     ----------------------------
 * This function ineserts the data value after the nodeptr node of the linked       该函数在链表的nodeptr节点之后插入数据值。
 * list. if nodeptr is NULL, append the obj to the tail of the linked list.         如果 nodeptr 为 NULL，则将 obj 附加到链表的尾部。
 *
 * return the node inserted                                                         返回插入的节点
 */

linkedlistADT InsertNode(linkedlistADT linkedlist, linkedlistADT nodeptr, int obj);

/*
 * Function: DeleteNode                                                             函数：DeleteNode
 * Usage: nodeptr = DeleteNode(linkedlist, obj, equalfunptr);                       使用：nodeptr = DeleteNode(linkedlist, obj, equalfunptr);
 * ------------------------------                                                   ------------------------------
 * This function deletes the node with the data obj of the linked list. it returns  该函数删除链表数据为obj的节点。
 * the pointer of the node if found, NULL otherwise.                                如果找到它返回节点的指针，否则返回NULL。
 */

linkedlistADT DeleteNode(linkedlistADT linkedlist, void *obj,
                         bool (*equalfunptr)(void *obj1, void *obj2));

/*
 * Function: TraverseList                                                           函数：TraverseList （traverse--遍历）
 * Usage: TraverseList(linkedlist, void (*traversefunptr)(void *obj));              使用：TraverseList(linkedlist, void (*traversefunptr)(void *obj));
 * ------------------------------                                                   ------------------------------
 * This function traverses the linked list, and process the node value obj using    该函数遍历链表，并使用funptr指向的函数处理节点值obj。
 * the function which funptr points to.
 */

void TraverseLinkedList(linkedlistADT linkedlist, void (*traversefunptr)(void *obj));

/*
 * Function: ithNode                                                                函数：ithNode
 * Usage: obj = ithNode(linkedlist, index);                                         使用：obj = ithNode(linkedlist, index);    
 * ------------------------------                                                   ------------------------------        
 * This function return the pointer of the index-th node of the linked list.        该函数返回链表第 index 个节点的指针。
 */

void *ithNodeobj(linkedlistADT head, int index);

/*
 * Function: NextNode                                                               函数：NextNode
 * Usage: nextnodeptr = NextNode(linkedlist, nodeptr);                              使用：nextnodeptr = NextNode(linkedlist, nodeptr);
 * ------------------------------                                                   ------------------------------
 * This function return the pointer of the next node of the node nodeptr.           该函数返回节点nodeptr的下一个节点的指针。
 */

linkedlistADT NextNode(linkedlistADT head, linkedlistADT nodeptr);

/*
 * Function: NodeObj                                                                函数：NodeObj
 * Usage: obj = NodeObj(linkedlist, nodeptr);                                       使用：obj = NodeObj(linkedlist, nodeptr);
 * ------------------------------                                                   ------------------------------
 * This function return the dataptr of the node nodeptr points to.                  该函数返回 nodeptr 指向的节点的 dataptr。
 */

void *NodeObj(linkedlistADT head, linkedlistADT nodeptr);

/*
 * Type: linkedlistCDT                                                              类型：linkedlistCDT
 * --------------                                                                   --------------
 * This type provides the concrete counterpart to the linkedlistADT.                这种类型提供了链表ADT 的具体对应物。
 */

struct linkedlistCDT {
    int dataptr;
    struct linkedlistCDT *next;
};  

#endif
