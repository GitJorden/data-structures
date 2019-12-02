#include "LinkedList.h"

namespace hw_wet_1
{
	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList()
	{
		this->length = 0;
		this->head = nullptr;
	}

	template <class T>
	DoublyLinkedList<T>::~DoublyLinkedList()
	{
		int thisLinkedListLength = this->length;
		for (int i = 0; i < thisLinkedListLength; i++)
		{
			DeleteNode(*this->head);
		}
	}

	template <class T>
	void DoublyLinkedList<T>::InsertNodeFromHead(Node<T>& node)
	{
		node.prev = nullptr;
		this->head->prev = &node;
		node.next = this->head;
		this->head = &node;
		this->length++;
	}

	template <class T>
	void DoublyLinkedList<T>::InsertNodeFromTail(Node<T>& node)
	{
		node.next = nullptr;
		node.prev = this->tail;
		this->tail->next = &node;
		this->tail = &node;

		this->length++;
	}

	template <class T>
	void DoublyLinkedList<T>::DeleteNode(Node<T>& node)
	{
		if (node.prev == nullptr && node.next != nullptr)
		{
			this->head->prev = nullptr;
		}
		else if (node.prev != nullptr && node.next == nullptr)
		{
			this->tail->prev = nullptr;
		}
		else
		{
			node.next->prev = node.prev;
			node.prev->next = node.next;
		}
		delete &node;

		length--;
	}

	template <class T>
	void DoublyLinkedList<T>::CreateNewNodeFromHead(T data)
	{
		Node* node = new Node();
		node->data = data;
		this->InsertNodeFromHead(*node);
	}

	template <class T>
	void DoublyLinkedList<T>::CreateNewNodeFromTail(T data)
	{
		Node* node = new Node();
		node->data = data;
		this->InsertNodeFromTail(*node);
	}
}