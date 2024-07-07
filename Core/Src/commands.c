#include "commands.h"

extern float mA;
extern int16_t raw;

static void connect(int argc, char**argv)
{
    if(argc < 2)
    {
        rt_kprintf("Illegal param\n");
        return;
    }

    RST_Set();

    addPath(atoi(argv[1]),atoi(argv[2]));
    
    assignNets();
    bridgesToPaths();
    printAllPaths();

    RST_Clr();

    sendAllPaths();
}
MSH_CMD_EXPORT(connect, connect sample: connect <from|to>);

static void disconnect(int argc, char**argv)
{
    if(argc < 2)
    {
        rt_kprintf("Illegal param\n");
        return;
    }
    RST_Set();

    removePath(atoi(argv[1]),atoi(argv[2]));
    
    assignNets();
    bridgesToPaths();
    printAllPaths();

    RST_Clr();

    sendAllPaths();
}
MSH_CMD_EXPORT(disconnect, connect sample: disconnect <from|to>);

static void disconnectAll(int argc, char**argv)
{
    clearAllConnections();
    FromOSclearAllconnections();
    rt_kprintf("All connections cleared!\n");
}
MSH_CMD_EXPORT(disconnectAll, disconnectAll sample: disconnectAll);

static void getCurrent(int argc, char**argv)
{
    rt_kprintf("I = %d uA\n",(int)(mA*1000));
    //rt_kprintf("Raw = %d\n",raw);
}
MSH_CMD_EXPORT(getCurrent, getCurrent sample: getCurent);