#include <iostream>
#include<stdio.h>
#include <fstream>

using namespace std;

int main(){
	int N, K;
	cin >> N >> K;
	int* A=new int[N];
	for(int i=0; i<N; i++) {
		cin >> A[i];
	}
    int ans = N+2;
    int M[K+1];
    M[0] = 0;
    for(int i = 1; i < K+1; ++i)
         M[i] = -1;
    long int pref[N+1];
    pref[0] = 0;

    for(int i = 1; i < N+1; ++i){
        pref[i] = A[i-1] + pref[i-1];
    }

    for(int i = 0; i < N;  i++){

        for(int j = 1; j < i+1; j++){

            long int  S = pref[i] - pref[i-j];
            if(S > K) break;

            if(M[S] == -1)
                M[S] = j;
            else 
                M[S] = min(M[S], j);

        }
     for(int j = i; j < N; j++) {

        long int S = pref[j+1] - pref[i];
        if(S > K) break;

        if (M[K-S] != -1)                                                       
            ans = min(M[K-S] + j-i+1 , ans);

     }
    }
    if(ans <= N)
        cout << ans <<endl;
    else 
        cout << -1 <<endl;
}
