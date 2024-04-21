#pragma once


template<typename T>
class LinkedList
{
public:
	LinkedList() : head_(nullptr), size_(0) {}

public:
	// Main functions for task
	void add(T val);
	void remove(T val);
	bool contains(int val);

	// Additional functions
	void add(int pos, T val);
	void add_forward(T val);
	void remove_first();
	void remove_last();

	void print();
	void clear();
	int size();

private:
	template<typename U>
	struct Node
	{
		Node() : next(nullptr) {}
		Node(U inVal) : val(inVal), next(nullptr) {}

		U val;
		Node<U>* next;
	};

private:
	Node<T>* head_;
	int size_;
};

template<typename T>
inline void LinkedList<T>::add(T val)
{
	Node<T>* newNode = new Node<T>(val);
	if (!head_)
	{
		head_ = newNode;
		++size_;
		return;
	}

	Node<T>* curr = head_;
	while (curr->next)
	{
		curr = curr->next;
	}
	curr->next = newNode;
	++size_;
}

template<typename T>
inline void LinkedList<T>::remove(T val)
{
	if (!head_)
	{
		std::cout << "remove(T val) interrupted - head is empty\n";
		return;
	}

	Node<T>* curr = head_;
	Node<T>* prev = nullptr;
	bool isFounded = false;
	do
	{
		if (curr->val == val)
		{
			isFounded = true;
			break;
		}

		prev = curr;

	} while (curr = curr->next);

	if (!isFounded)
	{
		std::cout << "remove(T val) - no element found with val = " << val << '\n';
		return;
	}

	if (curr == head_)
	{
		prev = head_;
		head_ = head_->next;
		delete prev;
		--size_;
		return;
	}

	if (!curr->next)
	{
		prev->next = nullptr;
		delete curr;
		--size_;
		return;
	}

	prev->next = curr->next;
	delete curr;
	--size_;
}

template<typename T>
inline bool LinkedList<T>::contains(int val)
{
	Node<T>* curr = head_;
	while (curr)
	{
		if (curr->val == val)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

template<typename T>
inline void LinkedList<T>::add(int pos, T val)
{
	if (pos < 0 || pos > size_)
	{
		std::cout << "add(int pos, T val) interrupted - incorrect position\n";
		return;
	}

	if (pos == 0)
	{
		add_forward(val);
		return;
	}
	if (pos == size_)
	{
		add(val);
		return;
	}

	Node<T>* curr = head_;
	Node<T>* newNode = new Node(val);
	while (pos != 1 && curr)
	{
		--pos;
		curr = curr->next;
	}

	newNode->next = curr->next;
	curr->next = newNode;
	++size_;
}

template<typename T>
inline void LinkedList<T>::add_forward(T val)
{
	Node<T>* newNode = new Node(val);
	if (!head_)
	{
		head_ = newNode;
	}
	else
	{
		newNode->next = head_;
		head_ = newNode;
	}
	++size_;
}

template<typename T>
inline void LinkedList<T>::remove_first()
{
	if (!head_)
	{
		std::cout << "remove_first() interrupted - head is empty\n";
		return;
	}
	Node<T>* temp = head_;
	head_ = head_->next;
	delete temp;
	--size_;
}

template<typename T>
inline void LinkedList<T>::remove_last()
{
	if (!head_)
	{
		std::cout << "remove_last() interrupted - head is empty\n";
		return;
	}

	Node<T>* curr = head_;
	Node<T>* prev = nullptr;
	do
	{
		prev = curr;
		curr = curr->next;

	} while (curr->next);
	prev->next = nullptr;
	delete curr;
	--size_;
}

template<typename T>
inline void LinkedList<T>::print()
{
	Node<T>* curr = head_;
	std::cout << "Size of linked list: " << size_ << '\n';
	std::cout << "List:\n[ ";
	while (curr)
	{
		std::cout << curr->val << ' ';
		curr = curr->next;
	}
	std::cout << "]\n";
}

template<typename T>
inline void LinkedList<T>::clear()
{
	Node<T>* curr = head_;

	while (curr)
	{
		Node<T>* temp = curr;
		curr = curr->next;
		delete temp;
	}
	head_ = nullptr;
	size_ = 0;
}

template<typename T>
inline int LinkedList<T>::size()
{
	return size_;
}