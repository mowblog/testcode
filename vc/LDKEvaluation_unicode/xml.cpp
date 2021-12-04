#include "stdafx.h"

//specified license manager
wchar_t * scope0 = 
L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <license_manager hostname=\"localhost\" /> \r\n"
"</haspscope>";

//specified lm ip address
wchar_t * scope1 =
L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <license_manager ip=\"??.??.??.??\" /> \r\n"
"</haspscope>";

//specified key id
wchar_t* scope2 =
L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <hasp id=\"123456789\" /> \r\n"
"</haspscope> \r\n"
"";

//specified product
wchar_t* scope3 =
L"<haspscope> \r\n"
"   <product id=\"123\"/> \r\n"
"</haspscope> \r\n";

//hl only
wchar_t* scope4=
L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <hasp type=\"HASP-HL\" /> \r\n"
"</haspscope>";

//unfiltered
wchar_t* scope_default =
L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope/>";



//create c2v
wchar_t* format3 =
L"<haspformat format=\"updateinfo\"/>";

//get fingerprint
wchar_t* format4 =
L"<haspformat format=\"host_fingerprint\"/>";

//license status
wchar_t* format1 =
L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspformat root=\"hasp_info\"> \r\n"
"    <feature> \r\n"
"        <attribute name=\"id\" /> \r\n"
"        <element name=\"license\" /> \r\n"
"        <hasp> \r\n"
"          <attribute name=\"id\" /> \r\n"
"          <attribute name=\"type\" /> \r\n"
"        </hasp> \r\n"
"    </feature> \r\n"
"</haspformat> \r\n"
"";

//accessible keys
wchar_t* format0 =
L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspformat root=\"hasp_info\"> \r\n"
"    <hasp> \r\n"
"        <attribute name=\"id\" /> \r\n"
"        <attribute name=\"type\" /> \r\n"
"        <feature> \r\n"
"            <attribute name=\"id\" /> \r\n"
"        </feature> \r\n"
"    </hasp> \r\n"
"</haspformat>";

//feature information
wchar_t* format2 =
L"<haspformat root=\"hasp_info\"> \r\n"
"    <feature> \r\n"
"       <attribute name=\"id\" /> \r\n"
"       <attribute name=\"locked\" /> \r\n"
"       <attribute name=\"expired\" /> \r\n"
"       <attribute name=\"disabled\" /> \r\n"
"       <attribute name=\"usable\" /> \r\n"
"    </feature> \r\n"
"</haspformat>";

