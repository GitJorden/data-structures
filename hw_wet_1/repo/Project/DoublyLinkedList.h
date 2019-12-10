#include <iostream>

namespace hw_wet_1
{
	template <class T>
	struct Node
	{
		Node(T& data)
			:data(data) {
		}
		Node<T>* next;
		Node<T>* prev;
		T data;
	};

	template <class T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList()
		{
			this->length = 0;
			this->head = nullptr;
			this->tail = nullptr;
		}

		~DoublyLinkedList()
		{
			int thisLinkedListLength = this->length;
			for (int i = 0; i < thisLinkedListLength; i++)
			{
				DeleteNode(*this->head);
			}
		}

		Node<T>& GetNext(Node<T>& node) { return node.next; }
		Node<T>& GetHead() { return *head; }
		Node<T>& GetTail() { return *tail; }
		int GetListLength() { return this->length; }

		void InsertNodeFromHead(Node<T>& node)
		{
				node.prev = nullptr;
				this->head->prev = &node;
				node.next = this->head;
				this->head = &node;
				this->length++;
		}
		void InsertNodeFromTail(Node<T>& node)
		{
				node.next = nullptr;
				node.prev = this->tail;
				this->tail->next = &node;
				this->tail = &node;

				this->length++;
		}

		void DeleteNode(Node<T>& node)
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

		void DeleteNodeAndSaveTheData(Node<T>& node)
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

			length--;
		}

		void CreateNewNodeFromHead(T& data)
		{
			Node<T>* node = new Node<T>(data);
			node->data = data;
			this->InsertNodeFromHead(*node);
		}
		void CreateNewNodeFromTail(T& data)
		{
			Node<T>* node = new Node<T>();
			node->data = &data;
			this->InsertNodeFromTail(*node);
		}
	private:
		int length;
		Node<T>* head;
		Node<T>* tail;
	};
}