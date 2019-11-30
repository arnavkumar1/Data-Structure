#include <iostream>
using namespace std;
class Node{
public:
    char colour; 
    int key;
    Node* left;
    Node* right;
    Node* parent;
	void Inorder(Node *root);
	void Insert(Node *z);
	void Insert_Fixup(Node *z);
	void Delete(Node *z);
	void Delete_Fixup(Node *x);
	void Transplant(Node *u, Node *v);
	Node* Search(Node *root, int value);
	void left_rotate(Node *x);
	void right_rotate(Node *x);
};

//This is the nil node, which will be used as the leaves. All leaf nodes will be nil and the parent of the root will also be nil
Node *nil = new Node();
Node *root = nil;

//Function prototypes

int main()
{
	Node o;
    nil->colour = 'b';
    nil->key = -1;
    nil->left = nil->right = nil->parent = NULL;
    while(1){
        cout << "\n1.........Insert\n2.........Delete\n3.........Search\n4........Print Inorder\n5...........Exit\n"<<endl;
        int choice;
        cin >> choice;
        switch(choice){
        case 1:
        {
            Node *z = new Node();						//We allocate memory to the new node and call the insert function of the RBT
            cout << "Enter the value to be inserted: \n";
            cin >> z->key;
            o.Insert(z);
        }
            break;
        case 2:
        {
            cout << "Enter the value of the node which has to be deleted: \n";		
            int value;
            cin >> value;
            Node *z = o.Search(root, value);
            if(z!=nil){								//If the required node is present in the tree, we call the delete function over that node
                o.Delete(z);
            }
            else
                cout << "No such node exists!\n";
        }
            break;
        case 3:
        {
            cout<<"\nEnter Value to Search"<<endl;
        	int l;
        	cin>>l;
        	Node *q=o.Search(root,l);
        	if(q!=nil)
        		cout<<"\nElement Found\n";	
        	else
        		cout<<"\nElement not found\n"<<endl;
        }
            break;
        case 4:
 			o.Inorder(root);       
	    	break;
	    case 5:
	    	exit(0);
        }
    }
    return 0;
}

//This function inserts a node into its appropriate position inside the rbtree just as we do in bst.
//Later on we call the fixup to fix the red black properties of the rbtree
void Node::Insert(Node *z)
{
    Node *y = nil;
    Node *x = root;
    while(x!=nil){							//we keep on traversing the tree till the time when we find the nil node, that is the leaf node
        y = x;
        if(z->key < x->key){						//If the key is lesser than the current node, then we traverse to the left child
            x = x->left;
        }
        else{								//If the key is greater than the current node, then we traverse to the right child
            x = x->right;
        }
    }
    z->parent = y;							//y is the key which is the parent of the nil node. So we make it the parent of the new node instead
    if(y==nil){								//IF y is nil, then there are no nodes in the tree, and so the new node becomes the root of the tree
        root = z;
    }
    else if(z->key < y->key){						//if the key of the new node is less than the parent's key, than we make it the left child of the parent y
        y->left = z;
    }
    else{								//Other wise we make z the right child of parent y
        y->right = z;
    }
    z->left = z->right = nil;
    z->colour = 'r';
    Insert_Fixup(z);
}

//Fixing the rb properties.
void Node::Insert_Fixup(Node *z)
{
    while(z->parent->colour=='r'){
        if(z->parent==z->parent->parent->left){						//If z is the left child, we have 3 cases
            Node *y = z->parent->parent->right;					//1 case when the uncle is red, and 2 when the uncle is black
            if(y->colour=='r'){
                z->parent->colour = 'b';							//In this case, we simply change the colours of the parent and uncle to black and change the grandparent's colour to red
                y->colour = 'b';
                z->parent->parent->colour = 'r';
                z = z->parent->parent;							//Then we check to see if the grandparent is violating any of the RB properties
            }
            else{
                if(z==z->parent->right){						//In the 2nd case, we perform a left rotation on z's parent
                    z = z->parent;
                    left_rotate(z);
                }
                else{									//And in the third case, we make z's parent black
                    z->parent->colour = 'b';						//We make its grandparent red
                    z->parent->parent->colour = 'r';
                    right_rotate(z->parent->parent);					//And then we perform right rotation on z's grandfather
                }
            }
        }
        else{										//If z is the right child, we have 3 cases again
            Node *y = z->parent->parent->left;					//1 case when the uncle is red, and 2 when the uncle is black
            if(y->colour=='r'){
                z->parent->colour = 'b';							//In this case, we simply change the colours of the parent and uncle to black and change the grandparent's colour to red
                y->colour = 'b';
                z->parent->parent->colour = 'r';
                z = z->parent->parent;							//Then we check to see if the grandparent is violating any of the RB properties
            }
            else{
                if(z==z->parent->left){							//In the 2nd case, we perform a right rotation on z's parent
                    z = z->parent;
                    right_rotate(z);
                }
                else{
                    z->parent->colour = 'b';						//And in the third case, we make z's parent black
                    z->parent->parent->colour = 'r';					//We make its grandparent red
                    left_rotate(z->parent->parent);					//And then we perform right rotation on z's grandfather
                }
            }
        }
    }
    root->colour = 'b';									//At the end, we have to make sure that the root is black
}

//Delete function performs the same way as the delete function of the bst.
//We later call fixup to fix the rb properties of the rbtree
void Node::Delete(Node *z)
{
    Node *y = z;
    Node *x;
    char y_og_colour = y->colour;
    if(z->left==nil){							//For deletion, we have 3 cases. If the left child is nil, then we replace the node with its right child
        x = z->right;
        Transplant(z, z->right);
    }
    else if(z->right==nil){						//If the right child is nil, then we replace the node with the left child
        x = z->left;
        Transplant(z, z->left);
    }
    else{								//ELse we find the successor to replace it with the deleted node. And then we delete the successor in the remaining tree
        y = z->right;
        while(y->left!=nil){
            y = y->left;
        }
        y_og_colour = y->colour;
        x = y->right;
        if(y->parent==z){						//This process of deletion is the same as the deletion in the binary search tree
            x->parent = y;
        }
        else{
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;						//After all the connections after the deletions are made, then we check the colour of the deleted node
        y->left->parent = y;
        y->colour = z->colour;
    }
    if(y_og_colour=='b'){							//If a red node is deleted then there is no problem with the properties of the rbtree. But if a black node is deleted, then some properties might get violated
            Delete_Fixup(x);						//Hence we call the delete fixup
    }									
}

//Fixing the rb properties
void Node::Delete_Fixup(Node *x)
{
    while(x!=root && x->colour=='b'){
        if(x==x->parent->left){							//We have the following 4 cases whem x is the left child of its parent
            Node *w = x->parent->right;					//1 when the sibling is red, and 3 when the sibling is black
            if(w->colour=='r'){							//When the sibling is red
                w->colour = 'b';
                x->parent->colour = 'r';
                left_rotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->colour=='b' && w->right->colour=='b'){			//When both children of x's sibling are black
                w->colour = 'r';
                x = x->parent;
            }
            else{
                if(w->right->colour=='b'){					//When the right child of x's sibling is black
                    w->left->colour = 'b';
                    w->colour = 'r';
                    right_rotate(w);
                    w = x->parent->right;
                }
                else{								//When the right child of x's sibling is red
                    w->colour = x->parent->colour;
                    x->parent->colour = 'b';
                    w->right->colour = 'b';
                    left_rotate(x->parent);
                    x = root;
                }
            }
        }
        else{									//The same 4 cases follow when x is the right child of its parent
            Node *w = x->parent->left;
            if(w->colour=='r'){
                w->colour = 'b';
                x->parent->colour = 'r';
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if(w->left->colour=='b' && w->right->colour=='b'){
                w->colour = 'r';
                x = x->parent;
            }
            else{
                if(w->left->colour=='b'){
                    w->right->colour = 'b';
                    w->colour = 'r';
                    left_rotate(w);
                    w = x->parent->left;
                }
                else{
                    w->colour = x->parent->colour;
                    x->parent->colour = 'b';
                    w->left->colour = 'b';
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
    }
    x->colour = 'b';
}

void Node::Transplant(Node *u, Node *v)					//This function is used to replace the node v with the node u
{
    if(u->parent==nil){							//If u is the root of the tree, then we make v as the new root
        root = v;
    }
    else if(u==u->parent->left){					//Other wise we connect v to the parent of the node u
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;						//And then we make the parent of v equal to the parent of u
}

void Node::Inorder(Node *root)						//This display is the standard form of displaying trees
{									//It prints the nodes of the tree in the ascending order of the weights
    if(root!=NULL){
        Inorder(root->left);
        if(root!=nil){
            cout << root->key << "-" << '(';
	   		cout<<root->colour;					//The order of traversal is as follows: LeftChild->Root->RightChild
			cout << ')' << " ";
		}
        Inorder(root->right);
    }
}

//This function searches for a particular node in the rb tree
Node* Node::Search(Node *root, int value)
{
    if(root==nil){							//This function will either return nil if the node is not present, or it will return the pointer to the required node
        return root;
    }
    if(value==root->key){						//IF the value of the current node is equal to the required value, then we return the pointer to the found node
        return root;
    }
    else if(value < root->key){
        Search(root->left, value);					//Else if the value is lesser than the key of the current node, then we traverse to the left child of the current node
    }
    else{				
        Search(root->right, value);					//if the value is greater than the key of the current node, then we traverse to the right child of the current node
    }
}

//Function for left rotation about x
void Node::left_rotate(Node *x)						//This function will perform the left rotation about the node x
{
    if(x==NULL){
        return;
    }
    Node *y = x->right;						//y is the right child of x
    x->right = y->left;
    if(y->left!=nil){
        y->left->parent = x;						//If the left child of y is not nil, then we make the parent of y's left child as x
    }
    y->parent = x->parent;						//Then we make the parent of y equal to the parent of x
    if(x->parent==nil){
        root = y;
    }
    else if(x==x->parent->left){					//Then we make the left or right child of x's parent as y
        x->parent->left = y;
    }									//This will break the link btw x and its original parent
    else{
        x->parent->right = y;
    }
    y->left = x;							//Then we make the left child of y as x and declare the parent of x as y
    x->parent = y;
}

//Function for right rotation about x
void Node::right_rotate(Node *x)
{									//This function will perform the right rotation about the node x
    if(x==NULL){
        return;
    }
    Node *y = x->left;
    x->left = y->right;
    if(y->right!=nil){							//If the right child of y is not nil, then we make the parent of y's right child as x
        y->right->parent = x;
    }
    y->parent = x->parent;						//Then we make the parent of y equal to the parent of x
    if(x->parent==nil){
        root = y;
    }
    else if(x==x->parent->right){					//Then we make the left or right child of x's parent as y
        x->parent->right = y;
    }									//This will break the link btw x and its original parent
    else{
        x->parent->left = y;
    }
    y->right = x;							//Then we make the left child of y as x and declare the parent of x as y
    x->parent = y;
}



