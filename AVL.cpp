//SHANZAY GAUHAR---L174236
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;

template<class K, class T>
class AVLNode {
public:
	K Key;
	T * data;
	int height;
	AVLNode<K, T> *left, *right;

	AVLNode()
	{
		data = nullptr;
		height = 0;
		left = nullptr;
		right = nullptr;
	}
	AVLNode(K key, T* Data = nullptr, int H = 0, AVLNode<K, T>* Left = nullptr, AVLNode<K, T>* Right = nullptr)
	{
		Key = key;
		data = new T;
		*data = *Data;
		height = H;
		left = Left;
		right = Right;
	}
	AVLNode(const AVLNode<K, T>& obj)
	{
		Key = obj.Key;
		height = obj.height;
		left = obj.left;
		right = obj.right;
		data = new T;
		*data = *obj.data;
	}
	AVLNode& operator=(const AVLNode<K, T>& obj)
	{
		Key = obj.Key;
		height = obj.height;
		left = obj.left;
		right = obj.right;
		data = new T;
		*data = *obj.data;
	}
	~AVLNode()
	{
		delete data;
	}
};
template<class K, class T>
class AVLMAP {

	/* Note we are making AVLMAP not node*/
	/*Add all the functions here */

private:
	AVLNode< K, T >* root;
public:
	AVLMAP(AVLNode<K, T>* ROOT = 0)
	{
		root = ROOT;
	}
	void InsertRecursively(K key, T*& data)
	{
		InsertRecursively(key, data, root);
	}
	//Insert recursively
	void InsertRecursively(K key, T*& data, AVLNode<K, T>*& bptr)
	{
		if (bptr == nullptr)
		{
			bptr = new AVLNode<K, T>(key, data);
		}
		else if (key == bptr->Key)
		{
			return; //since the value already exists, we don't have to insert it again
		}
		else if (key > bptr->Key)
		{
			InsertRecursively(key, data, bptr->right);
		}
		else if (key < bptr->Key)
		{
			InsertRecursively(key, data, bptr->left);
		}

		balance(bptr);
	}
	void PrintRecursively()
	{
		PrintRecursively(root);
	}
	void visit(AVLNode<K, T>* bptr)
	{
		cout << bptr->Key << setw(10) << *bptr->data << endl;
	}
	void PrintRecursively(AVLNode<K, T>* bptr)
	{
		if (bptr != nullptr) //basecase
		{
			//Inorder treversal, prints in ascending order LNR
			PrintRecursively(bptr->left);
			visit(bptr);
			PrintRecursively(bptr->right);
		}
	}
	int MaxHeight(AVLNode<K, T>* node_1, AVLNode<K, T>* node_2)
	{
		if (node_1 != nullptr && node_2 != nullptr)
		{
			if (node_1->height > node_2->height)
				return	node_1->height;
			else
				return node_2->height;
		}
		else if (node_1 == nullptr && node_2 != nullptr)
			return node_2->height;
		else if (node_1 != nullptr && node_2 == nullptr)
			return node_1->height;
		return -1;
	}

	int height(AVLNode<K, T>* node)
	{
		if (node == nullptr)
			return -1;

		return 1 + MaxHeight(node->left, node->right);
	}
	void rightRotate(AVLNode<K, T> *&bptr)
	{
		AVLNode<K, T>* orphan = bptr->left->right;
		AVLNode<K, T>* y = bptr->left;

		y->right = bptr;
		bptr->left = orphan;
		bptr->height = height(bptr); // update nodes height
		y->height = height(y);
		bptr = y;
	}
	void leftRotate(AVLNode<K, T> *& bptr)
	{
		AVLNode<K, T>* orphan = bptr->right->left;
		AVLNode<K, T>* y = bptr->right;
		y->left = bptr;
		bptr->right = orphan;


		bptr->height = height(bptr); // update nodes height
		y->height = height(bptr->right);     //because bptr right is disturbed and an orphan is attached here
		bptr = y;

	}
	void doubleLeftRightRotation(AVLNode<K, T> *&bptr) {
		leftRotate(bptr->left);
		rightRotate(bptr);
	}
	void doubleRightLeftRotation(AVLNode<K, T> *&bptr) {
		rightRotate(bptr->right);
		leftRotate(bptr);
	}
	void balance(AVLNode<K, T>* & t)
	{
		if (t == nullptr)
		{
			return;
		}
		if (height(t->left) - height(t->right) > 1)   //right rotation
		{

			if (height(t->left->left) >= height(t->left->right)) {
				rightRotate(t);

			}
			else {
				doubleLeftRightRotation(t);
			}
		}
		else if (height(t->right) - height(t->left) > 1)
		{
			if (height(t->right->right) >= height(t->right->left)) {
				leftRotate(t);
			}

			else {
				doubleRightLeftRotation(t);
			}

		}
		t->height = MaxHeight(t->left, t->right) + 1;
	}
	//Recursive lookup Function
	void lookupRecursively(K key)
	{
		bool flag = lookupRecursively(key, root);
		if (flag == 1)
			cout << endl << "Found\n";
		else
			cout << endl << "Not Found\n";
	}
	bool lookupRecursively(K key, AVLNode<K, T>* bptr)
	{
		if (bptr != nullptr) //base case
		{
			if (key == bptr->Key)
			{
				cout << key << "\t" <<  *bptr->data << endl;
				return true;
			}

			else if (key > bptr->Key)   //right side of BStree contains larger values
				return lookupRecursively(key, bptr->right);

			else if (key < bptr->Key)  //left side of BStree contains smaller values
				return lookupRecursively(key, bptr->left);
		}
		return false;
	}
	void Checkbalance()
	{
		static AVLNode<K, T>*  bptr = root;
		balance(root->left);
		balance(root);
		balance(root->right);
	}
	//Recursive Delete Function
	void DeleteRecursively(K key)
	{
		return DeleteRecursively(root, key);
	}
	void DeleteRecursively(AVLNode<K, T>*& node, K key)
	{
		if (node)  //basecase
		{
			if (node->Key == key)
			{
				DeleteNode(node);
			}
			else if (node->Key > key)
			{
				DeleteRecursively(node->left, key);
			}
			else if (node->Key < key)
			{
				DeleteRecursively(node->right, key);
			}
		}

	}
	//DELETE NODE FUNCTION TO DELETE NODE
	void DeleteNode(AVLNode<K, T>*& node)
	{
		AVLNode<K, T>* temp = node;
		//node is pointing to the Bnode which needs to be deleted
		//its address is stored in temp 
		//and node is then further modified in the code
		//condition for one or no child
		if (node->left == nullptr)
		{
			node = node->right;
			delete temp;
			temp = 0;
		}
		else if (node->right == nullptr)
		{
			node = node->left;
			delete temp;
			temp = 0;
		}
		//Conditions with two childs
		else
		{
			AVLNode<K, T>* temp;
			//maximum from the left is replaced at the node to be deleted
			//deletion by copy
			K max = MaxValue(node->left, temp);
			node->Key = max;

			delete node->data;
			node->data = temp->data;
			temp->data = nullptr;
			DeleteRecursively(node->left, max);
		}
		Checkbalance();
	}
	K MaxValue(AVLNode<K, T>* node, AVLNode<K, T>*&temp)
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		K value = node->Key; //saves the copy of data to return
		temp = node;
		return value;
	}
	void Destroy(AVLNode<K, T>* node)    //post order deletion LRN
	{
		if (node)  //basecase
		{
			Destroy(node->left);
			Destroy(node->right);
			delete node;
		}
	}
	~AVLMAP()
	{
		Destroy(root);
		root = nullptr;
	}
	void PlaceCursor(int x, int y) {
		COORD c;
		c.X = x; c.Y = y;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, c);
	}

	void Print()
	{
		AVLNode<K, T>* node = root;
		int x = 0;
		int y = 0;
		if (node)
		{
			while (node->left)   //moving towards the left most element
			{
				x--;
				node = node->left;
			}
			Print(root, x);
		}
	}

	void Print(AVLNode<K, T>* node, int& x){
		if (node){
			int y=root->height-node->height;
			Print(node->left, ++x);
		
			y = 2*(root->height-node->height);  //multiplied by 2 to increase distance between keys
			PlaceCursor(++x, y);
			cout << node->Key << endl;

			
			if (node->left)
			{
				PlaceCursor(x - 1, y + 1);
				cout << "/";
			} 
			if (node->right)
			{
				PlaceCursor(x + 1, y + 1);
				cout << "\\";
			}
			Print(node->right, ++x);
		}
	}

};

class ProductData {
	friend ostream& operator << (ostream& out, ProductData & obj)
	{
		out << obj.name << "\t" << obj.quantity << endl;
		return out;
	}
public:
	ProductData()
	{
		name = "";
		quantity = 0;
	}
	ProductData(string Name, int Quantity)
	{
		name = Name;
		quantity = Quantity;
	}
private:
	string name; //Value
	int quantity; //Value
};
template <class K, class T>
void LoadAVL(ifstream& in, AVLMAP<int, ProductData>& tree)
{
	in.open("test.txt");
	char name[100];
	char temp;
	K id;
	int quan;

	if (!in)
	{
		cout << "ERROR LOADING FILE\n";
		return;
	}
	else
	{
		in.getline( name,100); //header
		while (!in.eof())
		{
			in >> id;

			int i = 0;

			temp = in.get(); //gets tab
			temp = in.get(); //next character

			while (temp != '\t' && temp != '\n')
			{
				name[i++] = temp;
				temp = in.get();
			}

			name[i] = '\0';

			in >> quan;
			T* obj = new T(name, quan);  //CREATE OBJECT OF THE TYPE TO INSERT

			tree.InsertRecursively(id, obj);

		}
	}
}

void menu()
{
	cout << "1.LOAD FROM FILE\n";
	cout << "2.INSERT RECURSIVELY\n";
	cout << "3.DELETE RECURSIVELY\n";
	cout << "4.LOOK FOR AN ELEMENT\n";
	cout << "5.PRINT RECURSIVE\n";
	cout << "6.PRINT TREE\n";
	cout << "7. EXIT\n";
}
int main()
{
	cout << "Associative Map using AVLMAP\n";
	AVLMAP<int, ProductData> ProductMap;

	int choice=0;
	while (choice < 7)
	{
		cout << endl << endl << endl;
		menu();
		cin >> choice;
		if (choice == 1)
		{
			ifstream in;
			LoadAVL<int, ProductData>(in, ProductMap);
		}
		else if (choice == 2)
		{
			int key;
			string name;
			int quan;
			cout << "please enter key, name and quantity of the item you would like to insert respectively\n";
			cin >> key;
			cin >> name >> quan;
			ProductData* a = new ProductData(name, quan);
			ProductMap.InsertRecursively(key, a);
		}
		else if (choice == 3)
		{
			int key;
			cout << "Please enter the key you would like to delete\n";
			cin >> key;
			ProductMap.DeleteRecursively(key);
		}
		else if (choice == 4)
		{
			int key;
			cout << "Please enter the key you would like to search\n";
			cin >> key;
			ProductMap.lookupRecursively(key);
		}
		else if (choice == 5)
		{
			cout << "--------------------Print---------------------------------------\n";
			ProductMap.PrintRecursively();
			cout << "-----------------------------------------------------------------\n";
		}
		else if (choice == 6)
		{
			system("CLS");
			cout << endl;
			ProductMap.Print();

		}
	}
	
	return 0;
}