
#include <bits/stdc++.h>
using namespace std;

float fractionArr[100]={0};

struct Item{
	float weight;
	float cost;
	float ratio;



};


bool comparator(Item i1,Item i2){
	return i1.ratio>i2.ratio;
}

void fractionalKnapsack(vector<Item> vec,int capacity){
	float rem=capacity;

	for(unsigned int i=0;i<vec.size();i++){

		if(rem>vec[i].weight){
			fractionArr[i]=1;
			rem-=vec[i].weight;
		}else{
			float part=rem/vec[i].weight;
			fractionArr[i]=part;
			rem-=vec[i].weight*part;
		}

	}


}

void printFractions(vector<Item> vec,int capacity){
	int totalcost=0;

	cout<<endl<<"";
	cout<<"  Weight\t"<<"Cost\t"<<"Max Fraction used"<<endl;

	for(unsigned int i=0;i<vec.size();i++){
		totalcost+=vec[i].cost*fractionArr[i];
		cout<<"\t"<<vec[i].weight<<"\t\t "<<vec[i].cost <<"\t\t\t"<<fractionArr[i]<<endl;
	}
	cout<<endl;

	cout<<" Max possible profit : "<<totalcost<<endl;

}

int main() {

	#ifndef ONLINE_JUDGE
		freopen("G:/Codeblocks/FractionalKnapsack/input.txt","r",stdin);
		freopen("G:/Codeblocks/FractionalKnapsack/output.txt","w",stdout);
	#endif
	int items,capacity;
	vector<Item> vec;
	cin>>items>>capacity;

	cout<<"Number of items: "<<items<<endl;
	cout<<"Capacity of bag: "<<capacity<<endl<<endl;

	for(int i=0;i<items;i++){
		int cost,weigh;
		cin>>weigh>>cost;
		int ratio=cost/weigh;
		Item item;
		item.ratio=ratio;
		item.cost=cost;
		item.weight=weigh;
		vec.push_back(item);

	}

	sort(vec.begin(),vec.end(),comparator);
	cout<<"Sorted as per ratio of cost to weight :\n";
	for (auto x : vec)
		cout << "[ w: " << x.weight << "  c: " << x.cost<< "  r: "<<x.ratio<< " ]\n";

	 fractionalKnapsack(vec,capacity);

	 printFractions(vec,capacity);

	return 0;
}
