#include <stdio.h>
#include <string>
#include <windows.h>
extern int hello_1(char const * str);
int main(int argc, char ** argv)
{
	hello_1("jun");
	std::string s = "jack";
	hello_1(s.c_str());
	HANDLE hdl = NULL;
	DWORD result = WaitForSingleObject(hdl, 30);
	if(result != WAIT_OBJECT_0){
		hello_1("WaitForSingleObject");
	}
	return 0;
}