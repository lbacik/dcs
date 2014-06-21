#!/bin/sh

rm *.o
rm *.a
g++ -g -c ../share/bufor.cc
g++ -g -c readin.cc
ar cr readin.a bufor.o readin.o
ranlib readin.a

