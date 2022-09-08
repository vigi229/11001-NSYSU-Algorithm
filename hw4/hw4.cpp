#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime> 
#include <cstring>
#include <cmath>
using namespace std;
int main()
{
	srand(time(NULL));
	fstream Cfile,Wfile,Pfile,Outfile;
	string fileName,C,W,P;
	int c;
	cout<<"Select the file name:"<<endl;
	cin>>fileName;
	C=fileName+"/c.txt";
	W=fileName+"/w.txt";
	P=fileName+"/p.txt";
	Cfile.open(C.c_str(),ios::in);
	Wfile.open(W.c_str(),ios::in);
	Pfile.open(P.c_str(),ios::in);
	Cfile>>c;
	//cout<<"c= "<<c<<endl;
	int temp,w[1000],p[1000],best[1000],ori[1000],ans=0,weight=0;
	memset(best,0,sizeof(best));
	memset(ori,0,sizeof(best));
	int n=0;
	while(!Wfile.eof())
	{
		Wfile>>w[n];
		Pfile>>temp;
		if(Wfile.fail())
			break;
		p[n]=-1*temp;
		n++;
	}
	Cfile.close();
	Wfile.close();
	Pfile.close();
	while(weight<c)
	{
		int i=rand()%n;
		if(!best[i])
		{
			ans+=p[i];
			weight+=w[i];
		} 
		best[i]=1;
	}
	//for(int i=0;i<n;i++)
	//	cout<<best[i]<<" ";
	//cout<<"初始隨機值: p= "<<abs(ans)<<" w= "<<weight<<" "<<endl;
	while(weight>c)
	{
		int i=rand()%n;
		if(best[i])
		{
			ans-=p[i];
			weight-=w[i];
		} 
		best[i]=0;
	}
	//for(int i=0;i<n;i++)
	//	cout<<best[i]<<" ";
	//cout<<"降成合理值: p= "<<abs(ans)<<" w= "<<weight<<" "<<endl;
	int new_ans,new_weight;
	double T=2000,Tf=0.00001,Tc=0.9999;
	bool change=true,eq=false;
	
	while(T>Tf)
	{
		if(change)
		{
		new_ans=ans;
		new_weight=weight;
		for(int i=0;i<n;i++)
			ori[i]=best[i];
		}
		while(new_weight<=c)
		{
			int i=rand()%n;
			if(!ori[i])
			{
				new_ans+=p[i];
				new_weight+=w[i];
			} 
			ori[i]=1;
			if(new_weight==c&&rand()%10)
			{
				eq=true;
				//cout<<"eq"<<endl;
				break;
			}
			else
				eq=false;
		}
		if(!eq)
		{
			while(new_weight>=c)
			{
				int i=rand()%n;
				if(ori[i])
				{
					new_ans-=p[i];
					new_weight-=w[i];
				} 
					ori[i]=0;
				if(new_weight==c&&rand()%10)
				{
					eq=true;
					//cout<<"eq"<<endl;
					break;
				}
				else
					eq=false;
			}
		}
		double diff=new_ans-ans;//neg
		//cout<<exp(-diff/T)<<endl;
		if(diff<=0)
		{
			//cout<<"T "<<T<<" ans "<<ans<<" new_ans "<<new_ans<<endl;
			ans=new_ans;
			weight=new_weight;
			for(int i=0;i<n;i++)
				best[i]=ori[i];
			change=false;
		}
		else if(exp(-diff/T)*RAND_MAX>rand())
		{
			//if(ans==-309)			
			//	cout<<"another T "<<exp(-diff/T)*RAND_MAX<<" "<<RAND_MAX<<" ans "<<ans<<" new_ans "<<new_ans<<endl;
			weight=new_weight;
			ans=new_ans;
			for(int i=0;i<n;i++)
				best[i]=ori[i];
			change=false;
		}
		else
			change=true;	
		T=T*Tc;
	}
	//for(int i=0;i<n;i++)
	//	cout<<best[i]<<" ";
	cout<<"final: p= "<<abs(ans)<<endl;
	fileName="ans_"+fileName+".txt";
	Outfile.open(fileName.c_str(),ios::out);
	Outfile<<abs(ans)<<endl;
	for(int i=0;i<n;i++)
		Outfile<<best[i]<<endl;
	return 0;
} 
