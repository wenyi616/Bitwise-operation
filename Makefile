#
# Assignment: Bit Twiddling
# Class: CSC 252 Spring 2017
#
# TAs: Sayak Chakraborti (schakr11@cs.rochester.edu)
#      Kevin Gerami(kgerami@u.rochester.edu)
#
# Makefile for bits.c and tests.c.
#

CC = gcc
CFLAGS = -O -Wall -m32
LIBS =

all: tests

tests: tests.c bits.h
	$(CC) $(CFLAGS) $(LIBS) -o tests tests.c bits.c

clean:
	rm -f *.o tests *~
