#include <iostream>
using namespace std;

class Node{
	public:
		int data;
		Node* left;
		Node* right;
		Node* Insert(Node* root, int x);
		bool Search(Node* root, int x);
		Node* Delete(Node* root, int x);
	    void Print(Node* root);
	    Node* FindMin(Node* root);
};
Node* root;													

bool Node::Search(Node* root, int data){
	/* Start from root, compare value with it, if its less than root go to left subtree else go to right subtee */
	if(root==NULL){
		return false;
	}
	else if(root->data==data){
		return true;
	}
	else if(root->data>=data){
		return Search(root->left, data);
	}
	else{
		return Search(root->right, data);
	}
}


Node* Node::Insert(Node* root, int x){
	/* Create a new Node, if its greater than root, recursively call insert to right subtree else call insert to left subtree*/
	Node* temp = new Node();
	temp->data=x;
	temp->left=NULL;
    temp->right=NULL;
	if(root==NULL){	
		root=temp;
	}
	else if(x<=root->data){
		root->left= Insert(root->left, x);
	}
	else{
		root->right=Insert(root->right, x);
	}
	return root;	
}
Node* Node::FindMin(Node* root){
	//Funtion to find minimum from right subtree
		while(root->left!=NULL)
		root=root->left;
		return root;
	
}


Node* Node::Delete(Node* root, int x){
	if(root==NULL) return root;
	else if(x<root->data) root->left = Delete(root->left, x);
	else if(x>root->data) root->right = Delete(root->right, x);
	else{
		if(root->left==NULL && root->right==NULL){    //No child , Delete the node
			delete root;
			root=NULL;
		}
		else if(root->left==NULL){				// Only Right child, Attach the node to its right child and delete the node
			Node* temp=root;
			root=root->right;
			delete temp;
		}
		else if(root->right==NULL){			//Only left child, attach the node to its left child and delete the node
			Node* temp= root;
			root=root->left;
			delete temp;
		}
		else{									//2 children, Find minimum of right subtree and replace it with the Node's value
			Node* temp=FindMin(root->right);
			root->data=temp->data;
			root->right=Delete(root->right, temp->data);
		}
	}
	return root;
	
}

void Node::Print(Node* root){
	/* Inorder Print */
	if(root!=NULL){
		Print(root->left);
		cout<<root->data<<" ";
		Print(root->right);
	}	
}
int main(){
	root=NULL;
	Node b;
	int ch;
	do{
	cout<<"\n\n1.......Insert\n2......Search\n3........Delete\n4.......Print\n5......Exit\n"<<endl;
	cout<<"Enter Choice\n"<<endl;
	cin>>ch;
	switch(ch){
		case 1:
			cout<<"Enter Value to be inserted"<<endl;
			int x;
			cin>>x;
			root = b.Insert(root, x);
			break;
		case 2:
			cout<<"ENter value to search "<<endl;
			int sq;
			cin>>sq;
			if(b.Search(root, sq)){
				cout<<"Element Found"<<endl;
			}
			else{
				cout<<"Element not found"<<endl;
			}
			break;
			
		case 3:
			cout<<"Enter value to delete"<<endl;
			int d;
			cin>>d;
			root = b.Delete(root, d);
			if(root==NULL){
				cout<<"\nTree Empty"<<endl;
			}
			break;
		
		case 4:
			b.Print(root);
			break;
		
		case 5:
			break;
		}
	}
	while(ch!=5);
	return 0;
}
