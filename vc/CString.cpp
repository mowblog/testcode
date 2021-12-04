#include "afx.h"
#include <iostream>
using namespace std;

void main()
{
	CString Hex="0123456789ABCDEFabcdef";
	
	CString hexString="gfwa00000000000000000000000000000000";
	
	cout<<hexString.SpanIncluding(Hex);
}