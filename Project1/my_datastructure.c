#include <stdio.h>

#pragma region list

struct ListNode {
	int val;
	struct ListNode* next;
};
struct myList
{
	struct ListNode* head;
};
//
void print_list(struct ListNode* head) {
	struct ListNode* pt = head;
	while (pt->next != NULL) {
		printf("%d -> ", pt->val);
		pt = pt->next;
	}
	printf("%d \n", pt->val);
}
// create 
struct ListNode* create_ListNode_from_array(int* nums, int len) {
	// len is not index
	if (len == 0) {
		return NULL;
	}
	else {
		struct ListNode* pt = (struct ListNode*)malloc(sizeof(struct ListNode));
		pt->val = *nums;
		struct ListNode* head = pt;
		len--;
		nums++;
		while (len > 0) {
			pt->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			pt = pt->next;
			pt->next = NULL;
			pt->val = *nums;
			len--;
			nums++;
		}
		return head;
	}
}
// operation
struct ListNode* link_reverse(struct ListNode* link) {
	if (link->next == NULL) {
		return link;
	}
	else {
		struct ListNode* node = link;
		struct ListNode* pre_node = node;
		while (node->next != NULL) {
			// find the last node of link
			pre_node = node;
			node = node->next;
		}
		pre_node->next = NULL;
		node->next = link_reverse(link);
		return node;
	}

}
// cycle list
int list_empty(struct myList* L) {
	if (L->head==NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
int list_insert(struct myList* L, struct ListNode* x) {
	if (list_empty(L)) {
		L->head = x;
		x->next = L->head;
	}
	struct ListNode* pt = L->head->next;
	while (pt->next != L->head) {
		pt = pt->next;
	}
	pt->next = x;
	x->next = L->head;
}
int list_delete(struct myList* L, struct ListNode* x) {
	if (list_empty(L)) {
		printf("error: trying to delete an empty list \n");
		return -1;
	}
	struct ListNode* pt = L->head;
	while (pt->next != x && pt->next != L->head) {//退出时 要么找到x，要么是最后一个node
		pt = pt->next;
	}
	if (pt->next == x ) {// 如果pt下一个节点是x，则删除
		if (pt->next == L->head) {
			L->head = L->head->next;// 如果要删除的是头节点，链表头节点必须要换
		}
		pt->next = x->next;
	}
	else{// 此时pt下一个节点是头节点，而且不是 x ，我们也遍历完了
		printf("warnning: did not find the node\n");
		return -1;
	}
}

struct ListNode* list_search(struct myList* L, int k) {
	if (list_empty(L)) {
		printf("error: trying to search an empty list \n");
		return -1;
	}
	struct ListNode* pt = L->head;
	while (pt->val != k && pt->next != L->head) {
		pt = pt->next;
	}
	if (pt->next==L->head && pt->val != k) {
		return NULL;//说明没找到
	}
	else {//如果不是最后一个
		return pt;
	}
}

#pragma endregion

#pragma region DoubleList
struct myDoubleListNode {
	int key;
	struct myDoubleListNode* prev;
	struct myDoubleListNode* next;
};
struct myDoubleList
{
	struct myDoubleListNode* head;
};
struct myDoubleListNode* doublelist_search(struct myDoubleList* DL,int k) {
	struct myDoubleListNode* x = DL->head;
	while (x!= NULL && x->key!=k) {
		x = x->next;
	}
	return x;
}

int doublelist_insert(struct myDoubleList* DL, struct myDoubleListNode* x) {
	x->next = DL->head;
	if (x->next != NULL) {
		DL->head->prev = x;
	}
	DL->head = x;
	x->prev = NULL;
}
int doublelist_delete(struct myDoubleList* DL, struct myDoubleListNode* x) {
	if (x->prev!=NULL) {
		x->prev->next = x->next;
	}
	else {
		DL->head = x->next;//如果删除的节点是头节点
	}
	if (x->next != NULL) {
		x->next->prev = x->prev;
	}
}
#pragma endregion



#pragma region heap

struct HeapArray {
	int len;
	int* array;
};
// heap
int heap_left(int i) { return 2 * i; }
int heap_right(int i) { return 2 * i + 1; }
int heap_parent(int i) { return i / 2; }
void exchange(int* array, int idx1, int idx2) {
	int temp = *(array + idx1);
	*(array + idx1) = *(array + idx2);
	*(array + idx2) = temp;
}
void max_heapify(struct HeapArray* array, int idx) {
	// 思路从1开始，索引数组时从零开始,idx也是从1开始
	int r = heap_right(idx);
	int l = heap_left(idx);
	int largest_idx = idx;
	if (r <= array->len && *(array->array + r - 1) > * (array->array + idx - 1)) {
		largest_idx = r;
	}
	if (l <= array->len && *(array->array + l - 1) > * (array->array + largest_idx - 1)) {
		largest_idx = l;
	}
	if (largest_idx != idx) {
		exchange(array->array, idx - 1, largest_idx - 1);
		max_heapify(array, largest_idx);
	}
}
void max_heapify_loop(struct HeapArray* array,  int idx) {
	// 下面的思路从1开始，索引数组时从零开始,传入参数idx从1开始
	int largest_idx = idx;
	while (heap_left(idx) <= array->len) {//while不是叶子节点
		int r = heap_right(idx);
		int l = heap_left(idx);
		if (r <= array->len && *(array->array + r - 1) > * (array->array + idx - 1)) {
			largest_idx = r;
		}
		if (l <= array->len && *(array->array + l - 1) > * (array->array + largest_idx - 1)) {
			largest_idx = l;
		}
		if (largest_idx != idx) {
			exchange(array->array, idx - 1, largest_idx - 1);
			idx = largest_idx;
		}
		else {
			break;// 程序结束并返回
		}
	}

}
void build_max_heap(struct HeapArray* array) {
	int i = array->len / 2;
	for (i = array->len / 2;i > 0;i--) {
		max_heapify_loop(array, i);
	}
}
int* max_heap_sort(struct HeapArray* array) {
	// small to big
	int temp = array->len;
	build_max_heap(array);
	int i = 0;
	for (i = array->len - 1;i >= 0;i--) {
		exchange(array->array, 0, i);
		array->len -= 1;
		max_heapify_loop(array, 1);//长度减一
	}
	return array->array;
}
int heap_extract_max(struct HeapArray* array) {
	int max = *(array->array+0);
	*(array->array + 0) = *(array->array + array->len - 1);
	array->len -= 1;
	max_heapify_loop(array, 1);
	return max;
}
void heap_increase_key(struct HeapArray* array, int idx, int key) {
	// idx 从1开始
	if (array->array[idx - 1] > key) {
		printf("key too small\n");
	}
	array->array[idx - 1] = key;
	while (idx > 0 && array->array[heap_parent(idx) - 1] < key) {
		array->array[idx - 1] = array->array[heap_parent(idx) - 1];
		idx = heap_parent(idx);
	}
	array->array[idx - 1] = key;
}
void max_heap_insert(struct HeapArray* array, int key) {
	array->len += 1;
	array->array[array->len - 1] = -65535;
	heap_increase_key(array, array->len, key);
}
void max_heap_delete(struct HeapArray* array, int idx) {
	// idx 从1开始
	exchange(array->array,idx-1,array->len-1);
	array->len -= 1;
	int key = array->array[idx - 1];
	if (idx==1 || array->array[heap_parent(idx) - 1] >key) {
		max_heapify_loop(array, idx);
	}
	else {
		while (idx > 0 && array->array[heap_parent(idx) - 1] < key) {
			array->array[idx - 1] = array->array[heap_parent(idx) - 1];
			idx = heap_parent(idx);
		}
		array->array[idx - 1] = key;
	}
	
	
}


void min_heapify(struct HeapArray* array, int idx) {
	// 思路从1开始，索引数组时从零开始,idx也是从1开始
	int r = heap_right(idx);
	int l = heap_left(idx);
	int smallest_idx = idx;
	if (r <= array->len && *(array->array + r - 1) < * (array->array + idx - 1)) {
		smallest_idx = r;
	}
	if (l <= array->len && *(array->array + l - 1) < * (array->array + smallest_idx - 1)) {
		smallest_idx = l;
	}
	if (smallest_idx != idx) {
		exchange(array->array, idx - 1, smallest_idx - 1);
		min_heapify(array, smallest_idx);
	}
}
void build_min_heap(struct HeapArray* array) {
	int i = array->len / 2;
	for (i = array->len / 2;i > 0;i--) {
		min_heapify(array, i);
	}
}
int* min_heap_sort(struct HeapArray* array) {
	// big to small
	int temp = array->len;
	build_min_heap(array);
	int i = 0;
	for (i = array->len - 1;i >= 0;i--) {
		exchange(array->array, 0, i);
		array->len -= 1;
		min_heapify(array, 1);//长度减一
	}
	return array->array;
}
int heap_extract_min(struct HeapArray* array) {
	int min = *(array->array + 0);
	*(array->array + 0) = *(array->array + array->len - 1);
	array->len -= 1;
	min_heapify(array, 1);
	return min;
}
void heap_decrease_key(struct HeapArray* array, int idx, int key) {
	// idx 从1开始
	if (array->array[idx - 1] < key) {
		printf("key too big\n");
	}
	array->array[idx - 1] = key;
	while (idx > 0 && array->array[heap_parent(idx) - 1] > key) {
		array->array[idx - 1] = array->array[heap_parent(idx) - 1];
		idx = heap_parent(idx);
	}
	array->array[idx - 1] = key;
}
void min_heap_insert(struct HeapArray* array, int key) {
	array->len += 1;
	array->array[array->len - 1] = 65535;
	heap_decrease_key(array, array->len, key);
}
void min_heap_delete(struct HeapArray* array, int idx) {
	// idx 从1开始
	exchange(array->array, idx - 1, array->len - 1);
	array->len -= 1;
	int key = array->array[idx - 1];
	if (idx == 1 || array->array[heap_parent(idx) - 1] < key) {
		min_heapify(array, idx);
	}
	else {
		while (idx > 0 && array->array[heap_parent(idx) - 1] > key) {
			array->array[idx - 1] = array->array[heap_parent(idx) - 1];
			idx = heap_parent(idx);
		}
		array->array[idx - 1] = key;
	}


}

#pragma endregion

#pragma region stack
struct myStack {
	int top ;
	int* array;
};
int stack_empty(struct myStack* S) {
	if (S->top == 0) { return 1; }
	else {
		return 0;
	}
}
int push(struct myStack* S, int x) {
	S->top += 1;
	S->array[S->top] = x;
}
int pop(struct myStack* S) {
	if (S->top == 0) { 
		printf("error: under flow \n"); 
		return -1;
	}
	else {
		S->top -= 1;
		return S->array[S->top+1];
	}
}


#pragma endregion

#pragma region queue
struct myQueue {
	int top;
	int tail;
	int length;
	int* array;
};
int queue_empty(struct myQueue* Q) {
	if (Q->top == Q->tail) {
		return 1;
	}
	else {
		return 0;
	}
}
int queue_full(struct myQueue* Q) {
	if ((Q->tail > Q->top && Q->tail == Q->length) || (Q->top - Q->tail) == 1) {
		return 1;
	}
	else {
		return 0;
	}
}
int enqueue(struct myQueue* Q,int x) {
	if (queue_full(Q)) {
		printf("error: queue full \n");
		return -1;
	}
	Q->array[Q->tail] = x;
	if (Q->tail==Q->length) {
		Q->tail = 0;
	}
	else {
		Q->tail += 1;
	}
}
int dequeue(struct myQueue* Q) {
	if (queue_empty(Q)) {
		printf("error: queue empty \n");
		return -1;
	}
	int x = Q->array[Q->top];
	if (Q->top== Q->length) {
		Q->top = 0;
	}
	else {
		Q->top += 1;
	}
	return x;
}

#pragma endregion

#pragma region deque
struct myDeque {
	int top;
	int tail;
	int length;
	int* array;
};
// 满、空 deque的情况同queue
int head_enqueue(struct myDeque* D,int x) {
	if (queue_full(D) == 1) {//调用qeque的函数这里可能需要类型转化
		printf("error: queue full \n");
		return -1;
	}
	if (D->top == 0) {
		D->top = D->length;
		D->array[D->top] = x;
	}
	else {
		D->top -= 1;
		D->array[D->top] = x;
	}
}
int tail_enqueue(struct myDeque* D, int x) {
	if (queue_full(D) == 1) {//调用qeque的函数这里可能需要类型转化
		printf("error: queue full \n");
		return -1;
	}
	if (D->tail == D->length) {
		D->tail = 0;
		D->array[D->tail] = x;
	}
	else {
		D->tail += 1;
		D->array[D->tail] = x;
	}
}
int top_dequque(struct myDeque* D) {
	if (queue_empty(D) == 1) {//调用qeque的函数这里可能需要类型转化
		printf("error: queue empty \n");
		return -1;
	}
	if (D->top == D->length) {
		D->top = 0;
	}
	else {
		D->top += 1;
	}
}
int tail_dequque(struct myDeque* D) {
	if (queue_empty(D) == 1) {//调用qeque的函数这里可能需要类型转化
		printf("error: queue empty \n");
		return -1;
	}
	if (D->tail == 0) {
		D->tail = D->length;
	}
	else {
		D->tail -= 1;
	}
}
#pragma endregion



