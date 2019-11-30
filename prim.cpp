#include <bits/stdc++.h>
using namespace std;

class Edge{							//Storing Edges of Graph
	public:
		friend class Heap;
		int v1,v2,weight;
};

class Heap{							//Min Heap
	public:
		friend class Edge;
		vector <Edge> A;		
		int Parent(int i){			//Parent of index
			return (i-1)/2;
		}
		int left(int i){			//Left Child of index
			return (2*i+ 1);
		}
		int right(int i){			//Right Child of Index 
			return (2*i+2);
		}
		void push(Edge x);
		void pop();
		Edge top();
		void heapify_down(int i);
		void heapify_up(int i);
		void swapp(Edge &a, Edge &b){		//Funtion to swap two Edges
			int t1=a.weight;
			a.weight=b.weight;
			b.weight=t1;
			int t2=a.v1;
			a.v1=b.v1;
			b.v1=t2;
			int t3=a.v2;
			a.v2=b.v2;
			b.v2=t3;
		}
};

void Heap::push(Edge x){			//Insert at the end of array and then call heapify_up funtion
	A.push_back(x);
	int index=A.size()-1;
	heapify_up(index);
}

void Heap::pop(){					//Copy last added element to the front, then remove it and then call heapify_down
	if (A.size()==0){
		cout<<"\nHeap Empty\n"<<endl;
		return;
	}
	A[0]=A.back();
	A.pop_back();
	heapify_down(0);
}

Edge Heap::top(){			//returns root/first element of edge
	return A[0];
}

void Heap::heapify_down(int i){			//compare with smallest(left and right child) and then swap until heap property is met
	int l=left(i);
	int r=right(i);
	int least=i;
	if(A[l].weight<A[i].weight && l<A.size())
		least=l;
	if(A[r].weight<A[least].weight && r<A.size())
		least=r;
	if(least!=i){
		swapp(A[i],A[least]);
		heapify_down(least);
	}
}

void Heap::heapify_up(int i){				//compare with parent and swap until heap property is restored
	if(i > 0){
	if(A[Parent(i)].weight>A[i].weight){
		swap(A[i],A[Parent(i)]);
		heapify_up(Parent(i));
		}
	}
}

int main(){
	Heap h;
	cout<<"\nEnter Number of Vertices"<<endl;
	int v,e;
	cin>>v;
	cout<<"\nEnter Number of Edges\n";
	cin>>e;
	Edge eo[e];			
	vector <Edge> G;						//Array of Edge to store edges of graph
	vector <Edge> MST;						//Array of Edge to Store the MST
	for(int i=0; i<e; i++){						//Input Edges
		cout<<"\nEnter Edge1, Edge2, Weight\n"<<endl;
		cin>>eo[i].v1>>eo[i].v2>>eo[i].weight;
		G.push_back(eo[i]);			
	}

	vector <int> m;
	int var = 0;
	/* Go through each vertex, find its neighbors, add them to Min Heap, extract the edge with minimum weight to MST,
	Remove the Edge from Edge List, go to next vertex until all vertices are visited */
	for(int i=0; i<v-1; i++){ 
		
		m.push_back(var);
		for(int j=0; j<e; j++){
			if(G[j].v1==var || G[j].v2==var){
				h.push(G[j]);
			}
		}
		Edge temp=h.top();
		
		while(find (m.begin(), m.end(), temp.v1) != m.end() && find (m.begin(), m.end(), temp.v2) != m.end()){
			h.pop();
			temp = h.top();
		}

		temp = h.top();
		if(find (m.begin(), m.end(), temp.v1) != m.end()){
			var = temp.v2;
		}
		else
			var = temp.v1;
		MST.push_back(temp);
		h.pop();
	}
	cout<<"\nThe Edges of Minimum Spanning Tree Are: \n"<<endl;
	for(int i=0; i<v-1; i++){
		cout<<MST[i].v1<<" "<<MST[i].v2<<" "<<MST[i].weight<<endl;
	}
	

}