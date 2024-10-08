#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "CH446Q.h"
#include "stdbool.h"
#include "stdio.h"
#include "2812_driver.h"

#define NET_ERROR -1
#define NET_OK 1

#define MAX_BRIDGES 255
#define MAX_NODES 80
#define MAX_NETS 80

//ordinary nodes define
#define A_0 0
#define A_1 1
#define A_2 2
#define A_3 3
#define A_4 4
#define A_5 5
#define A_6 6
#define A_7 7

#define B_0 8
#define B_1 9
#define B_2 10
#define B_3 11
#define B_4 12
#define B_5 13
#define B_6 14
#define B_7 15

#define C_0 16
#define C_1 17
#define C_2 18
#define C_3 19
#define C_4 20
#define C_5 21
#define C_6 22
#define C_7 23

#define D_0 24
#define D_1 25
#define D_2 26
#define D_3 27
#define D_4 28
#define D_5 29
#define D_6 30
#define D_7 31

#define E_0 32
#define E_1 33
#define E_2 34
#define E_3 35
#define E_4 36
#define E_5 37
#define E_6 38
#define E_7 39

#define F_0 40
#define F_1 41
#define F_2 42
#define F_3 43
#define F_4 44
#define F_5 45
#define F_6 46
#define F_7 47

#define G_0 48
#define G_1 49
#define G_2 50
#define G_3 51
#define G_4 52
#define G_5 53
#define G_6 54
#define G_7 55

#define H_0 56
#define H_1 57
#define H_2 58
#define H_3 59
#define H_4 60
#define H_5 61
#define H_6 62
#define H_7 63

//special nodes define
#define AD1 64
#define AD2 65

#define DA1 66
#define DA2 67

#define SUPPLY_8V_P 68
#define SUPPLY_8V_N 69
#define SUPPLY_5V_P 70
#define SUPPLY_5V_N 71
#define SUPPLY_3V3  72
#define GND 73

#define ISENSE1_PLUS 74
#define ISENSE1_MINUS 75
#define ISENSE2_PLUS 76
#define ISENSE2_MINUS 77

#define EMPTY_NET 80

typedef struct rgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgbColor;

enum pathType {BBtoBB, BBtoSF};

enum nodeType {BB, SF};

struct pathStruct{

  int node1; //these are the rows or nano header pins to connect
  int node2;
  int net;

  int cur; 

  int chip[4];
  int x[6];
  int y[6];
  int candidates[3][3]; //[node][candidate]

  int skip;
};

struct netStruct{ 

uint8_t number; //nets are uint8_t, nodes are int8_t

const char *name; // human readable "Net 3"

int8_t specialFunction; // store #defined number for that special function -1 for regular net

uint8_t intersections[8]; //if this net shares a node with another net, store this here. If it's a regular net, we'll need a function to just merge them into one new net. special functions can intersect though (except Power and Ground), 0x7f is a reserved empty net that nothing and intersect

int8_t doNotIntersectNets[8]; //if the net tries to share a node with a net that contains any #defined nodes here, it won't connect and throw an error (SUPPLY to GND)

uint8_t occupied; //this isn't implemented - priority = 1 means it will move connections to take the most direct path, priority = 2 means connections will be doubled up when possible, priority = 3 means both
};

struct chipStatus{

int chipNumber;

char chipChar;

int8_t xStatus[16]; //store the bb row or nano conn this is eventually connected to so they can be stacked if conns are redundant

int8_t yStatus[8];  //store the row/nano it's connected to

const int8_t xMap[16];

const int8_t yMap[8];

};

void clearAllConnections();
void initPath();
void printAllPaths();
int checkDoNotIntersect(int net1,int net2);
int addPath(int node1,int node2);
int removePath(int node1,int node2);
void combineNets(int net1,int net2);
void assignNets();
void findStartAndEndChips(int node1, int node2, int pathIdx);
void bridgesToPaths();
void sendAllPaths();
void setLedColors();

#endif