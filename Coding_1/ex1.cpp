#include <iostream>
#include <algorithm>   
#include <bits/stdc++.h>

using namespace std;

int check(int array[],int& median,int& N, int& K){
	
	int prefix[N];
	
	for (int i = 0; i < N; i++){
		if(array[i] >= median)
			prefix[i] = 1;
		else
			prefix[i] = -1;
	}
	//prefix
	for (int i = 1; i < N; i++){
		prefix[i] += prefix[i-1];
	}
	
	int minus = min(0,prefix[0]);
	int max_sum = 0;
	max_sum = max(0,prefix[K-1]);
	
	for (int i = 1 ; i < N-K+1; i++){
		
		max_sum = max(max_sum,prefix[i+K-1]-minus);
		minus = min(minus,prefix[i]);
	}
	
	if (max_sum > 0)
		return 1;
	else
		return 0;	
}
int findMax(int array[], int N, int K) {
	int low = 1, high = N + 1;
	int temp = -1;
  
    while (low <= high) {
    int mid = low + (high - low) / 2;


    if (check(array,mid, N, K)){
      temp = mid;
	  low = mid + 1;
      
}
    else
      high = mid - 1;
}
  return temp;
}

int main()
{
	int N, K; 
    cin >> N >> K;
    int a[N];
	for (int i = 0; i < N; i++) {
		cin >> a[i];
    }

	int l = 0;
	int r = N-1;
	int temp = -99;
	cout << findMax(a, N, K) << endl;
	return 0;
}


