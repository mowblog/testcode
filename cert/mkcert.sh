#!/bin/bash

if [ $# -ne 1 ];then
    echo "usage ./mkcert.sh level"
    exit
fi

#是否给private key设定密码
PRIVATE_KEY_WITH_PASSWORD="false"
PASSWORD="helloworld"
DAYS=3650
SUBJECT=""
POLICY="policy_anything"
PKCSNAME="LZU"

if [ $PRIVATE_KEY_WITH_PASSWORD == "true" ];then
PASSOUT="-aes256 -passout pass:$PASSWORD"
PASSIN="-passin pass:$PASSWORD"
else
PASSOUT=""
PASSIN=""
fi

#keystore密码
PKCSPASSOUT="-passout pass:Aa123456"

rm -rf RootCA* newCert
LV=0
while [ $LV -lt $1 ]
do
    mkdir RootCA$LV
    touch RootCA$LV/index.txt RootCA$LV/serial
    echo "01" > RootCA$LV/serial
    CERTIFICATE="certificate     = \$dir/RootCA$LV.pem"
    PRIVATE_KEY="private_key     = \$dir/private/RootCA$LV.key"
    cp openssl.cnf openssl.cnf.tmp
    sed -i "48 a$CERTIFICATE" openssl.cnf.tmp
    sed -i "54 a$PRIVATE_KEY" openssl.cnf.tmp
    mv openssl.cnf.tmp RootCA$LV/openssl.cnf
    ((LV=LV+1))
done

LV=0
while [ $LV -lt $1 ]
do
    echo
    echo "======= creating RootCA$LV ======="
    echo
    if [ $LV -eq 0 ];then
        cd RootCA$LV
        openssl genrsa $PASSOUT -out RootCA$LV.key 2048
        openssl req -new -x509 -days $DAYS -key RootCA$LV.key $PASSIN -out RootCA$LV.pem -subj /C=CN/ST=GS/L=LZ/O=LZUiversity/OU=ETS/CN=RootCA$LV/emailAddress=RootCA$LV@lzu.cn -config openssl.cnf -sha256
    else
        cd ..; cd RootCA$LV
        openssl genrsa $PASSOUT -out RootCA$LV.key 2048
        openssl req -new -x509 -days $DAYS -key RootCA$LV.key $PASSIN -out RootCA$LV.crt -subj /C=CN/ST=GS/L=LZ/O=LZUiversity/OU=ETS/CN=RootCA$LV/emailAddress=RootCA$LV@lzu.cn -config openssl.cnf
        openssl ca -ss_cert RootCA$LV.crt -cert ../RootCA$[$LV-1]/RootCA$[$LV-1].pem -keyfile ../RootCA$[$LV-1]/RootCA$[$LV-1].key $PASSIN -config openssl.cnf -policy $POLICY -out RootCA$LV.pem -outdir ./ -extensions v3_ca -batch
    fi
    ((LV=LV+1))
done

((LV=LV-1))
echo
echo "======= creating Server.pem ======="
echo
openssl genrsa $PASSOUT -out Server.key 2048
openssl req -new -x509 -days $DAYS -key Server.key $PASSIN -out Server.crt -subj /C=CN/ST=GS/L=LZ/O=LZUiversity/OU=ETS/CN=Server/emailAddress=RootCA$LV@lzu.cn -config openssl.cnf
openssl ca -ss_cert Server.crt -cert RootCA$LV.pem -keyfile RootCA$LV.key $PASSIN -config openssl.cnf -policy $POLICY -out Server.pem -outdir ./ -batch
echo
echo "======= creating Client.pem ======="
echo
openssl genrsa $PASSOUT -out Client.key 2048
openssl req -new -x509 -days $DAYS -key Client.key $PASSIN -out Client.crt -subj /C=CN/ST=GS/L=LZ/O=LZUiversity/OU=ETS/CN=Client/emailAddress=RootCA$LV@lzu.cn -config openssl.cnf
openssl ca -ss_cert Client.crt -cert RootCA$LV.pem -keyfile RootCA$LV.key $PASSIN -config openssl.cnf -policy $POLICY -out Client.pem -outdir ./  -batch
echo
echo "======= verify Server.pem Client.pem ======="
echo
cp RootCA$LV.pem RootCA$LV.pem.bak
ROOTS=0
while [ $ROOTS -lt $LV ]
do
    cat ../RootCA$ROOTS/RootCA$ROOTS.pem >> RootCA$LV.pem
    ((ROOTS+=1))
done
openssl verify -CAfile RootCA$LV.pem Server.pem Client.pem
echo
echo "======= collect cert ======="
echo
cd ..;mkdir newCert
mv RootCA$LV/Server.key RootCA$LV/Server.pem RootCA$LV/Client.key RootCA$LV/Client.pem RootCA$LV/RootCA$LV.key RootCA$LV/RootCA$LV.pem newCert


echo
echo "======= verify the cert and private key ======="
echo
cd newCert
openssl rsa -modulus -noout -in Server.key | openssl md5
openssl x509 -modulus -noout -in Server.pem | openssl md5
openssl rsa -modulus -noout -in Client.key | openssl md5
openssl x509 -modulus -noout -in Client.pem | openssl md5

#generate pkcs12 for java program
echo
echo "======= generate pkcs12 without chain for java program ======="
echo
openssl pkcs12 -export -in Server.pem -inkey Server.key -name $PKCSNAME $PKCSPASSOUT  -out Server.p12
openssl pkcs12 -export -in Client.pem -inkey Client.key -name $PKCSNAME $PKCSPASSOUT  -out Client.p12

echo
echo "======= generate pkcs12 with chain for java program ======="
echo
openssl pkcs12 -export -chain -CAfile RootCA$LV.pem -in Server.pem -inkey Server.key -name $PKCSNAME $PKCSPASSOUT  -out Server_wc.p12
openssl pkcs12 -export -chain -CAfile RootCA$LV.pem -in Client.pem -inkey Client.key -name $PKCSNAME $PKCSPASSOUT  -out Client_wc.p12
