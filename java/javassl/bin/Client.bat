rem https://docs.oracle.com/javase/7/docs/technotes/guides/security/jsse/JSSERefGuide.html#SSLParameters

java  -Djavax.net.ssl.trustStore=D:/ssl/ClientTrust.p12 -Djavax.net.ssl.trustStorePassword=Aa123456 -Dcom.sun.net.ssl.checkRevocation=true  SSLClient

rem  -Djavax.net.ssl.keyStore=D:/ssl/Client.p12 -Djavax.net.ssl.keyStorePassword=Aa123456 -Djavax.net.debug=ssl

pause