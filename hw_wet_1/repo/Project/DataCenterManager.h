#include "DataCenter.h"
#include "AVLTree.h"

namespace hw_wet_1
{
	class DataCenterManager
	{
	public:
		DataCenterManager() {}
		~DataCenterManager()
		{
			delete treeSortedByLinux;
			delete treeSortedByWinodws;
		}

		void AddDataCenter(int dataCenterID, int numOfServers)
		{
			DataCenter* dataCenter = new DataCenter(dataCenterID, numOfServers);

			treeSortedById->insert(new Vertex<DataCenter, int>(dataCenter, &dataCenterID));

			Vertex<int, DataCenter>* vertex = new Vertex<int, DataCenter>(&dataCenterID, dataCenter);
			dataCenter->ComapreBy(LINUX);
			treeSortedByLinux->insert(vertex);

			dataCenter->ComapreBy(WINDOWS);
			treeSortedByWinodws->insert(vertex);
		}

		StatusType RemoveDataCenter(int dataCenterID)
		{
			DataCenter& dataCenter = *(treeSortedById->find(&dataCenterID)->data);

			treeSortedByLinux->avlRemove(&dataCenter);
			treeSortedByWinodws->avlRemove(&dataCenter);
			treeSortedById->avlRemove(&dataCenterID);
		}

		StatusType RequestServer(int dataCenterID, int serverID, int os, int *assignedID)
		{
			DataCenter& dataCenter = *(treeSortedById->find(&dataCenterID)->data);
			Server& server = dataCenter.GetServerById(serverID);

			if (server.GetServerOS() != *assignedID)
			{
				if (server.GetServerOS() == LINUX)
				{
					dataCenter.InstallWindows(server);
				}
				if (server.GetServerOS() == WINDOWS)
				{
					dataCenter.InstallLinux(server);
				}
			}
			if (!server.IsServerOccupied())
			{
				server.ChangeServersOccupationStatus();
			}
		}

		StatusType FreeServer(int dataCenterID, int serverID)
		{
			DataCenter& dataCenter = *(treeSortedById->find(&dataCenterID)->data);
			Server& server = dataCenter.GetServerById(serverID);

			if (server.IsServerOccupied())
			{
				server.ChangeServersOccupationStatus();
			}
		}

		StatusType GetDataCentersByOS(int os, int **dataCenters, int* numOfDataCenters)
		{
			AvlTree<int, DataCenter>& tree = *treeSortedByLinux;
			*numOfDataCenters = tree.length;
			int* referenceOfDataCentersOrderedArray = tree.getArrayInOrder();
			for (int i = 0; i < *numOfDataCenters; i++)
			{
				*dataCenters[i] = referenceOfDataCentersOrderedArray[i];
			}
		}

		void Quit(void** DS)
		{
			delete DS;
			DS = NULL;
		}

	private:
		AvlTree<int, DataCenter>* treeSortedByLinux = new AvlTree<int, DataCenter>();
		AvlTree<int, DataCenter>* treeSortedByWinodws = new AvlTree<int, DataCenter>();
		AvlTree<DataCenter, int>* treeSortedById = new AvlTree<DataCenter, int>();
	};
}