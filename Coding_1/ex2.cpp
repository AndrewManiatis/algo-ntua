#include <iostream>  
#include<stdio.h>  
#include <fstream>  
  
using namespace std;  
  
int main(){  
    //input
	int N, K;  
    
	cin >> N >> K;  
    
	int* A=new int[N];  
    
	for(int i=0; i<N; i++) {  
        cin >> A[i];  
    }  
    
	int ans = N+2;  
    
	int minlength[K+1];  
    
	minlength[0] = 0;  
    
	for(int i = 1; i < K+1; ++i)  
         minlength[i] = -1;  
    
	long int prefix[N+1];  
    
	//construct prefix array
    
    prefix[0] = 0;  
  
    for(int i = 1; i < N+1; ++i){  
        prefix[i] = A[i-1] + prefix[i-1];  
    }  
  
    for(int i = 0; i < N;  i++){  
  
        for(int j = i+1; j < N+1; j++) {  
  
        long int suml = prefix[j] - prefix[i];  
        if(suml > K) break;  
  
        if (minlength[K-suml] != -1)                                                         
            ans = min(minlength[K-suml] + j-i , ans);  
      
    }
		for(int j = 1; j < i+1; j++){  
  
            long int  suml = prefix[i] - prefix[i-j];  
            if(suml > K) break;  
  
            if(minlength[suml] == -1)  
                minlength[suml] = j;  
            else   
                minlength[suml] = min(minlength[suml], j);  
  
        }  
      
    }  
    if(ans <= N)  
        cout << ans <<endl;  
    else   
        cout << -1 <<endl;  
}
