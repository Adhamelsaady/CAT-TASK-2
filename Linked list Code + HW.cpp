#include <iostream>
using namespace std;
struct Node {
	int data { };
	Node* next{ };
	Node(int data) :data(data) { }
};
class LinkedList {
private:
	Node* head{};
	Node* tail{};
	int length = 0;
public:
	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << '\n';
	}
	
	void insert_end(int val){
		Node* item = new Node(val);
		if (!head)
			head = tail = item;
		else {
			tail->next = item;
			tail = item;
		}
		length++;
	}

	Node* get_nth(int key) {
		int idx = 1;
		for (Node* cur = head; cur; cur = cur->next) {
			if (idx == key)
				return cur;
			else
				idx++;
		}
		return nullptr;
	}

	int search(int value) {
		int idx = 1;
		for (Node* cur = head; cur ;cur = cur->next) {
			if (cur->data == value)
				return idx;
			idx++;
		}
		return -1;
	}

	int improved_search(int value) {
		int idx = 1;
		Node* prev = nullptr;
		for (Node* cur = head; cur; cur = cur->next) {
			if (cur->data == value) {
				if (!idx)
					return idx;
				else {
					swap(prev->data, cur->data);
					return idx - 1;
				}
			}
			else {
				idx++, prev = cur;
			}
		}
		return -1;
	}

	// HW 1 (easy) (Build distructor) 
	~LinkedList() {		// O(n) time - O(1) memory
		while (head) {
			Node* cur = head->next;
			delete head;
			head = cur;
		}
	}

	// HW 2 (easy) (Insert Front) 
	void insert_front(int data) { // O(1) Time && O(1) Memory 
		Node* item = new Node(data);
		if (!head)
			head = tail = item;
		else {
			item->next = head;
			head = item;
		}
		length++;
	}

	// HW 3 (easy)(Delete Front)
	void delete_front() {
		Node* temp = head->next;
		delete head;
		head = temp;
		length--;
		if (length <= 1)
			head = tail;
	}

	// HW 4 (easy)(get_nth_from_the_back)
	Node* get_nth_from_the_back(int n) {
		int idx = length;
		for (Node* cur = head; cur; cur = cur->next) {
			if (idx == n)
				return cur;
			else
				idx--;
		}
		return nullptr;
	}

	// HW 5 (easy)(is_the_same_list) [Using Length]
	bool is_the_same_list(LinkedList &list1) {
		// O(N) Time and memory
		if (list1.length != length)
			return false;
		Node* temp = list1.head;
		for (Node* cur = head; cur; cur = cur->next) {
			if (cur->data != temp->data)
				return false;
			temp = temp->next;
		}
		return true;
	}

	// HW 5 (easy)(is_the_same_list) [Without Length]
	bool is_same_list_v2(LinkedList &list1) {
		Node* temp1 = list1.head, *temp2 = head;
		bool flag = false;
		while (temp1 && temp2) {
			if (temp1->data != temp2->data)
				return false;
			else {
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		return !temp1 && !temp2;
	}

	// HW 6 (easy-meduim)(Delete with key)
	void delete_with_key(int value){
		Node* prev = nullptr;
		for (Node* cur = head; cur; cur = cur->next) {
			if (cur->data == value) {
				if (head == cur) {
					Node* temp = head->next;
					delete head;
					head = temp;			
				}
				else {
					prev->next = cur->next;
					delete cur;
				}
				length--;
				return;
			}
			prev = cur;
		}
		return;
	}

	// HW 7 (easy-meduim)(Insert Sorted)
	void Insert_Sorted(int value) {
		Node* temp = new Node(value);
		if (!head)
			head = temp = tail;
		else if (temp->data < head->data) {
			temp->next = head;
			head = temp;
		}
		else {
			for (Node* cur = head; cur; cur = cur->next) {
				Node* nex = cur->next;
				if (nex->data > temp->data) {
					cur->next = temp;
					temp->next = nex;
					break;
				}
			}
		}
		length++;
	}

	// HW 8 (easy-meduim)(Reverse)
	void reverse() {		
		if (length <= 1)
			return;
		tail = head;
		Node* prev = head;
		head = head->next;
		while (head) {
			Node* nxt = head->next;
			head->next = prev;
			prev = head;
			head = nxt;
		}
		head = prev;
		tail->next = nullptr;
	}

	// HW 9 (meduim)(Reverse head&tail)
	void reverse_head_and_tail() {
		if (length <= 1)
			return;
		if (length == 2) {
			swap(head, tail);
		}
		Node* posthead = head->next;
		Node* prehead = nullptr;
		for (Node* cur = head; cur; cur = cur->next) {
			if (cur->next == tail)
				prehead = cur;
		}
		tail->next = posthead;
		prehead->next = head;
		head->next = nullptr;
		swap(head, tail);
	}

	// HW 10 (meduim)(max recurcive)
	int max_recurcive(Node* node = nullptr,bool flag = true) {
		if (flag)
			return max_recurcive(this->head, false);
		if(!node)
			return INT_MIN;
		return max(max_recurcive(node->next,0), node->data);
	}
};
int main()
{
	LinkedList list;
	list.insert_end(1);
	list.insert_end(14);
	list.insert_end(15); 
	list.insert_end(5);
	list.insert_end(2);
	list.insert_front(11);
	list.delete_front();
	list.print();
	list.reverse_head_and_tail();
	cout << list.max_recurcive() << '\n';
	list.print();
}

