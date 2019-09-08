#!/bin/sh
rm *.exe
#all: tcpc tcps udpc udps
#tcpc: tcpc.cpp
	g++ -static -o tcpc tcpc.cpp -lws2_32
#tcps: tcps.cpp
	g++ -static -o tcps tcps.cpp -lws2_32
#udpc: udpc.cpp
	g++ -static -o udpc udpc.cpp -lws2_32
#udps: udps.cpp
	g++ -static -o udps udps.cpp -lws2_32

