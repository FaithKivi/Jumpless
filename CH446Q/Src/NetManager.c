#include "NetManager.h"

struct pathStruct path[MAX_BRIDGES + 2]; //this is the array of paths

struct netStruct net[MAX_NETS] = { //these are the special function nets that will always be made
//netNumber,       ,netName          ,specialFunction        ,intsctNet[] ,doNotIntersectNodes[]                 ,occupied
    {     81       ,"Empty Net"      ,EMPTY_NET              ,{}          ,{EMPTY_NET,EMPTY_NET,EMPTY_NET,EMPTY_NET,EMPTY_NET,EMPTY_NET,EMPTY_NET} , 1},     
    {     1        ,"GND"            ,GND                    ,{}          ,{SUPPLY_8V_P,SUPPLY_8V_N,SUPPLY_5V_P,SUPPLY_5V_N,SUPPLY_3V3,DA1,DA2}    , 1},
    {     2        ,"+8V"            ,SUPPLY_8V_P            ,{}          ,{GND,SUPPLY_8V_N,SUPPLY_5V_P,SUPPLY_5V_N,SUPPLY_3V3,DA1,DA2}            , 1},
    {     3        ,"-8V"            ,SUPPLY_8V_N            ,{}          ,{GND,SUPPLY_8V_P,SUPPLY_5V_P,SUPPLY_5V_N,SUPPLY_3V3,DA1,DA2}            , 1},
    {     4        ,"+5V"            ,SUPPLY_5V_P            ,{}          ,{GND,SUPPLY_5V_N,SUPPLY_8V_P,SUPPLY_8V_N,SUPPLY_3V3,DA1,DA2}            , 1},
    {     5        ,"-5V"            ,SUPPLY_5V_N            ,{}          ,{GND,SUPPLY_5V_P,SUPPLY_8V_P,SUPPLY_8V_N,SUPPLY_3V3,DA1,DA2}            , 1},
    {     6        ,"+3.3V"          ,SUPPLY_3V3             ,{}          ,{GND,SUPPLY_8V_P,SUPPLY_8V_N,SUPPLY_5V_P,SUPPLY_5V_N,DA1,DA2}           , 1},
    {     7        ,"DAC 1"          ,DA1                    ,{}          ,{GND,SUPPLY_8V_P,SUPPLY_8V_N,SUPPLY_5V_P,SUPPLY_5V_N,SUPPLY_3V3,DA2}    , 1},
    {     8        ,"DAC 2"          ,DA2                    ,{}          ,{GND,SUPPLY_8V_P,SUPPLY_8V_N,SUPPLY_5V_P,SUPPLY_5V_N,SUPPLY_3V3,DA1}    , 1},
    {     9        ,"ADC 1"          ,AD1                    ,{}          ,{}                                   , 1},
    {     10       ,"ADC 2"          ,AD2                    ,{}          ,{}                                   , 1},
    {     11       ,"I Sense1 +"     ,ISENSE1_PLUS           ,{}          ,{ISENSE1_MINUS}                      , 1},
    {     12       ,"I Sense1 -"     ,ISENSE1_MINUS          ,{}          ,{ISENSE1_PLUS}                       , 1},
    {     13       ,"I Sense2 +"     ,ISENSE2_PLUS           ,{}          ,{ISENSE2_MINUS}                      , 1},
    {     14       ,"I Sense2 -"     ,ISENSE2_MINUS          ,{}          ,{ISENSE2_PLUS}                       , 1},
};

int nodeStatus[MAX_NODES] = {[GND]           = 1, 
                             [SUPPLY_8V_P]   = 2, 
                             [SUPPLY_8V_N]   = 3, 
                             [SUPPLY_5V_P]   = 4, 
                             [SUPPLY_5V_N]   = 5,
                             [SUPPLY_3V3]    = 6,
                             [DA1]           = 7,
                             [DA2]           = 8,
                             [AD1]           = 9,
                             [AD2]           = 10,
                             [ISENSE1_PLUS]  = 11,
                             [ISENSE1_MINUS] = 12,
                             [ISENSE2_PLUS]  = 13,
                             [ISENSE2_MINUS] = 14 
                             };

const int nodesToChip[64] = {           
CHIP_A,CHIP_A,CHIP_A,CHIP_A,CHIP_A,CHIP_A,CHIP_A,CHIP_A,
CHIP_B,CHIP_B,CHIP_B,CHIP_B,CHIP_B,CHIP_B,CHIP_B,CHIP_B,
CHIP_C,CHIP_C,CHIP_C,CHIP_C,CHIP_C,CHIP_C,CHIP_C,CHIP_C,
CHIP_D,CHIP_D,CHIP_D,CHIP_D,CHIP_D,CHIP_D,CHIP_D,CHIP_D,                                   
CHIP_E,CHIP_E,CHIP_E,CHIP_E,CHIP_E,CHIP_E,CHIP_E,CHIP_E,
CHIP_F,CHIP_F,CHIP_F,CHIP_F,CHIP_F,CHIP_F,CHIP_F,CHIP_F,
CHIP_G,CHIP_G,CHIP_G,CHIP_G,CHIP_G,CHIP_G,CHIP_G,CHIP_G,
CHIP_H,CHIP_H,CHIP_H,CHIP_H,CHIP_H,CHIP_H,CHIP_H,CHIP_H};

struct chipStatus ch[12] = {
  {CHIP_A,'A',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_I, CHIP_J, CHIP_B, CHIP_B, CHIP_C, CHIP_C, CHIP_D, CHIP_D, CHIP_E, CHIP_E, CHIP_F, CHIP_F, CHIP_G, CHIP_G, CHIP_H, CHIP_H},//X MAP constant
  {A_0, A_1, A_2, A_3, A_4, A_5, A_6, A_7}},  // Y MAP constant

  {CHIP_B,'B',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_A, CHIP_A, CHIP_I, CHIP_J, CHIP_C, CHIP_C, CHIP_D, CHIP_D, CHIP_E, CHIP_E, CHIP_F, CHIP_F, CHIP_G, CHIP_G, CHIP_H, CHIP_H},
  {B_0, B_1, B_2, B_3, B_4, B_5, B_6, B_7}},//yMap

  {CHIP_C,'C',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_A, CHIP_A, CHIP_B, CHIP_B, CHIP_I, CHIP_J, CHIP_D, CHIP_D, CHIP_E, CHIP_E, CHIP_F, CHIP_F, CHIP_G, CHIP_G, CHIP_H, CHIP_H},
  {C_0, C_1, C_2, C_3, C_4, C_5, C_6, C_7}},

  {CHIP_D,'D',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_A, CHIP_A, CHIP_B, CHIP_B, CHIP_C, CHIP_C, CHIP_I, CHIP_J, CHIP_E, CHIP_E, CHIP_F, CHIP_F, CHIP_G, CHIP_G, CHIP_H, CHIP_H},
  {D_0, D_1, D_2, D_3, D_4, D_5, D_6, D_7}},

  {CHIP_E,'E',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_A, CHIP_A, CHIP_B, CHIP_B, CHIP_C, CHIP_C, CHIP_D, CHIP_D, CHIP_I, CHIP_J, CHIP_F, CHIP_F, CHIP_G, CHIP_G, CHIP_H, CHIP_H},
  {E_0, E_1, E_2, E_3, E_4, E_5, E_6, E_7}},

  {CHIP_F,'F',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_A, CHIP_A, CHIP_B, CHIP_B, CHIP_C, CHIP_C, CHIP_D, CHIP_D, CHIP_E, CHIP_E, CHIP_I, CHIP_J, CHIP_G, CHIP_G, CHIP_H, CHIP_H},
  {F_0, F_1, F_2, F_3, F_4, F_5, F_6, F_7}},

  {CHIP_G,'G',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_A, CHIP_A, CHIP_B, CHIP_B, CHIP_C, CHIP_C, CHIP_D, CHIP_D, CHIP_E, CHIP_E, CHIP_F, CHIP_F, CHIP_I, CHIP_J, CHIP_H, CHIP_H},
  {G_0, G_1, G_2, G_3, G_4, G_5, G_6, G_7}},

  {CHIP_H,'H',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {CHIP_A, CHIP_A, CHIP_B, CHIP_B, CHIP_C, CHIP_C, CHIP_D, CHIP_D, CHIP_E, CHIP_E, CHIP_F, CHIP_F, CHIP_G, CHIP_G, CHIP_I, CHIP_J},
  {H_0, H_1, H_2, H_3, H_4, H_5, H_6, H_7}},

  {CHIP_I,'I',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {AD1, AD2, DA1, DA2, SUPPLY_8V_P, SUPPLY_8V_N, SUPPLY_5V_P, SUPPLY_5V_N, SUPPLY_3V3, GND, ISENSE1_PLUS, ISENSE1_MINUS, ISENSE2_PLUS, ISENSE2_MINUS, EMPTY_NET, EMPTY_NET},
  {CHIP_A,CHIP_B,CHIP_C,CHIP_D,CHIP_E,CHIP_F,CHIP_G,CHIP_H}},

  {CHIP_J,'J',
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // x status
  {-1,-1,-1,-1,-1,-1,-1,-1}, //y status
  {AD1, AD2, DA1, DA2, SUPPLY_8V_P, SUPPLY_8V_N, SUPPLY_5V_P, SUPPLY_5V_N, SUPPLY_3V3, GND, ISENSE1_PLUS, ISENSE1_MINUS, ISENSE2_PLUS, ISENSE2_MINUS, EMPTY_NET, EMPTY_NET},
  {CHIP_A,CHIP_B,CHIP_C,CHIP_D,CHIP_E,CHIP_F,CHIP_G,CHIP_H}}
};

static void nodeExchange(int *node1,int *node2)
{
    int temp;
    temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void clearAllConnections()
{
    int i,j;
    
    for(i = 0; i < MAX_BRIDGES; i++)
    {
        path[i].net = 0;

        for(j = 0; j < 4; j++)
        {
            path[i].chip[j] = -1;
        }

        for(j = 0; j < 6; j++)
        {
            path[i].x[j] = 0;
            path[i].y[j] = 0;
        }
    }
		for(i = 0; i<10; i++)
		{
			for(j = 0; j < 16; j++)
			{
				ch[i].xStatus[j] = -1;
			}
			for(j = 0; j < 8; j++)
			{
				ch[i].yStatus[j] = -1;
			}
		}
		for(i = 0; i < AD1; i++)
		{
			nodeStatus[i] = 0;
		}
		for(i = 15; i < MAX_NETS; i++)
		{
			net[i].occupied = 0;
		}
    initPath();   
}

void initPath()
{
    int i;

    for(i = 0;i < MAX_BRIDGES; i++)//initialize all nodes
    {
        path[i].node1 = -1;
        path[i].node2 = -1;
        path[i].net = 0;
        path[i].cur = i + 1;
    }
    
    path[MAX_BRIDGES].cur = 0;//tail of backup list
    path[MAX_BRIDGES + 1].cur = 0;//head of data list
}

void printAllPaths()
{
    int searchIndex,i;

    searchIndex = path[MAX_BRIDGES + 1].cur;
    if(searchIndex == 0) return;
    for(i = 0; i < MAX_BRIDGES; i++)
    {
        rt_kprintf("connecting %d to %d in net %d, switching on %d-%d-%d and %d-%d-%d\n",path[searchIndex].node1,
                                                                           path[searchIndex].node2,
                                                                           path[searchIndex].net,
                                                                           path[searchIndex].chip[0],
                                                                           path[searchIndex].x[0],
                                                                           path[searchIndex].y[0],
                                                                           path[searchIndex].chip[1],
                                                                           path[searchIndex].x[1],
                                                                           path[searchIndex].y[1]);
        if(path[searchIndex].cur <= 0) break;
        searchIndex = path[searchIndex].cur;
    }
}

int addPath(int node1,int node2)
{
    int freeNodeIndex,searchIndex,i;

    if(node1 == node2) return NET_ERROR;
    else if(node1 > node2) nodeExchange(&node1,&node2);//make sure that node2 is greater than node1

    //check if the path already exists
    searchIndex = path[MAX_BRIDGES + 1].cur;
    for(i = 0; i < MAX_BRIDGES; i++)
    {
        if(path[searchIndex].node1 == node1 && path[searchIndex].node2 == node2) return NET_ERROR;
        if(path[searchIndex].cur <= 0) break;
        searchIndex = path[searchIndex].cur;
    }

    //get a free node    
    freeNodeIndex = path[0].cur;
    if(freeNodeIndex > 0) path[0].cur = path[freeNodeIndex].cur;
    else return NET_ERROR;//no space left

    path[freeNodeIndex].node1 = node1;
    path[freeNodeIndex].node2 = node2;
    path[freeNodeIndex].cur = path[MAX_BRIDGES + 1].cur;
    path[MAX_BRIDGES + 1].cur = freeNodeIndex;

    return NET_OK;
}

int removePath(int node1,int node2)
{
    int searchIndex,deleteIndex,i;

    if(node1 == node2) return NET_ERROR;
    else if(node1 > node2) nodeExchange(&node1,&node2);//make sure that node2 is greater than node1

    //search for the path to remove
    searchIndex = MAX_BRIDGES + 1;
    deleteIndex = path[searchIndex].cur;
    if(deleteIndex == 0) return NET_ERROR;
    for(i = 0; i < MAX_BRIDGES; i++)
    {
        if(path[searchIndex].cur <= 0) return NET_ERROR;//path not found
        if(path[deleteIndex].node1 == node1 && path[deleteIndex].node2 == node2) break;
        
        searchIndex = path[searchIndex].cur;
        deleteIndex = path[searchIndex].cur;
    }

    path[deleteIndex].node1 = -1;
    path[deleteIndex].node2 = -1;
    path[deleteIndex].net = 0;

    //update the data list
    path[searchIndex].cur = path[deleteIndex].cur;

    //add the free node to backup list
    path[deleteIndex].cur = path[0].cur;
    path[0].cur = deleteIndex;

    return NET_OK;
}

void combineNets(int net1,int net2)
{
    int i;
    for(i = 0; i < MAX_NODES; i++)
    {
        if(nodeStatus[i] == net2) nodeStatus[i] = net1;
    }
    net[net2].occupied = 0;
}

void assignNets()
{
    int i,searchIndex,netIndex;
    int newNode1,newNode2;
    
    searchIndex = path[MAX_BRIDGES + 1].cur;
    if(searchIndex == 0) return;
    for(i = 0; i < MAX_BRIDGES; i++)
    {
        newNode1 = path[searchIndex].node1;
        newNode2 = path[searchIndex].node2;

        //error checking    
        if(newNode1 < 0 || newNode1 < 0)
        {
            path[searchIndex].net = -1;
            continue;
        }
        
        if(nodeStatus[newNode1] == nodeStatus[newNode2] && nodeStatus[newNode1] > 0)//in the same net
        {
            path[searchIndex].net = nodeStatus[newNode1];        
        }
        else if(nodeStatus[newNode1] > 0 && nodeStatus[newNode2] > 0 && nodeStatus[newNode1] != nodeStatus[newNode2])//in different nets
        {
            if(nodeStatus[newNode1] <= 14 && nodeStatus[newNode2] <= 14)//not combining special nets
            { 
                path[searchIndex].net = 0;    
                continue;
            }
            else if(nodeStatus[newNode2] <= 14) combineNets(nodeStatus[newNode2],nodeStatus[newNode1]);
            else combineNets(nodeStatus[newNode1],nodeStatus[newNode2]);

            path[searchIndex].net = nodeStatus[newNode1]; 
        }
        else if(nodeStatus[newNode1] > 0)//node 1 already in a net
        {
            nodeStatus[newNode2] = nodeStatus[newNode1];
            path[searchIndex].net = nodeStatus[newNode1];    
        }
        else if(nodeStatus[newNode2] > 0)//node 2 already in a net
        {
            nodeStatus[newNode1] = nodeStatus[newNode2];
            path[searchIndex].net = nodeStatus[newNode2];    
        }
        else//neither node is in a net 
        {
            for(netIndex = 0; netIndex < MAX_NETS; netIndex++)//search for a free net
            {
                if(!net[netIndex].occupied) break;
            }

            net[netIndex].occupied = 1;
            nodeStatus[newNode1] = netIndex;
            nodeStatus[newNode2] = netIndex;
            path[searchIndex].net = netIndex;
        }

        if(path[searchIndex].cur <= 0) break;
        searchIndex = path[searchIndex].cur;
    }
}

void findStartAndEndChips(int node1, int node2, int pathIdx)
{
    static int twice;
    static int bothNodes[2];
    
    bothNodes[0] = node1;
    bothNodes[1] = node2;

    for (int twice = 0; twice < 2; twice++) // first run gets node1 and start chip, second is node2 and end
    {
       if(bothNodes[twice] <= H_7) path[pathIdx].chip[twice] = nodesToChip[bothNodes[twice]];//ordinary nodes
       else 
       {
            path[pathIdx].candidates[twice][0] = CHIP_I;
            path[pathIdx].candidates[twice][1] = CHIP_J;
       }
    }
}

int xMapForNode(int node, int chip)
{
    int nodeFound = -1;
    for (int i = 0; i < 16; i++)
    {
        if (ch[chip].xMap[i] == node)
        {
            nodeFound = i;
            break;
        }
    }

    return nodeFound;
}

int yMapForNode(int node, int chip)
{
    int nodeFound = -1;
    for (int i = 0; i < 8; i++)
    {
        if (ch[chip].yMap[i] == node)
        {
            nodeFound = i;
            break;
        }
    }
    return nodeFound;
}

int xMapForChipLane0(int chip1, int chip2)
{
    int nodeFound = -1;
    for (int i = 0; i < 16; i++)
    {
        if (ch[chip1].xMap[i] == chip2)
        {
            nodeFound = i;
            break;
        }
    }
    return nodeFound;
}

int xMapForChipLane1(int chip1, int chip2)
{
    int nodeFound = -1;
    for (int i = 0; i < 16; i++)
    {
        if (ch[chip1].xMap[i] == chip2)
        {
            if (ch[chip1].xMap[i + 1] == chip2)
            {
                nodeFound = i + 1;
                break;
            }
        }
    }
    return nodeFound;
}

void bridgesToPaths()
{
    int searchIndex,i,j;
    int xMapL0c0,xMapL1c0,xMapL0c1,xMapL1c1;
    int sameChipPaths[MAX_BRIDGES],sameChipIndex = 0;
    searchIndex = path[MAX_BRIDGES + 1].cur;
		if(searchIndex == 0) return;
    for(i = 0; i < MAX_BRIDGES; i++)
    {
        findStartAndEndChips(path[searchIndex].node1, path[searchIndex].node2, searchIndex);
        if(path[searchIndex].candidates[1][0] <= 0)
        {
            xMapL0c0 = xMapForChipLane0(path[searchIndex].chip[0], path[searchIndex].chip[1]);
            xMapL1c0 = xMapForChipLane1(path[searchIndex].chip[0], path[searchIndex].chip[1]);
            xMapL0c1 = xMapForChipLane0(path[searchIndex].chip[1], path[searchIndex].chip[0]);
            xMapL1c1 = xMapForChipLane1(path[searchIndex].chip[1], path[searchIndex].chip[0]);

            if(path[searchIndex].chip[0] == path[searchIndex].chip[1])//on the same chip
            {
                path[searchIndex].x[0] = -2;
                path[searchIndex].x[1] = -2;

                sameChipPaths[sameChipIndex] = searchIndex;
                sameChipIndex ++;
            }
            else
            {
                if ((xMapL1c0 != -1) && (ch[path[searchIndex].chip[0]].xStatus[xMapL1c0] == path[searchIndex].net || ch[path[searchIndex].chip[0]].xStatus[xMapL1c0] == -1)) // check if lane 1 shares a net first so it should prefer sharing lanes
                {
                    ch[path[searchIndex].chip[0]].xStatus[xMapL1c0] = path[searchIndex].net;
                    ch[path[searchIndex].chip[1]].xStatus[xMapL1c1] = path[searchIndex].net;

                    path[searchIndex].x[0] = xMapL1c0;
                    path[searchIndex].x[1] = xMapL1c1;
                }
                else if ((xMapL0c0 != -1) && (ch[path[searchIndex].chip[0]].xStatus[xMapL0c0] == path[searchIndex].net || ch[path[searchIndex].chip[0]].xStatus[xMapL0c0] == -1)) // lanes will alway be taken together, so only check chip 1
                {
                    ch[path[searchIndex].chip[0]].xStatus[xMapL0c0] = path[searchIndex].net;
                    ch[path[searchIndex].chip[1]].xStatus[xMapL0c1] = path[searchIndex].net;

                    path[searchIndex].x[0] = xMapL0c0;
                    path[searchIndex].x[1] = xMapL0c1;
                }
                else
                {

                }
            }
            path[searchIndex].y[0] = yMapForNode(path[searchIndex].node1, path[searchIndex].chip[0]);
            path[searchIndex].y[1] = yMapForNode(path[searchIndex].node2, path[searchIndex].chip[1]);

            ch[path[searchIndex].chip[0]].yStatus[path[searchIndex].y[0]] = path[searchIndex].net;
            ch[path[searchIndex].chip[1]].yStatus[path[searchIndex].y[1]] = path[searchIndex].net;
        }
        else
        {
            xMapL0c0 = xMapForChipLane0(path[searchIndex].chip[0], path[searchIndex].candidates[1][0]);
            xMapL1c0 = xMapForChipLane0(path[searchIndex].chip[0], path[searchIndex].candidates[1][1]);
            xMapL0c1 = xMapForNode(path[searchIndex].node2, CHIP_I);
            xMapL1c1 = xMapForNode(path[searchIndex].node2, CHIP_J);

            if ((xMapL1c0 != -1) && (ch[path[searchIndex].chip[0]].xStatus[xMapL1c0] == path[searchIndex].net || ch[path[searchIndex].chip[0]].xStatus[xMapL1c0] == -1))
            {
                path[searchIndex].chip[1] = CHIP_J;    

                ch[path[searchIndex].chip[0]].xStatus[xMapL1c0] = path[searchIndex].net;
                ch[path[searchIndex].candidates[1][1]].xStatus[xMapL1c1] = path[searchIndex].net;

                path[searchIndex].x[0] = xMapL1c0;
                path[searchIndex].x[1] = xMapL1c1;

                path[searchIndex].y[0] = yMapForNode(path[searchIndex].node1, path[searchIndex].chip[0]);
                path[searchIndex].y[1] = path[searchIndex].chip[0];

                ch[path[searchIndex].chip[0]].yStatus[path[searchIndex].y[0]] = path[searchIndex].net;
                ch[path[searchIndex].candidates[1][1]].yStatus[path[searchIndex].y[1]] = path[searchIndex].net;
            }
            else if ((xMapL0c0 != -1) && (ch[path[searchIndex].chip[0]].xStatus[xMapL0c0] == path[searchIndex].net || ch[path[searchIndex].chip[0]].xStatus[xMapL0c0] == -1))
            {
                path[searchIndex].chip[1] = CHIP_I; 

                ch[path[searchIndex].chip[0]].xStatus[xMapL0c0] = path[searchIndex].net;
                ch[path[searchIndex].candidates[1][0]].xStatus[xMapL0c1] = path[searchIndex].net;

                path[searchIndex].x[0] = xMapL0c0;
                path[searchIndex].x[1] = xMapL0c1;

                path[searchIndex].y[0] = yMapForNode(path[searchIndex].node1, path[searchIndex].chip[0]);
                path[searchIndex].y[1] = path[searchIndex].chip[0];

                ch[path[searchIndex].chip[0]].yStatus[path[searchIndex].y[0]] = path[searchIndex].net;
                ch[path[searchIndex].candidates[1][0]].yStatus[path[searchIndex].y[1]] = path[searchIndex].net;
            }
            else
            {

            }
            path[searchIndex].candidates[1][0] = -1;
            path[searchIndex].candidates[1][1] = -1;
        }

        if(path[searchIndex].cur <= 0) break;
        searchIndex = path[searchIndex].cur;
    }

    for(i = 0;i < sameChipIndex; i++)
    {
        for(j = 0; j < 16; j++)
        {
            if(ch[path[sameChipPaths[i]].chip[0]].xStatus[j] <= 0 || ch[path[sameChipPaths[i]].chip[0]].xStatus[j] == path[sameChipPaths[i]].net)
            {
                ch[path[sameChipPaths[i]].chip[0]].xStatus[j] = path[sameChipPaths[i]].net;

                path[sameChipPaths[i]].x[0] = j;
                path[sameChipPaths[i]].x[1] = j;
                break;
            }
        }
    }
}

void sendAllPaths()
{
    int searchIndex,i;

    searchIndex = path[MAX_BRIDGES + 1].cur;
    if(searchIndex == 0) return;
    for(i = 0; i < MAX_BRIDGES; i++)
    {
        sendXYraw(path[searchIndex].chip[0],path[searchIndex].x[0],path[searchIndex].y[0],1);
        sendXYraw(path[searchIndex].chip[1],path[searchIndex].x[1],path[searchIndex].y[1],1);

        if(path[searchIndex].cur <= 0) break;
        searchIndex = path[searchIndex].cur;
    }
}