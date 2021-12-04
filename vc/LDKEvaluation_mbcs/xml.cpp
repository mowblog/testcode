#include "stdafx.h"

//specified license manager
char *scope0 = 
"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <license_manager hostname=\"localhost\" /> \r\n"
"</haspscope>";

//specified lm ip address
char *scope1 =
"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <license_manager ip=\"??.??.??.??\" /> \r\n"
"</haspscope>";

//specified key id
char *scope2 =
"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <hasp id=\"123456789\" /> \r\n"
"</haspscope> \r\n"
"";

//specified product
char *scope3 =
"<haspscope> \r\n"
"   <product id=\"123\"/> \r\n"
"</haspscope> \r\n";

//hl only
char *scope4=
"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope> \r\n"
"    <hasp type=\"HASP-HL\" /> \r\n"
"</haspscope>";

//unfiltered
char *scope_default =
"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
"<haspscope/>";



//create c2v
char *format3 =
"<haspformat format=\"updateinfo\"/>";

//get fingerprint
char *format4 =
"<haspformat format=\"host_fingerprint\"/>";

//license status
char *format1 =
"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
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
char *format0 =
"<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \r\n"
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
char *format2 =
"<haspformat root=\"hasp_info\"> \r\n"
"    <feature> \r\n"
"       <attribute name=\"id\" /> \r\n"
"       <attribute name=\"locked\" /> \r\n"
"       <attribute name=\"expired\" /> \r\n"
"       <attribute name=\"disabled\" /> \r\n"
"       <attribute name=\"usable\" /> \r\n"
"    </feature> \r\n"
"</haspformat>";

