/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library1.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1
#define _234218_WET1

#ifdef __cplusplus
extern "C" {
#endif

	/* Return Values
	 * ----------------------------------- */
	typedef enum {
		SUCCESS = 0,
		FAILURE = -1,
		ALLOCATION_ERROR = -2,
		INVALID_INPUT = -3
	} StatusType;


	void *Init()
	{
		return 0;
	}

	StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers)
	{
		return SUCCESS;
	}

	StatusType RemoveDataCenter(void *DS, int dataCenterID)
	{
		return SUCCESS;
	}

	StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID)
	{
		return SUCCESS;
	}

	StatusType FreeServer(void *DS, int dataCenterID, int serverID)
	{
		return SUCCESS;
	}

	StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters)
	{
		return SUCCESS;
	}

	void Quit(void** DS)
	{
		int a = 0;
	}

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1 */
