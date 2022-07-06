#pragma once
#include <string>
#include <iostream>
#include <vector>


struct ListNode
{
	ListNode* prev;
	ListNode* next;
	ListNode* rand;
	std::string data;
};

class List
{
public:
	List();
	void Serialize(FILE* file) const;
	void Deserialize(FILE* file);
	void push_back(std::string str);
	void set_rand(unsigned int from, unsigned int to);
	void show() const;
	void deletelist();
	~List();

private:
	ListNode* head;
	ListNode* tail;
	int count;
	std::vector<int> rand_data;
	std::vector<ListNode*> node_ptrs;
};