#include <iostream>
using std::cout;
using std::cin;
using std::endl;
class Node{
public:
    int key, degree;
    Node* p;
    Node* child;
    Node* sibling;
    Node* binomial_heap_minimum();
    void binomial_link(Node* y, Node* z);
    void binomial_heap_union(Node* h1, Node* h2);
    Node* binomial_heap_merge(Node* h1, Node* h2);
    void Insert();
    void Delete_min();
    Node* Reverse(Node* ptr);
    void Print(Node* temp);
    void Display();

};

//Global pointers
Node* head = NULL;
Node* prev = NULL;
Node* head1 = NULL;


//Function for finding the minimum element in the roots of the binomial heap.
Node* Node::binomial_heap_minimum()
{
    Node* y = NULL;											//This function will traverse the the linked list of roots of all the trees present in the binomial heap
    Node* x = head;
    Node* t = head;
	if(x==NULL){													//If the head is set to NULL, then there are no elements in the binomial heap
        return t;
    }
    int mini = x->key;
    y=x;
    x = x->sibling;
    while(x!=NULL){													//This loop will traverse the whole list and store the smallest key in the variable 'mini'
        if(mini>x->key){
            mini = x->key;
            y = x;
            prev = t;
        }
        t = x;
        x = x->sibling;
    }
    return y;														//And then we return the pointer to the node which contains the minimum key.
}

void Node::binomial_link(Node* y, Node* z)
{																	//This function is used to make the parent of node y equal to the node z
    y->p = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;													//And the degree of the parent node z is increased by 1
}

//Function for finding the union of two binomial heaps
void Node::binomial_heap_union(Node* h1, Node* h2)
{
    head = binomial_heap_merge(h1, h2);								//The union function first calls the merge function which returns the merged list with the pointer head
    if(head==NULL){
        return;
    }
    Node* x = head;
    Node* prevx = NULL;
    Node* nextx = x->sibling;
    while(nextx!=NULL){							
        if(x->degree!=nextx->degree){								//If the degree of two adjacent nodes are not equal, then we simply move ahead
            prevx = x;
            x = nextx;
        }
        else{														//If they are equal, then we have 3 cases
            if((nextx->sibling!=NULL)&&(x->degree==nextx->sibling->degree)){			//If the 3rd node after these 2 nodes also has the same degree, then we move ahead
                prevx = x;
                x = nextx;
            }
            else if(x->key<nextx->key){								//Else we make the node with the smaller key as the child of the node with the larger key
                x->sibling = nextx->sibling;
                binomial_link(nextx, x);
            }
            else{													//And the last case is when the 2nd node has the lower value, we make it as the child of its previous node
                if(prevx!=NULL){
                    prevx->sibling = nextx;
                    binomial_link(x, nextx);
                    x = nextx;
                }
                else{
                    head = nextx;
                    binomial_link(x, nextx);
                    x = nextx;
                }
            }
        }
        nextx = x->sibling;
    }
}

//Merging two binomial heaps.
Node* Node::binomial_heap_merge(Node* h1, Node* h2)
{																	//This function is used to merge two binomial heaps in order of their degrees
    Node* a = h1;											//It works similar to the merge function which we use in the merge sort procedure
    Node* b = h2;
    Node* h = a;
    Node* aprev = NULL;
    Node* temp;
    while(a!=NULL && b!=NULL){
        if(a->degree==b->degree){									//We keep on adding the b values to the binomial heap a till a or b becomes empty 
            temp = b->sibling;
            b->sibling = a->sibling;
            a->sibling = b;
            b = temp;
            aprev = a->sibling;
            a = a->sibling->sibling;
        }
        else if(a->degree<b->degree){								//If a has lesser degree, then a will be inserted into the list
            aprev = a;
            a = a->sibling;
        }
        else{														//Otherwise b will be inserted before a in the list
            temp = b->sibling;
            b->sibling = a;
            if(aprev==NULL){
                h = b;
                aprev = b;
            }
            else{
                aprev->sibling = b;
                aprev = b;
            }
            b = temp;
        }
    }
    if(b!=NULL){													//When a becomes empty, we add the remaining elements of b into a at the end
        if(aprev==NULL){
            h = b;
        }
        else{
            aprev->sibling = b;
        }
    }

    return h;
}

//Reversing a linked list(for deletion)
Node* Node::Reverse(Node* ptr)
{																				//This function is a simple way to reverse a linked list of nodes
    if(ptr==NULL){
        return NULL;
    }
    Node* prev = ptr;													//We start with the head of the linked list and make reverse connections over it
    Node* next;
    ptr = ptr->sibling;
    if(ptr!=NULL)
        next = ptr->sibling;
    prev->sibling = NULL;
    while(ptr!=NULL){
        ptr->sibling = prev;
        prev = ptr;
        ptr = next;
        if(ptr!=NULL){
            next = ptr->sibling;
        }
    }
    return prev;																//At the end, we return the head of the reversed linked list, which is also a binomial heap
}

void Node::Insert()
{
    Node* temp = new Node();												//We allocate memory to the new node
    cout << "Enter Value to Insert\n";
    cin >> temp->key;
    temp->degree = 0;															//We make its degree equal to 0
    temp->p = temp->child = temp->sibling = NULL;
    Node *tp = head;
    binomial_heap_union(tp, temp);												//And then we call union over this node and the existing binomial heap
}

//Deletes the minimum element from the roots of the binomial heap.
void Node::Delete_min()
{
    Node* temp = binomial_heap_minimum();								//This function will delete the minimum root from the binomial heap
    if(temp==NULL){
        cout<<"\nHeap already Empty\n";
        return;
    }
    if(temp==head){
        head = head->sibling;
    }
    if(prev!=NULL){
        prev->sibling = temp->sibling;
    }
    Node* t = Reverse(temp->child);										//We reverse the children of the deleted node and place a pointer over its head
    Node* tp = head;

    binomial_heap_union(tp, t);													//Then we call union over the two binomial heaps.
}

void Node::Display()
{
    Node* temp = head;
    while(temp!=NULL){
        Print(temp);
        temp=temp->sibling;
    }
    cout << endl;
}

void Node::Print(Node* temp){
    while(temp!=NULL){
        cout<<temp->key<< " ";
        Print(temp->child);
        temp=temp->sibling;
    }
}
int main()
{
    Node o;
    while(1){
        cout << "\n\n1............Insert\n2..........Delete Min\n3.........Display\n4...........Find Min\n5........Exit\n\n";
        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
            o.Insert();                                          
            prev = NULL;
            break;

        case 2:
            o.Delete_min();                                        
            prev = NULL;
            break;

        case 3:
            o.Print(head);                                             
            prev = NULL;
            break;
        
        case 4:
        {
            Node* tt = o.binomial_heap_minimum();             
            if(tt==NULL){
                cout <<"\nHeap Empty\n";            
            }
            else
                cout <<"\nMinimum Element :  " << tt->key << endl;      
            break;
        }
        case 5:
            exit(0);
        }
    }

    return 0;
}
