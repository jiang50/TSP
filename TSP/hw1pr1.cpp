//Yucheng Jiang 525006053
//CSCE 420
//Due: Ocotber 2, 2017
//hw1pr1.cpp 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

class Tsp{
	public:
	Tsp(int num,vector<int> x,vector<int> y);
	void solve();
	int selectmin(vector<double> t);
	private:
	vector<int> node_x;
	vector<int> node_y;
	vector<vector<double>> distance;
	vector<int> col;
	vector<int> row;
	int p;
	
};

Tsp::Tsp(int num,vector<int> x,vector<int> y)
	:p(num),node_x(x),node_y(y),distance(num,vector<double>(num)){
	
	for(int i=0;i<p-1;i++){
		distance[i][i]=0;
		for(int j=i+1;j<p;j++){
			double dis=sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2));
			distance[i][j]=dis;
			distance[j][i]=dis;
		}
	}

	distance[p-1][p-1]=0;
	col.push_back(0);
	for(int i=1;i<p;i++)col.push_back(1);
	for(int i=0;i<p;i++)row.push_back(1);
}

int Tsp::selectmin(vector<double> t){

	int k=0;
	double m=-1;
	for(int j=0;j<p;j++){
		if(col[j]==1){
			if(m==-1){
				m=t[j];
				k=j;
			}
			else if(t[j]<m){
				m=t[j];
				k=j;
			}
		}
	}
	return k;
}



void Tsp::solve(){
	vector<double> temp(p);
	double s=0;//total distance
	int i=0;//current node
	int j=0;//next node
	while(row[i]){
		for(int k=0;k<p;k++){
			temp[k]=distance[i][k];
		}
		j=selectmin(temp);

		row[i]=0;
		col[j]=0;
		cout<<node_x[i]<<" "<<node_y[i]<<endl;
		s=s+distance[i][j];
		i=j;
	}
	
	cout<<s<<endl;
}


int main(int argc, char* argv[]){
	string fn=argv[1];
	ifstream ist{fn};
	if(!ist)perror("can't open input file!");
	vector<int>x;
	vector<int>y;
	string s;
	int num_p=0;
	while(!ist.eof()){
		num_p++;
		getline(ist,s);
		stringstream sstr(s);
		int x1,y1;
		sstr>>x1>>y1;
		x.push_back(x1);
		y.push_back(y1);
	}

	Tsp t(num_p,x,y);
	t.solve();
	
		
}