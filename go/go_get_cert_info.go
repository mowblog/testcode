package main

import (
   "crypto/x509"
   "encoding/pem"
   "fmt"
   "io/ioutil"
)

func main() {

    certFile,err := ioutil.ReadFile("test.pem") 
    if err != nil {
	fmt.Println(err.Error())
    }

    pemBlock, _ := pem.Decode([]byte(certFile))
    if pemBlock == nil {
	    fmt.Println("decode error")
    }

    cert,err := x509.ParseCertificate(pemBlock.Bytes)
    if err != nil {
	fmt.Println(err.Error())
    }

    fmt.Printf("Name %s\n", cert.Subject.CommonName)
    fmt.Printf("Not before %s\n", cert.NotBefore.String())
    fmt.Printf("Not after %s\n", cert.NotAfter.String())
}
