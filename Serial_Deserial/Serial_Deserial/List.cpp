#include "List.h"


List::List() : head(nullptr), tail(nullptr), count(0)
{}

void List::Serialize(FILE* file) const
{
	if (file)
	{
		ListNode* temp = tail;
		fwrite(&count, sizeof(count), 1, file);
		for (int i = 0; i < count; i++)
		{
			const char* data = temp->data.c_str();
			int len = temp->data.length();
			fwrite(&len, sizeof(len), 1, file);
			fwrite(data, sizeof(char), len, file);
			if (temp->next) temp = temp->next;
			fwrite(&rand_data[i], sizeof(int), 1, file);
		}
	}
}

void List::Deserialize(FILE* file)
{
	if (file)
	{
		deletelist();
		int size;
		fread(&size, sizeof(size), 1, file);
		node_ptrs.resize(size, 0);
		for (int i = 0; i < size; i++)
		{
			int len;
			fread(&len, sizeof(len), 1, file);
			char* data = new char[len + 1];
			fread(data, sizeof(char), len, file);
			data[len] = '\0';
			push_back(data);
			delete[] data;
			node_ptrs[i] = head;
			fread(&rand_data[i], sizeof(int), 1, file);
		}

		for (int i = 0; i < size; i++) set_rand(i + 1, rand_data[i]);
	}
}

void List::push_back(std::string str)
{
	if (head == nullptr)
	{
		head = tail = new ListNode;
		head->data = str;
		head->next = head->prev = head->rand = nullptr;
		count++;
		rand_data.resize(count, 0);
		node_ptrs.push_back(head);
	}
	else
	{
		ListNode* temp = head;
		head->next = new ListNode;
		head = head->next;
		head->data = str;
		head->next = head->rand = nullptr;
		head->prev = temp;
		count++;
		rand_data.resize(count, 0);
		node_ptrs.push_back(head);
	}
}

void List::set_rand(unsigned int from, unsigned int to)
{
	if (count && from <= count && to <= count && from > 0 && to > 0)
	{
		rand_data[from - 1] = to;
		node_ptrs[from - 1]->rand = node_ptrs[to - 1];
	}
}

void List::show() const
{
	if (head)
	{
		ListNode* temp = tail;
		for (int i = 0; i < count; i++)
		{
			if (temp->rand)
			{
				std::cout << temp->data << " -> " << temp->rand->data << '\n';
				if (temp->next) temp = temp->next;
			}
			else
			{
				std::cout << temp->data << " -> 0" << '\n';
				if (temp->next) temp = temp->next;
			}
		}
		std::cout << '\n';
	}
}

void List::deletelist()
{
	if (count)
	{
		ListNode* temp = tail;
		for (int i = 0; i < count; i++)
		{
			if (temp->next)
			{
				tail = tail->next;
				delete temp;
				temp = tail;
			}
			else
			{
				delete temp;
				break;
			}
		}
		tail = head = nullptr;
		count = 0;
		node_ptrs.resize(0);
		node_ptrs.clear();
		rand_data.resize(0);
		rand_data.clear();
	}
}

List::~List()
{
	deletelist();
}