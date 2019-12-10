//
// Created by HP on 01/12/2019.
//

#ifndef WET1_STRUCT_GENERIC_TREE_H
#define WET1_STRUCT_GENERIC_TREE_H
#include <iostream>
namespace hw_wet_1
{


	enum ReturnValues
	{
		SUCCESS,
		FAILURE,
		ALLOCATION_ERROR,
		INVALID_INPUT,
		EXISTS,
		NOT_EXISTS
	};



	template <class T, class U>
	class Vertex
	{
	public:
		U* key;
		T* data;
		Vertex* dad;
		Vertex* l_son;
		Vertex* r_son;
		int h;
		//builder
		Vertex(T* data, U* key, Vertex* dad = NULL, Vertex* l_son = NULL, Vertex* r_son = NULL) :
			key(key), data(data), dad(dad), l_son(l_son), r_son(r_son), h(0)
		{
		}
		// no need for copy constructor and = operator
		~Vertex()
		{
			if (this)
			{
				delete key;
				delete data;
			}
		}
		U* getKey()
		{
			return key;
		}
		int getHeight()
		{
			return h;
		}
		int max(int a, int b)
		{
			return a > b ? a : b;
		}



		//U should has operators: ==, <, =
		//starts from given vertex.
		//returns reference to vertex if its in the tree and if not its father.
		Vertex<T, U>* vertexSearch(U* key2find)
		{
			if (!this)return dad;
			if (*key == *key2find) return this;
			if (*key2find < *key)
			{
				if (!l_son)return this;
				return l_son->vertexSearch(key2find);
			}
			else
			{
				if (!r_son)return this;
				return r_son->vertexSearch(key2find);
			}
		}
		//we use this function only on existing vertex that is not leaf
		int calcBF()
		{
			if (!l_son)
				return (-1) - r_son->getHeight();
			if (!r_son)
				return l_son->getHeight() - (-1);
			return l_son->getHeight() - r_son->getHeight();
		}
		void update_height()
		{
			if (this)
			{
				int lh;
				int rh;
				if (l_son)
					lh = l_son->h;
				else lh = -1;
				if (r_son)
					rh = r_son->h;
				else rh = -1;
				h = max(lh, rh) + 1;
			}
		}
		//updates dads new son
		void update_dad(Vertex<T, U>* new_son)
		{
			if (dad)
			{
				if (dad->l_son == this)
					dad->l_son = new_son;
				else
					dad->r_son = new_son;
			}
		}
		//calls in swap vertex
		/*void update_dad_in_2_sons(){
			if(!dad) return;
			if(l_son) {
				l_son->dad = dad;
			}
			if(r_son){
				r_son->dad = dad;
			}
		}*/
		//finds min vertex in r_son sub tree
		//operates on vertex with 2 sons
		Vertex<T, U>* maxVertex()
		{
			Vertex<T, U>* v = l_son;
			while (v->r_son)
				v = v->r_son;
			return v;
		}
		void swapVertices(Vertex<T, U>* v_2_swap)
		{
			U* swapped_old_key_p = v_2_swap->key;
			T* swapped_old_data_p = v_2_swap->data;
			v_2_swap->key = key;
			v_2_swap->data = data;
			key = swapped_old_key_p;
			data = swapped_old_data_p;
		}

		void vertexPrintKeys()
		{
			if (this != NULL)
			{
				l_son->vertexPrintKeys();
				std::cout << *(key) << " ";
				r_son->vertexPrintKeys();
			}
		}

	};

	template <class T, class U>
	class AvlTree
	{
		Vertex<T, U>* root;
	public:

		int length = 0;
		//creates new avlTree its root initialize to zero
		explicit AvlTree() :root(NULL)
		{
		}
		//return NULL - if the key isnt in tree
		//return Vertex* - if key in the tree
		Vertex<T, U>* find(U* key)
		{
			if (!root) return NULL;
			Vertex <T, U>* v = root->vertexSearch(key);
			//v cant be NULL
			if (v->key == key)return v;
			return NULL;
		}
		ReturnValues insert(Vertex<T, U>* new_v)
		{
			if (!root)
			{
				root = new_v;
				return SUCCESS;
			}
			Vertex <T, U>* v = root->vertexSearch(new_v->key);
			//v cant be NULL
			if (*(v->key) == *(new_v->key)) return EXISTS;
			//v is dad
			if ((*(new_v->key)) < (*(v->key)))
			{
				v->l_son = new_v;
				new_v->dad = v;
			}
			else
			{
				v->r_son = new_v;
				new_v->dad = v;
			}

			//
			new_v->h = 0;
			heihgtAndBalance(new_v);
			return SUCCESS;
		}

		//from delete dad we need to start balancing
		Vertex<T, U>* leafDelete(Vertex<T, U>* toDelete)
		{
			if (toDelete == root)
			{
				root = NULL;
				delete toDelete;
				return NULL;
			}
			Vertex<T, U>* delete_dad = toDelete->dad;
			toDelete->update_dad(NULL);

			delete toDelete;
			return delete_dad;
		}
		Vertex<T, U>* onlyChildDelete(Vertex<T, U>* toDelete)
		{
			//in case to delete is root no rolls are needed so we
			//return NULL
			if (toDelete == root)
			{
				if (toDelete->l_son)
				{
					root = toDelete->l_son;
					(toDelete->l_son->dad) = NULL;
					delete toDelete;
					return NULL;
				}
				else
				{
					root = toDelete->r_son;
					(toDelete->r_son->dad) = NULL;
					delete toDelete;
					return NULL;
				}
			}
			//case root is not to delete
			Vertex<T, U>* delete_dad = toDelete->dad;
			if (toDelete->l_son)
			{
				toDelete->update_dad(toDelete->l_son);
				toDelete->l_son->dad = toDelete->dad;
			}
			else
			{
				toDelete->update_dad(toDelete->r_son);
				toDelete->r_son->dad = toDelete->dad;
			}
			delete toDelete;
			return delete_dad;
		};


		Vertex<T, U>*  doubleSonDelete(Vertex<T, U>* toDelete, Vertex<T, U>* to_swap)
		{
			toDelete->swapVertices(to_swap);
			//to_swap is the  one we want to remove
			if (!(to_swap->l_son))
				return leafDelete(to_swap);
			else return onlyChildDelete(to_swap);
		};
		int* getArrayInOrder()
		{

		}
		// assumptions: < operator for key,
		// no rotations yet
		ReturnValues avlRemove(U* key)
		{
			if (!root)
			{
				return NOT_EXISTS;
			}
			Vertex<T, U> * v_2_delete = root->vertexSearch(key);
			//v cant be NULL
			if (v_2_delete->key != key)
				return NOT_EXISTS;
			//to be deleted is vertex reference to delete with the searched key
			Vertex<T, U>* balance_origin;
			//double son case
			if (v_2_delete->l_son && v_2_delete->r_son)
			{
				Vertex<T, U>* to_swap = v_2_delete->maxVertex();
				balance_origin = doubleSonDelete(v_2_delete, to_swap);
			}
			else if (!(v_2_delete->l_son) && !(v_2_delete->r_son))
				balance_origin = leafDelete(v_2_delete);
			else balance_origin = onlyChildDelete(v_2_delete);

			if (!balance_origin)return SUCCESS;
			//balance_origin is a real node
			Vertex<T, U> *p = balance_origin;
			int p_old_height;
			Vertex<T, U>*new_root = p;
			do
			{
				if (!p) return SUCCESS;
				p->update_height();
				p_old_height = p->h;
				int p_bf = p->calcBF();
				//
				if (p_bf == 2)
				{
					if (p->l_son->calcBF() >= 0)
					{
						new_root = llRotation(p);
					}
					else
					{
						new_root = lrRotation(p);
					}
				}
				if (p_bf == -2)
				{
					if (p->r_son->calcBF() <= 0)
					{
						new_root = rrRotation(p);
					}
					else
					{
						new_root = rlRotation(p);
					}
				}
				p = p->dad;
			} while (new_root->h != p_old_height);
			return SUCCESS;
		}

		//deletes vertex like in regular binary tree
		//returns NULL when key is not in tree or it was the only vertex;
		//returns Vertex<T,U>* to real object when we need to start roll from there



	/* Vertex<T, U> *bstRemove(U *key) {
		 if (!root) {
			 return NULL;
		 }
		 Vertex<T, U> *v = root->vertexSearch(key);
		 //v cant be NULL
		 if (v->key != key)
			 return NULL;
		 //v is reference to the vertex with the searched key
		 Vertex<T, U>* dad = v->dad;
		 //case v = leaf
		 if (!v->l_son && !v->r_son) {
			 v->update_dad(NULL);
			 delete v;
			 return dad;
		 }
		 //case v has only left son
		 if (!v->r_son) {
			 v->update_dad(v->l_son);
			 v->l_son->dad = dad;
			 delete v;
			 return dad;
		 }
		 //case v has only right son
		 if (!v->l_son) {
			 v->update_dad(v->r_son);
			 v->r_son->dad = dad;
			 delete v;
			 return dad;
		 }
		 //case v has 2 sons
		 v->swapVertices(v->maxVertex());
		 //after switch we can be only 2 possible cases
		 //leaf

		 dad = v->dad;
		 if (!v->l_son) {
			 v->update_dad(NULL);
			 delete v;
			 return dad;
		 }
			 //only left child
		 else {
			 v->update_dad(v->l_son);
			 v->l_son->dad = dad;
			 delete v;
			 return dad;

		 }
	 }*/

	 //distruct tree from top to bottom

		~AvlTree()
		{
			delete root;
		}

		//for test
		void treeClear()
		{
			delete root;
		}

		//updates height in the insertion course(hight of added leaf is allready 0)
		//makes rotations if needed

		void heihgtAndBalance(Vertex<T, U>* leaf)
		{
			Vertex<T, U>* v = leaf;
			while (v != root)
			{
				Vertex<T, U>* p = v->dad;
				if (p->h >= (v->h + 1)) return;
				p->h = v->h + 1;
				int p_bf = p->calcBF();
				//
				if (p_bf == 2)
				{
					if (p->l_son->calcBF() >= 0)
					{
						llRotation(p);
						break;
					}
					else
					{
						lrRotation(p);
						break;
					}
				}
				if (p_bf == -2)
				{
					if (p->r_son->calcBF() <= 0)
					{
						rrRotation(p);
						break;
					}
					else
					{
						rlRotation(p);
						break;
					}
				}
				v = p;
			}
		}
		void setRoot(Vertex<T, U>* v)
		{
			root = v;
		}
		Vertex<T, U>* llRotation(Vertex<T, U>* v)
		{
			//follows lecture names
			Vertex<T, U>* b = v;
			Vertex<T, U>* a = b->l_son;
			Vertex<T, U>* ar = (a->r_son);
			Vertex<T, U>* tree_dad = b->dad;
			//pointer switches inside subTree
			a->r_son = b;
			a->dad = b->dad;
			b->l_son = ar;
			b->dad = a;
			if (ar)
				ar->dad = b;
			//
			b->update_height();
			//update the new son for the dad of all sub tree
			if (!tree_dad)
			{
				root = a;
				return a;
			}
			if (tree_dad->l_son == b) (tree_dad->l_son) = a;
			else (tree_dad->r_son) = a;
			return a;
		}
		Vertex<T, U>* lrRotation(Vertex<T, U>* v)
		{
			//follows lectures names
			Vertex<T, U>* c = v;
			Vertex<T, U>* a = c->l_son;
			Vertex<T, U>* b = a->r_son;
			Vertex<T, U>* bl = b->l_son;
			Vertex<T, U>* br = b->r_son;
			Vertex<T, U>* tree_dad = c->dad;
			//pointer switches inside subTree
			if (bl)
				bl->dad = a;
			if (br)
				br->dad = c;
			b->l_son = a;
			b->r_son = c;
			b->dad = c->dad;
			a->r_son = bl;
			a->dad = b;
			c->l_son = br;
			c->dad = b;
			//
			a->update_height();
			c->update_height();
			b->update_height();
			//update the new son for the dad of all sub tree
			if (!tree_dad)
			{
				root = b;
				return b;
			}
			if (tree_dad->l_son == c) (tree_dad->l_son) = b;
			else (tree_dad->r_son) = b;
			return b;
		}
		Vertex<T, U>* rrRotation(Vertex<T, U>* v)
		{
			//follows lecture names
			Vertex<T, U>* b = v;
			Vertex<T, U>* a = b->r_son;
			Vertex<T, U>* al = (a->l_son);
			Vertex<T, U>* tree_dad = b->dad;
			//pointer switches inside subTree
			a->l_son = b;
			a->dad = b->dad;
			b->r_son = al;
			b->dad = a;
			if (al)
				al->dad = b;
			//
			b->update_height();
			//update the new son for the dad of all sub tree
			if (!tree_dad)
			{
				root = a;
				return a;
			}
			if (tree_dad->l_son == b) (tree_dad->l_son) = a;
			else (tree_dad->r_son) = a;
			return a;
		}
		Vertex<T, U>* rlRotation(Vertex<T, U>* v)
		{
			//follows lectures names
			Vertex<T, U>* c = v;
			Vertex<T, U>* a = c->r_son;
			Vertex<T, U>* b = a->l_son;
			Vertex<T, U>* bl = b->l_son;
			Vertex<T, U>* br = b->r_son;
			Vertex<T, U>* tree_dad = c->dad;
			//pointer switches inside subTree
			if (bl)
				bl->dad = c;
			if (br)
				br->dad = a;
			b->l_son = c;
			b->r_son = a;
			b->dad = c->dad;
			a->l_son = br;
			a->dad = b;
			c->r_son = bl;
			c->dad = b;
			//
			a->update_height();
			c->update_height();
			b->update_height();
			//update the new son for the dad of all sub tree
			if (!tree_dad)
			{
				root = b;
				return b;
			}
			if (tree_dad->l_son == c) (tree_dad->l_son) = b;
			else (tree_dad->r_son) = b;
			return b;
		}
		//for debug

		void treePrintKeys()
		{
			root->vertexPrintKeys();
		};

		/* void clearTree(){
			 if (this != NULL) {
				 l_son -> vertexPrintKeys();
				 std::cout << *(key) << " ";
				 r_son ->vertexPrintKeys();
			 }

		 }*/


		 //delete
		 //< operator over loading
		// bool operator<
		//inorder traversal

		/*old swapVertices
		 * {

			bool is_left_son = (v_2_swap == l_son);

			//update dads

			if(is_left_son){
				if(this->dad){
					if(this->dad->l_son==this)
						this->dad->l_son = v_2_swap;
					else
						this->dad->r_son = v_2_swap;
				}
			}
			else{
				if(this->dad){
					if(this->dad->l_son==this)
						this->dad->l_son = v_2_swap;
					else
						this->dad->r_son = v_2_swap;
				}
				if(v_2_swap->dad){
					if(v_2_swap->dad->l_son==v_2_swap)
						v_2_swap->dad->l_son =this;
					else
						v_2_swap->dad->r_son = this;
				}
			}

			//2 swap is always smaller

			//update 3 pointers of the 2 switched vertices
			Vertex<T,U>* or_old_dad= dad;
			Vertex<T,U>* or_old_left= l_son;
			Vertex<T,U>* or_old_right= r_son;
			//if statment is for case: 2 swap is left son of this
			if (is_left_son){
				(v_2_swap->l_son) = this;
				this->dad = v_2_swap;
			}
			else{
				v_2_swap->l_son = or_old_left;
				dad = v_2_swap->dad;
			}
			l_son = v_2_swap->l_son;
			r_son = v_2_swap->r_son;
			v_2_swap->dad = or_old_dad;
			v_2_swap->r_son = or_old_right;

			//update sons after swap
			v_2_swap->update_dad_in_2_sons();
			this->update_dad_in_2_sons();

		}
		 *
		 *
		 *
		 *
		 */



	};
}

#endif //WET1_STRUCT_GENERIC_TREE_H
