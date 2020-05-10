#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
using namespace std;
int main()
{
	time_t now;
	struct tm *timenow;
	time(&now);
	timenow = localtime(&now);
	cout << timenow->tm_year+1900<<"_"<<timenow->tm_mon+1<<"_"<<timenow->tm_mday
	<<"_"<<timenow->tm_hour<<":"<<timenow->tm_min<<":"<<timenow->tm_sec
	        << endl;
	return 0;
}


