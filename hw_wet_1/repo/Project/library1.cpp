#include "library1.h"
#include "DataCenterManager.h"

void * Init()
{
	return nullptr;
}

StatusType AddDataCenter(void * DS, int dataCenterID, int numOfServers)
{
	return StatusType();
}

StatusType RemoveDataCenter(void * DS, int dataCenterID)
{
	return StatusType();
}

StatusType RequestServer(void * DS, int dataCenterID, int serverID, int os, int * assignedID)
{
	return StatusType();
}

StatusType FreeServer(void * DS, int dataCenterID, int serverID)
{
	return StatusType();
}

StatusType GetDataCentersByOS(void * DS, int os, int ** dataCenters, int * numOfDataCenters)
{
	return StatusType();
}

void Quit(void ** DS)
{
}
