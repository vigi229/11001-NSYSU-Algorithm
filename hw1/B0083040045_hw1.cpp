#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime> 
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
	clock_t start,end;
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
	
	start=clock();
	
	int c,data[3][30],n=0,best=0,bestComp=0;
	Cfile>>c;
	
	while(!Wfile.eof())
	{
		Wfile>>data[0][n];
		Pfile>>data[1][n];
		data[2][n]=0;
		n++;
	}

	Cfile.close();
	Wfile.close();
	Pfile.close();
	
	int i=0,digit=0,price=0,weight=0;
	bool timesUp=false;
	double times=pow(2,n);
	while(i<times)
	{
		digit=0;price=0;weight=0;
		int temp=i;
		while(temp!=0)
		{
			if(temp%2==1)
			{
				if(data[0][digit]+weight>c)
					break;
				weight+=data[0][digit];
				price+=data[1][digit];
			}
			temp/=2;
			digit++;
		}
		if(price>best)
		{
			best=price;
			bestComp=i;
		}
		end=clock();
		if((end-start)>60000)
		{
			timesUp=true;
			break;
		}
		i++;
	}
	digit=0;
//	cout<<bestComp<<endl; 
	while(bestComp>0)
	{
		if(bestComp%2==1)
			data[2][digit]=1;
		bestComp/=2;
		digit++;
	}
	if(timesUp)
		cout<<"Running over 1 minute...."<<endl;
	else
		cout<<"Finish"<<endl;

	fileName="ans_"+fileName+".txt";
	Outfile.open(fileName.c_str(),ios::out);
	Outfile<<best<<endl;
	for(i=0;i<n;i++)
		Outfile<<data[2][i]<<endl;
	return 0;
} 
