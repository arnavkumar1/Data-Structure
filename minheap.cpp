#include <bits/stdc++.h>
using namespace std;

class Heap{
	public:
		vector <int> A;				//Array to store heap elements
		int Parent(int i){			//Parent of each index
			return (i-1)/2;
		}
		int left(int i){			//Left child
			return (2*i+ 1);
		}
		int right(int i){			//right child
			return (2*i+2);
		}
		void push(int x);
		void pop();
		int top();
		void heapify_down(int i);
		void heapify_up(int i);
};

void Heap::push(int x){				//insert element at last and then call heapify_up
	A.push_back(x);
	int index=A.size()-1;
	heapify_up(index);
}

void Heap::pop(){					//copy last added element to root and then delete it, call heapify_down to restore heap property
	if (A.size()==0){
		cout<<"\nHeap Empty\n"<<endl;
		return;
	}
	A[0]=A.back();
	A.pop_back();
	heapify_down(0);
}

int Heap::top(){				//return root/first elemet of heap/array
	if(A.size()==0){
		return -1;
	}
	return A[0];
}

void Heap::heapify_down(int i){			//compare with smallest of lchild,rchild and then swap until heap property is restored
	int l=left(i);
	int r=right(i);
	int least=i;
	if(A[l]<A[i] && l<A.size())
		least=l;
	if(A[r]<A[least] && r<A.size())
		least=r;
	if(least!=i){
		swap(A[i],A[least]);
		heapify_down(least);
	}
}

void Heap::heapify_up(int i){				//compare with parent and swap if value is smaller than parent to restore heap property
	if(i>0 && A[Parent(i)]>A[i]){
		swap(A[i],A[Parent(i)]);
		heapify_up(Parent(i));
	}
}

int main(){
	Heap h;
	int ch;
	int t;
	do{
		cout<<"\n1.......Insert\n2..........Find min\n3...........Delete Min\n4..........Print\n5...........Exit\n"<<endl;
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"\nEnter a number\n"<<endl;
				int k;
				cin>>k;
				h.push(k);
				break;
			case 2:
				t=h.top();
				if(t==-1){
					cout<<"\nHeap Empty\n";
				}
				else
					cout<<"\nMinimum Element : "<<t<<endl;
				break;
			case 3:
				h.pop();
				break;
			case 4:
				 for(int i=0; i<h.A.size(); i++){
				 	cout<<h.A[i]<<" ";
				 }
				 break;
			case 5:	
				exit(0);			
		}

	}while(ch!=5);
	return 0;
}