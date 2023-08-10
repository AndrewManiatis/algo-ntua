#include <iostream>  
#include <stack>  
#include <vector>  
using namespace std;

stack<int> LIS_stacks[200000]; 

int replace_lis(vector<int> v, int lo, int hi, int To_Find)
{
    int mid;
    while (hi!=lo) {
		mid = (hi + lo) / 2;
		if (v[mid] < To_Find) {
			if (v[mid+1] >= To_Find)
			return mid+1;
			else
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }
    return mid;
}

int replace_lds(vector<int> v, int lo, int hi, int To_Find)
{
    int mid;
    while (hi!=lo) {
		mid = (hi + lo) / 2;
		if (v[mid] > To_Find) {
			if (v[mid+1] <= To_Find)
			return mid+1;
			else
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }
    return mid;
}
void LIS(int* gift,int N,vector<int>& LIS_vect, int* LIS_lengths){
	int index;
	for (int i=1; i<N; i++){
		if (LIS_vect.back() < gift[i]){
			LIS_vect.push_back(gift[i]);
			LIS_lengths[i] = LIS_vect.size();
			
			LIS_stacks[LIS_vect.size()-1].push(gift[i]);
		}
		else{	
			index = replace_lis(LIS_vect, 0, LIS_vect.size()-1, gift[i]);
			LIS_lengths[i] = index + 1;
			LIS_vect[index]  = gift[i];
			LIS_stacks[index].push(gift[i]);
	}
}
}
void LDS(int*gift, int N, vector<int>& LDS_vect,int* LDS_lengths){
	int index;
	for (int i=1; i<N; i++){
		if (LDS_vect.back() > gift[N-1-i]){
			LDS_vect.push_back(gift[N-1-i]);
			LDS_lengths[N-1-i] = LDS_vect.size();
		}
		else{	
			index = replace_lds(LDS_vect, 0, LDS_vect.size()-1, gift[N-1-i]);
			LDS_lengths[N-1-i] = index + 1;
			LDS_vect[index] = gift[N-1-i];
	}
}
}
int bs_stack(int lo, int hi, int To_Find){
	
	int mid;
    while (lo!=hi) {
		mid = (hi + lo) / 2;
		if (LIS_stacks[mid].top() < To_Find) {
			if (LIS_stacks[mid+1].top() > To_Find)
				return mid;
			else
				lo = mid + 1;
			}
		else if(LIS_stacks[mid].top() > To_Find)
			hi = mid;
        else
        	return mid;
}
return lo;
}
int main(){
	
	int N,K;
	cin >> N >> K;
	int* gift=new int[N];
	for (int i=0; i<N; i++)
		cin >> gift[i];	
		
	vector<int> LIS_vect;
	vector<int> LDS_vect;
	int* LIS_lengths = new int[N]; //here we store the LIS length until the element of index i
	LIS_lengths[0] = 1;
	int* LDS_lengths = new int[N]; //here we store the LDS length until the element of index i
	LDS_lengths[N-1] = 1;
	
	LIS_vect.push_back(gift[0]);
	LIS_stacks[0].push(gift[0]);
	
	LDS_vect.push_back(gift[N-1]);
	
	LIS(gift,N,LIS_vect,LIS_lengths); //nlogn
	LDS(gift,N,LDS_vect,LDS_lengths); //nlogn
	int zerokmax = -1;
	if (K ==0){
		for (int i=0; i<N; i++){
			if (LIS_lengths[i] > zerokmax)
				zerokmax = LIS_lengths[i];
		}
		cout << zerokmax << endl;
		return 0;
	}
	
	int max_LIS = LIS_vect.size()-1;
	int temp_max = -1;
	/*
	cout<<  "LIS lengths:"<< endl;
	for (int i=0; i<N; i++){
		cout << LIS_lengths[i] << " ";
	}
	cout << endl << endl;

	cout<<  "LDS lengths:"<< endl;
	for (int i=0; i<N; i++){
		cout << LDS_lengths[i] << " ";
	}
	cout << endl << endl;	
	*/
	for (int i=0; i<N-1; i++){
		int temp = gift[N-1-i] + K;
		//cout << "For " << gift[N-1-i] << endl;
		
		LIS_stacks[LIS_lengths[N-1-i]-1].pop();
		
		if (LIS_stacks[LIS_lengths[N-1-i]-1].empty()){
			max_LIS --;
		}
		//cout << "Search: "<<bs_stack(0,max_LIS,temp)<< endl;
		if(LIS_stacks[bs_stack(0,max_LIS,temp)].top() == temp)
			temp_max = max(temp_max, bs_stack(0,max_LIS,temp) + LDS_lengths[N-1-i]);
		else
			temp_max = max(temp_max, bs_stack(0,max_LIS,temp) + 1 + LDS_lengths[N-1-i]);
		//cout << temp_max << endl;
				
}
cout << temp_max << endl;
}
