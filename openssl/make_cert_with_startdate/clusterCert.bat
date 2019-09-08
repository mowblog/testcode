REM # ！/bin/sh

REM touch index.txt
REM echo 00000000 > serial

del *.csr *.key *.crt index.txt* serial* *.pem *.p12 crlnumber* *.crl *.req

type nul > index.txt
type null > index.txt.attr
echo 00000000 > serial

openssl genrsa -out RootCA.key 2048
openssl req -new  -key RootCA.key -out RootCA.csr -subj /C=CN/ST=SX/O=IT/OU=Hello/CN=RootCA -config openssl.cnf
openssl ca -selfsign  -in RootCA.csr -key RootCA.key -config openssl.cnf -extensions v3_ca  -out RootCA.pem -batch -startdate 20190101000000Z -enddate 20290101000000Z -rand_serial

openssl genrsa -out Server1.key 2048
openssl req -new -key Server1.key  -out Server1.csr -subj /C=CN/ST=SX/O=IT/OU=Hello/CN=Server1 -config openssl.cnf 
openssl ca -in Server1.csr -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf -extensions usr_cert -out Server1.pem -batch -startdate 20190101000000Z -enddate 20290101000000Z -rand_serial

openssl genrsa  -out Server2.key 2048
openssl req -new -key Server2.key  -out Server2.csr -subj /C=CN/ST=SX/O=IT/OU=Hello/CN=Server2 -config openssl.cnf
openssl ca -in Server2.csr -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf -extensions usr_cert -out Server2.pem -batch -startdate 20190101000000Z -enddate 20290101000000Z -rand_serial

openssl genrsa  -out Server3.key 2048
openssl req -new -key Server3.key  -out Server3.csr -subj /C=CN/ST=SX/O=IT/OU=Hello/CN=Server3 -config openssl.cnf
openssl ca -in Server3.csr -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf -extensions usr_cert -out Server3.pem -batch -startdate 20190101000000Z -enddate 20290101000000Z -rand_serial

openssl genrsa  -out Client1.key 2048
openssl req -new -key Client1.key  -out Client1.csr -subj /C=CN/ST=SX/O=IT/OU=Hello/CN=Client1 -config openssl.cnf
openssl ca -in Client1.csr -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf -extensions usr_cert -out Client1.pem -batch -startdate 20190101000000Z -enddate 20290101000000Z -rand_serial

openssl genrsa  -out Client2.key 2048
openssl req -new -key Client2.key  -out Client2.csr -subj /C=CN/ST=SX/O=IT/OU=Hello/CN=Client2 -config openssl.cnf
openssl ca -in Client2.csr -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf -extensions usr_cert -out Client2.pem -batch -startdate 20190101000000Z -enddate 20290101000000Z -rand_serial

openssl genrsa  -out Client3.key 2048
openssl req -new -key Client3.key  -out Client3.csr -subj /C=CN/ST=SX/O=IT/OU=Hello/CN=Client3 -config openssl.cnf
openssl ca -in Client3.csr -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf -extensions usr_cert -out Client3.pem -batch -startdate 20190101000000Z -enddate 20290101000000Z -rand_serial

copy index.txt bak.index.txt

copy bak.index.txt index.txt
echo 01 > crlnumber
openssl ca -revoke Server1.pem -config openssl.cnf   -crldays 3650
openssl ca -gencrl -out Server1.crl -config openssl.cnf  

copy bak.index.txt index.txt
echo 02 > crlnumber
openssl ca -revoke Server2.pem -config openssl.cnf  -cert RootCA.pem -keyfile RootCA.key -crldays 3650
openssl ca -gencrl -out Server2.crl -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf  

copy bak.index.txt index.txt
echo 03 > crlnumber
openssl ca -revoke Server3.pem -config openssl.cnf  -cert RootCA.pem -keyfile RootCA.key -crldays 3650
openssl ca -gencrl -out Server3.crl -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf  

copy bak.index.txt index.txt
echo 04 > crlnumber
openssl ca -revoke Client1.pem -config openssl.cnf  -cert RootCA.pem -keyfile RootCA.key -crldays 3650
openssl ca -gencrl -out Client1.crl -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf  

copy bak.index.txt index.txt
echo 05 > crlnumber
openssl ca -revoke Client2.pem -config openssl.cnf  -cert RootCA.pem -keyfile RootCA.key -crldays 3650
openssl ca -gencrl -out Client2.crl -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf  

copy bak.index.txt index.txt
echo 06 > crlnumber
openssl ca -revoke Client3.pem -config openssl.cnf  -cert RootCA.pem -keyfile RootCA.key -crldays 3650
openssl ca -gencrl -outdir ./ -out Client3.crl -cert RootCA.pem -keyfile RootCA.key -config openssl.cnf  