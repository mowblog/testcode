del *.req *.key *.crt index.txt* serial* *.pem *.p12

type nul > index.txt
echo 00 > serial

rem openssl genrsa -out Root.key 2048
rem openssl req -new -x509 -days 3650 -key Root.key -out Root.pem -subj /CN=Root -config openssl.cnf -sha256
rem openssl x509 -req -extfile openssl.cnf -extensions v3_ca -in Root.req -out Root.pem -signkey Root.key -CAcreateserial -days 3650



openssl genrsa -out RootCA.key 2048
openssl req -new -x509 -days 3650 -key RootCA.key -out RootCA.pem -subj /C=CN/ST=GS/L=LZ/O=LZUiversity/OU=ETS/CN=RootCA/emailAddress=RootCA@lzu.cn -config openssl.cnf -sha256

openssl genrsa  -out Server.key 2048
openssl req -new -x509 -days 3650 -key Server.key  -out Server.req -subj /C=CN/ST=GS/L=LZ/O=LZUiversity/OU=ETS/CN=Server/emailAddress=RootCA@lzu.cn -config openssl.cnf
openssl ca -ss_cert Server.req -cert RootCA.pem -keyfile RootCA.key  -config openssl.cnf  -out Server.pem -outdir ./ -batch

openssl genrsa  -out Client.key 2048
openssl req -new -x509 -days 3650 -key Client.key  -out Client.req -subj /C=CN/ST=GS/L=LZ/O=LZUiversity/OU=ETS/CN=Client/emailAddress=RootCA@lzu.cn -config openssl.cnf
openssl ca -ss_cert Client.req -cert RootCA.pem -keyfile RootCA.key  -config openssl.cnf  -out Client.pem -outdir ./  -batch

openssl pkcs12 -export -in Server.pem -inkey Server.key -name Server -passout pass:Aa123456  -out Server.p12
openssl pkcs12 -export -in Client.pem -inkey Client.key -name Client -passout pass:Aa123456  -out Client.p12
keytool -import -alias Client -keystore ServerTrust.p12 -storepass Aa123456 -noprompt -file Client.pem
keytool -import -alias Server -keystore ClientTrust.p12 -storepass Aa123456 -noprompt -file Server.pem