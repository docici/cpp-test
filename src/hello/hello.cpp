#include <string>
#include <stdio.h>
#include <windows.h>
int hello_1(char const * str)
{
	printf("%s: hello %s\n", __FUNCTION__, str);
	HANDLE hdl = NULL;
	std::string s= "a std::string";
	DWORD result = WaitForSingleObject(hdl, 30);
	if(result != WAIT_OBJECT_0){
//		printf("%s: WaitForSingleObject failed %s\n", __FUNCTION__, s.c_str());
	}
	
	return 0;
}