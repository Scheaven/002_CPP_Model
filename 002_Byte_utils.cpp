#include <algorithm>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <vector>
using namespace std;


template<typename T>
static T bytes2T(unsigned char *bytes)
{
    T res = 0;
    int n = sizeof(T);
    memcpy(&res, bytes, n);
    return res;
}


template<typename T>
static unsigned char * T2bytes(T u)
{
    int n = sizeof(T);
    unsigned char* b = new unsigned char[n];
    memcpy(b, &u, n);
    return b;
}

int main(int argc, char const *argv[])
{
	// int d = 267;
 //   unsigned char *p = T2bytes<int>(d);
 //   for(int i = 0; i<sizeof(d); i++)
 //   {
 //   		cout << i << "::" <<p << endl;
 //       printf("p[%d]=0xX\n", i, p[i]);
 //   }

 //   int aaa = bytes2T<int>(p);
 //   cout << aaa << endl;
 //   // printf("d=%d\n", d);
 //   delete []p;

   // 将float转化为bytes流
   float f = -0.727412;
   unsigned char *p  = T2bytes<float>(f);

   
   cout << sizeof(f) << ":::" << sizeof(p) << endl;

   unsigned char pp[2048][sizeof(f)]; //将存储byte流，存入矩阵

   // pp[0] = *p;
   cout << sizeof(pp) << endl;

  
   memcpy(&pp[0], p, sizeof(f));

   // cout << -0.7274 << endl;
   // for(int i = 0; i<sizeof(f); i++)
   // {
   // 	   memcpy(pp[0][i], &p[i], sizeof(1));
   //     printf("p[%d]=X\n", i, pp[0][i]);
   // }

  // 将bytes流转化为float

   // int as = sizeof(p);
   unsigned char *ppp = new unsigned char[sizeof(f)];
   memcpy(ppp, &pp[0], sizeof(f));
   // for(int i = 0; i<sizeof(f); i++)
   // {
   // 	   memcpy(ppp[i], &pp[0][i], sizeof(1));
   //     // printf("p[%d]=X\n", i, pp[0][i]);
   // }






   float fff = bytes2T<float>(ppp);

   // printf("f=%.1f\n", f);
   cout << "--" << fff << endl;
   delete []p;

	return 0;
}
