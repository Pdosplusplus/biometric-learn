#!/bin/sh

CC=gcc
CXX=g++
SRCS=client.cpp
CLIENT_CFLAGS=`xmlrpc-c-config c++ libwww-client --cflags`
CLIENT_LIBS=`xmlrpc-c-config c++ libwww-client --libs`
OBJS=client.o

g++ $CLIENT_CFLAGS -o $OBJS $SRCS $CLIENT_LIBS

#make clean
#make run
