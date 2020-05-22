#include<iostream>
using namespace std;
#define rows 8
#define cols 8
int a[rows][cols];
int b[rows][cols];
int c[rows][cols];
int main()
{
	int m,n,i,j,k,p,q;
	cin>>m>>n;//输入矩阵a 
	for(i=0;i<m;++i)
		for(j=0;j<n;++j)
			cin>>a[i][j];
			
	cin>>p>>q;//输入矩阵b 
	for(i=0;i<p;++i)
		for(j=0;j<q;++j)
			cin>>b[i][j];
			
	for(i=0;i<m;++i){//矩阵c=a*b  m为a的行
		for(j=0;j<q;++j){ // q为b的列
			c[i][j]=0;
			for(k=0;k<n;++k) //n 为a的列
				c[i][j]+=a[i][k]*b[k][j];
			}
	}
	
	for(i=0;i<m;++i){//输出矩阵c 
		for(j=0;j<q;++j)
			{
				cout<<c[i][j]<<" ";
			}
		cout<<endl;
	}
	system("pause");
	return 0;
}