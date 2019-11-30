#include <bits/stdc++.h>
using namespace std;

class DisjointSet{
	public:
		unordered_map <int,int> parent;					//Container to Store parent of each element
		int Find(int k);
		void Union(int x, int y);
		void print(vector <int> set);
};

int DisjointSet::Find(int k){				//funtion to find parent
	if(parent[k]==k){
		return k;
	}
	return(Find(parent[k]));
}

void DisjointSet::Union(int x, int y){			//funtion to do union of two sets
	int a=Find(x);
	int b=Find(y);
	parent[b]=a;

}
void DisjointSet::print(vector <int> set){				//Printing parent of each element
	cout<<"Printing Parent of Each Element\n"<<endl;
	for(int i : set){
		cout<<Find(i)<<" ";
	}
	cout<<endl;
}
int main(){
	DisjointSet ds;
	vector<int> set;					//Array to store elements
	int k=0;
	int ch;
	do{
		cout<<"1.....INSERT IN SET\n2......UNION\n3.......PRINT\n4.....EXIT\n"<<endl;
		cout<<"Enter Choice\n"<<endl;
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"Enter value to be inserted"<<endl;
				int p;
				cin>>p;
				set.push_back(p);
				ds.parent[p]=p;
				break;
			case 2:
				cout<<"ENter numbers for union"<<endl<<endl;
				int g,h;
				cin>>g>>h;
				ds.Union(g,h);
				break;
			case 3:
				ds.print(set);
				break;
			case 4:
				break;			

		}
	}while(ch!=4);
	return 0;
}
