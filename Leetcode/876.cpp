/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int count = 1;
        ListNode* cur = head;

        while (cur != NULL) {
            cur = cur->next;
            count++;
        }

        int mid = (count % 2 == 0) ? (count/2) : (count/2 + 1);

        cur = head;
        for (int i = 1; i < mid; i++) {
            cur = cur->next;
        }
        return cur;
    }
};
