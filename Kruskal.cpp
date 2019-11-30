#include <bits/stdc++.h>
using namespace std;

class Edge{					//class to store edges of graph
public:
	int v1;
	int v2;
	int weight;
	
};
bool compareweight(Edge i, Edge j){				// compare operator to compare wieght of edges
	return (i.weight < j.weight);
}
class DisjointSet{								//Disjoint Set Data Structure
	public:
		unordered_map <int,int> parent;
		int Find(int k);
		void Union(int x, int y);
		void makeset (int v);
};

void DisjointSet::makeset(int v){				//Mark Parent of each vertex to itself. 
	for(int i=0; i<v; i++){
		parent[i]=i;
	}
}

int DisjointSet::Find(int k){				//Finds parent ot each vertex recursively
	if(parent[k]==k){
		return k;
	}
	return(Find(parent[k]));
}

void DisjointSet::Union(int x, int y){			//Union of two vertices
	int a=Find(x);
	int b=Find(y);
	parent[a]=b;

}

int main(){
	DisjointSet ds;
	int v,e;
	int p,q;
	cout<<"\nEnter number of vertices\n"<<endl;
	cin>>v;
	ds.makeset(v);								
	cout<<"\nEnter number of Edges\n"<<endl;
	cin>>e;
	Edge eo[e];									//Array of Edge Objects to store the edges of graph
	for(int i=0; i<e; i++)
	{
		cout<<"Enter Edge1, Edge2, weight"<<endl;
		cin>>eo[i].v1>>eo[i].v2>>eo[i].weight;
	}
	sort(eo, eo+e, compareweight);					//SOrt the edges according to weight
	cout<<"\n\nThe Edges of Minimum Spanning Tree are : \n "<<endl;
	for(int i=0; i<e; i++){
		p=eo[i].v1;
		q=eo[i].v2;
		p=ds.Find(p);
		q=ds.Find(q);
		if(p!=q){
			cout<<eo[i].v1<<" "<<eo[i].v2<<" "<<eo[i].weight<<endl;
			ds.Union(p,q);
		}
	}

	return 0;
}
