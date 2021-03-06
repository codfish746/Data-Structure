// First-reverse-nodes-in-k-group.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

// definition for singly-linked list.
 struct ListNode {
     int val;
	 ListNode *next;
	 ListNode(int x) : val(x), next(NULL) {}
};



 class Solution {
 public:
	 /*
	 * @param head: a ListNode
	 * @param k: An integer
	 * @return: a ListNode
	 */
	 ListNode * reverseKGroup(ListNode * head, int k) {
		 // write your code here
		 int m_iNodeCount = 0;
		 ListNode* t = head;
		 while (t) {
			 m_iNodeCount++;
			 t = t->next;
		 }
		 int time = m_iNodeCount / k;
		 ListNode* waitList, *mid, **workNode;

		 waitList = head;		//指向当前翻转的k链尾部
		 workNode = &head;	//保存当前头部的地址
		 mid = NULL;
		 for (int i = 0; i < time; i++)//反转time个组
		 {
			 for (int j = 1; j < k; j++)//每个组需要调整k-1次
			 {
				 mid = waitList->next;  //
				 waitList->next = waitList->next->next;
				 mid->next = *workNode;
				 *workNode = mid;  //把
			 }
			 workNode = &waitList->next;
			 waitList = waitList->next;//将

		 }
		 return head;
	 }

 };


int main()
{
	Solution s;
	ListNode* a = new ListNode(1);
	a->next= new ListNode(2);
	a->next->next= new ListNode(3);
	a->next->next->next= new ListNode(4);
	a->next->next->next->next= new ListNode(5);
	a=s.reverseKGroup(a, 2);
	while (a)
	{
		cout << a->val << endl;
		a = a->next;
	}
	system("pause");
    return 0;
}

