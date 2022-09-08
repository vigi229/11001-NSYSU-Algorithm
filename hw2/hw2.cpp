#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

struct data{
	int idx;
	double w,p,cp;
};
bool compare(data a,data b)
{
	return a.cp>b.cp;
}
int main()
{
	fstream Cfile,Wfile,Pfile,Outfile;
	string fileName,C,W,P;
	cout<<"Select the file name:"<<endl;
	cin>>fileName;
	C=fileName+"/c.txt";
	W=fileName+"/w.txt";
	P=fileName+"/p.txt";
	Cfile.open(C.c_str(),ios::in);
	Wfile.open(W.c_str(),ios::in);
	Pfile.open(P.c_str(),ios::in);
	
	data dataset[30];
	int c,n=0,best=0;
	Cfile>>c;
	
	while(!Wfile.eof())
	{
		Wfile>>dataset[n].w;
		Pfile>>dataset[n].p;
		dataset[n].cp=dataset[n].p/dataset[n].w;
		dataset[n].idx=n;
		n++;
	}
	sort(dataset,dataset+n,compare);
	Cfile.close();
	Wfile.close();
	Pfile.close();
	
	int i,flag[n]={0},weight=0,temp;
	for(i=0;i<n;i++)
	{
		if(dataset[i].w+weight>c)
			continue;
		weight+=dataset[i].w;
		best+=dataset[i].p;
		flag[dataset[i].idx]=1;
	}
	cout<<"Finish"<<endl;

	fileName="ans_"+fileName+".txt";
	Outfile.open(fileName.c_str(),ios::out);
	Outfile<<best<<endl;
	for(i=0;i<n;i++)
		Outfile<<flag[i]<<endl;
	return 0;
} 
