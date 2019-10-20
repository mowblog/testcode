#!/bin/bash

CERT_PATH=/home/jma/IdeaProjects/javassl/cert

cd out/production/javassl

java -Djavax.net.ssl.trustStore=${CERT_PATH}/trustStore.p12\
 -Djavax.net.ssl.trustStorePassword=Aa123456\
 -Djavax.net.ssl.keyStore=${CERT_PATH}/Server.p12\
 -Djavax.net.ssl.keyStorePassword=Aa123456\
 -Djavax.net.debug=ssl\
 SSLServer