#include <iostream>

namespace hw_wet_1
{
	template <class T>
	class Node
	{
	public:
		Node<T>* next;
		Node<T>* prev;
		T data;
	};

	template <class T>
	class DoublyLinkedList
	{
	public:
		int length;
		Node<T>* head;
		Node<T>* tail;

		DoublyLinkedList();
		~DoublyLinkedList();

		void InsertNodeFromHead(Node<T>& node);
		void InsertNodeFromTail(Node<T>& node);
		void DeleteNode(Node<T>& node);

		void CreateNewNodeFromHead(T data);
		void CreateNewNodeFromTail(T data);
	};
}