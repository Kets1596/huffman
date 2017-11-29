// CSCI 2530
// Assignment: 6
// Author:     Ketu Patel
// File:       pqueue.h
// Tab stops:  8

// These #ifndef and #define lines make it so that, if this file is
// read more than once by the compiler, its body is skipped on all
// but the first time it is read.

#ifndef PQUEUE_H
#define PQUEUE_H

typedef const char* ItemType;
typedef double      PriorityType;
typedef void 	   (*ItemPrinter)(ItemType);
typedef void 	   (*PriorityPrinter)(PriorityType);

// Forward declaration of PQCell
struct PQCell;

// An object type PriorityQueue represents a pointer.
// The fields are:
//
//	head	a pointer to to a linked list made of PQCells.
//      
struct PriorityQueue
{
	PQCell* head;

	PriorityQueue()
	{
		head = NULL;
	}

};

// Public functions

void remove(PriorityQueue& q, ItemType& x, PriorityType& p);
bool isEmpty(const PriorityQueue &q);
void insert(PriorityQueue& q, ItemType x, PriorityType p);
void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter
      pp);

#endif
