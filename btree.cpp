#include <bits/stdc++.h>
#define t 3
using namespace std;

class Node{
	public:
		int key[5];
		Node* child[6];
		int n;											//Stores number of keys in a node
		bool leaf;
		void Create();
		void Insert(Node* x, int k);
		void ins(Node *x, int k);
		void split_child(Node* x, int i);
		void Print(Node* x);
		bool Search(Node* x, int k);
		int Find(Node* x, int k);
		void del_leaf(Node* x, int k);
		void del_nonleaf(Node* x, int k, int i);
		void fill(Node* x, int i);
		void del_tree(Node* x, int k);
		void merge(Node* x, int i);
		void borrow_from_left(Node* x, int i);
		void borrow_from_right(Node* x, int i);
		int post(Node* x, int i);
		int pre(Node* x, int i);


};
Node* root;

void Node::Print(Node* x){					//Preorder Traversal
	cout<<endl;
	for(int i=0; i<x->n; i++){
		cout << x->key[i] << " ";
	}
	cout << endl;
	if(!x->leaf){						//If root is not a leaf node, print its children			
		for(int i=0; i<x->n + 1; i++){
			Print(x->child[i]);
		}
	}
}
void Node::merge(Node* x, int i){
	/* Merges ith child of x, key i and i+1 th child of x */
	Node* y = x->child[i];
	Node* z = x->child[i+1];
	y->key[t-1] = x->key[i];
	int j;
	for(j=0; j<t-1; j++){
		y->key[t+j] = z->key[j];
		y->child[t+j] = z->child[j];
	}
	y->child[2*t-1] = z->child[t-1];
	y->n = 2*t - 1;
	delete(z);
	for(j = i; j < x->n - 1; j++){
		x->key[j] = x->key[j+1];
		x->child[j+1] = x->child[j+2];
	}
	x->child[x->n] = NULL;
	x->n = x->n - 1;
	/* If root becomes NULL, height of tree decreases by 1 and root comes down */
	if(x->n == 0){
		root = x->child[0];
		delete(x);
	}
}
void Node::del_leaf(Node* x, int k){
	/* Find the key, shift keys next to it to and decrease count by 1 */
	int i = Find(x, k);
	int j;
	for(j = i; j < x->n - 1; j++){
		x->key[j] = x->key[j+1];
	}
	x->n = x->n - 1;
}


void Node::del_nonleaf(Node* x, int k, int i){
	int v;
	if(x->leaf){
		del_tree(x, k);
		return;
	}
	Node* y = x->child[i];
	Node* z = x->child[i+1];
	/* Preceding child has atleast t keys. Find predecessor and swap with key. Then go down and continue recursively */
	if(y->n >= t){
		v = pre(x, i);
		x->key[i] = v;
		del_tree(x->child[i], v);
	}
	/* Succeding child has atleast t keys. Find successor and swap with key. Then go down and continue recursively */
	else if(z->n >= t){
		v = post(x, i);
		x->key[i] = v;
		del_tree(x->child[i+1], v);
	}
	/* Both childs have t-1 key. Merge them and continue recursively */
	else{
		merge(x, i);
		del_nonleaf(y, k, t-1);
	}
}

void Node::del_tree(Node* x, int k){
	int i = Find(x, k);
	if(i < x->n && k == x->key[i]){
		// Key found
		if(x->leaf) // delete from leaf
			del_leaf(x, k);
		else	//delete from non leaf
			del_nonleaf(x, k, i);
	}
	else{
		if(x->leaf){ // key doesn;t exist
			cout << "\nElement not in Tree\n";
			return;
		}
		/* Move the pointer to its appropriate position */
		/* Check if child has atleast t keys or not. If not call fill function */
		/* Recursively call the function again */
		if(x->child[i]->n < t)
			fill(x, i);
		if(x->child[i] == NULL) i--;
		del_tree(x->child[i], k);
	}
}
void Node::fill(Node* x, int i){
	Node* left = NULL;
	Node* right = NULL;
	/* Case 1- left sibling has atleast t keys, borrow from it */
	/* Case 2- right sibling has atleast t keys, borrow from it */
	/* Case 3- left sibling is not NULL, merge from it */
	/* Case 4- right sibling is not NULL, merge from it */
	if(i!=0)
		left = x->child[i-1];	
	if(i!=x->n)
		right = x->child[i+1];
	if(left!=NULL && left->n >=t)
		borrow_from_left(x, i);
	else if(right!=NULL && right->n >=t)
		borrow_from_right(x, i);
	else if(right!=NULL)
		merge(x, i);
	else
		merge(x, i-1);
}

void Node::borrow_from_left(Node* x, int i){
	/* Move max key k' of left sibling to parent node and ith key of parent node to its child */
	Node* y = x->child[i];
	Node* z = x->child[i-1];
	int j;
	for(j=y->n; j>0; j--){
		y->key[j] = y->key[j-1];
		y->child[j+1] = y->child[j];
	}
	y->child[1] = y->child[0];
	y->child[0] = z->child[z->n];
	y->key[0] = x->key[i-1];
	x->key[i-1] = z->key[z->n-1];
	z->child[z->n] = NULL;
	z->n = z->n - 1;
	y->n = y->n + 1;
}
void Node::borrow_from_right(Node* x, int i){
	/* Move min key k' of right sibling to parent node and ith key of parent node to its child */
	Node* y = x->child[i];
	Node* z = x->child[i+1];
	int j;
	y->child[y->n + 1] = z->child[0];
	y->key[y->n] = x->key[i];
	x->key[i] = z->key[0];
	for(j=0; j < z->n - 1; j++){
		z->key[j] = z->key[j+1];
		z->child[j] = z->child[j+1];
	}
	z->child[z->n - 1] = z->child[z->n];
	z->child[z->n] = NULL;
	z->n = z->n - 1;
	y->n = y->n + 1;
}

int Node::post(Node* x, int i){
	/* Find minimum value of next child */
	Node* y = x->child[i+1];
	while(y->child[0] != NULL)
		y = y->child[0];
	return  y->key[0];
}
int Node::pre(Node* x, int i){
	/* Find maximum value of prev child */
	Node* y = x->child[i];
	while(y->child[(y->n)] != NULL)
		y = y->child[(y->n)];
	return  y->key[y->n - 1];
}
void Node::Create(){     //Function to create a new B-Tree
	root=new Node();
	root->leaf=true;
	root->n=0;
}
int Node::Find(Node *x, int k){     //Funtion to find the index at which k is smaller or equal to the key */
	int i;
	for(i=0; i<x->n; i++){
		if(k <= x->key[i])
			break;
	}
	return i;
}
void Node::Insert(Node *x, int k){
	Node *y;
	//If root is full split the root node, shift center upwards and assign root to it.
	if(x->n == 2*t - 1){
		y = new Node();
		root = y;
		root->leaf = false;
		root->n = 0;
		root->child[0] = x;
		split_child(root, 0);										
	}
	ins(root, k);
}
void Node::split_child(Node *x, int i){
	//Create a new Node z and assign 2nd half of splitting node to z. Both keys and child, then move the middle value upwards
	Node* z =new Node();
	Node* y=x->child[i];				//Y points to the node to be splitted
	z->leaf=y->leaf;					//if y is leaf then z will also be
	z->n=t-1;
	y->n=t-1;							//size of nodes will be t-1(2) after splitting
	for(int j = 0; j < t-1; j++){       // New node gets last 2 keys	
		z->key[j] = y->key[j+t];
	}
	if (!y->leaf){							//Assign children of last two keys of y to z
		for(int j = 0; j < t; j++){
			z->child[j] = y->child[j+t];
			y->child[j+t] = NULL;
		}
	}
	for(int j = x->n; j > i; j--){			// Shfting child and key right to make space for new key
		x->key[j] = x->key[j-1];	
		x->child[j+1] = x->child[j];
	}
	x->child[i+1] = z;				// Adding child pointer to newly created node
	x->key[i] = y->key[t-1];		// Shifting middle value upwards
	x->n = x->n + 1;				// Size of node increases by 1
}
bool Node::Search(Node* x, int k){
	int i = 0;
	while (i < x->n && k > x->key[i]) //go through the node until key is smaller or equal to the node value in root
		i++;
	if(i < x->n && k == x->key[i]){		//if value is in the node, return true
		return true;
	}
	else if(x->leaf){					// if the node is leaf node return false			
		return false;
	}
	else{							//else go through its children to repeat the procedure
		Search(x->child[i], k);
	}

}
void Node::ins(Node *x, int k){			// Function to find appropriate Node to insert
	int i=x->n;
	if(x->leaf){                       // If x is a leaf, go to appropriate index and insert key there. Shift other keys forward. Increment the count of x by 1
		while(i>=1 && k < x->key[i-1]){
			x->key[i] = x->key[i-1];
			i--;
		}
		x->key[i] = k;
		x->n = x->n + 1;
	}
	else{								//If x is not a leaf go to the appropriate child to find the leaf node where key has to be inserted				
		while(i>=1 && k < x->key[i-1]){
			i--;
		}
		if(x->child[i]->n == 2*t - 1){			//If the child is full then call split_child() and insert according to value of k
			split_child(x, i);
			if(k > x->key[i])
				i++;
		}
		ins(x->child[i], k);			//Call the main insert function
	}
}



int main(){
	Node n;
	n.Create();					//Create a Empty B-Tree
	int ch;
	int v;
	do{
		cout<<"\n1........Insert\n2........Search\n3.........Delete\n4........Print\n5..........Exit\n";
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"Enter value to Insert"<<endl;
				cin>>v;
				if(root->n > 0 && n.Search(root, v)){
				cout << "Duplicate element\n";
				break;
				}
				n.Insert(root, v);
				cout << endl;
				break;
			case 2:
				cout<<"\nEnter value to Search\n";
				cin>>v;
				if(n.Search(root,v)){
					cout<<"\nElement Found\n"<<endl;
				}
				else{
					cout<<"\nElement not found\n"<<endl;
				}
				break;
			case 3:
				cout<<"\nEnter Value to Delete\n";
				cin>>v;
				n.del_tree(root,v);
				cout<<endl;	
			case 4:
				n.Print(root);
				cout<<endl;
				break;
			case 5:
				exit(0);
		}

	}while(ch!=5);
	return 0;
}