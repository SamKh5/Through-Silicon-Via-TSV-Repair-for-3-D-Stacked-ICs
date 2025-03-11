// C++ program for calculating average distances to farthest and nearest redundant TSVs
#include<bits/stdc++.h>
using namespace std;

double findDmaxNoDiag(int n, vector<pair<int,int>> faultyTSV) {
	
	int dist_sum = 0;
	
	for(int i=0;i<faultyTSV.size();i++) {
		int row = faultyTSV[i].first;
		int col = faultyTSV[i].second;
		
		dist_sum += 1+2*n-row-col;
	}
	
	double dist_avg = (double) dist_sum / (double) faultyTSV.size();
	
	return dist_avg;
}

double findDmaxDiag(int n, vector<pair<int,int>> faultyTSV) {
	
	double dist_sum = 0.0;
	
	for(int i=0;i<faultyTSV.size();i++) {
		int row = faultyTSV[i].first;
		int col = faultyTSV[i].second;
		
		dist_sum += 1.0 + 1.414*(n-max(row,col)) + (double)max(row,col) - (double)min(row,col);
	}
	
	double dist_avg = dist_sum / (double) faultyTSV.size();
	
	return dist_avg;
}

double findDmin(int n, vector<pair<int,int>> faultyTSV) {
	
	int dist_sum = 0;
	
	for(int i=0;i<faultyTSV.size();i++) {
		int row = faultyTSV[i].first;
		int col = faultyTSV[i].second;
		
		dist_sum += 1+n-max(row,col);
	}
	
	double dist_avg = (double) dist_sum / (double) faultyTSV.size();
	
	return dist_avg;
}

int32_t main()
{
	int n;
	cout<<"Enter side length of grid : "<<endl;
	cin>>n;
	
	int n_fault;
	cout<<"Enter the number of faulty TSV's : "<<endl;
    cin>>n_fault;
    
	vector<pair<int,int>> faultyTSV;
	cout<<"Enter the faulty TSV's positions(row and coloumn number) : "<<endl;
	
	for(int i=0;i<n_fault;i++) 
	{
		int x,y;
		cin>>x>>y;
		faultyTSV.push_back({x,y});
	}
	
	cout<<"Dmax without diagonal flow : "<<findDmaxNoDiag(n, faultyTSV)<<endl;
	cout<<"Dmax with diagonal flow : "<<findDmaxDiag(n, faultyTSV)<<endl;
	cout<<"Dmin : "<<findDmin(n, faultyTSV)<<endl;

    return 0;
}