#!/bin/sh

rm *.o
rm *.a
g++ -g -c ../share/lfunc.cc
g++ -g -c insig.cc
g++ -g -c iscas89rozbij.cc
g++ -g -c iscas89Dmg.cc
g++ -g -c parserISCAS89.cc
g++ -g -c debug.cc
ar cr parsery.a lfunc.o iscas89rozbij.o insig.o iscas89Dmg.o \
      parserISCAS89.o debug.o
ranlib parsery.a

