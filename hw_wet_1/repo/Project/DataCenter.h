#include "LinkedList.h"
namespace hw_wet_1 {

	template<class T, class U>
	class DataCenter {
		DataCenter();
		virtual ~DataCenter();
	private:
		int NumberOfServers();
		int NumberOfLinuxServers();
		int NumberOfWindowsServers();
		int AddServer();
		int GetServerById();
		int InstallLinux();
		int InstallWindows();
		int SetServerAsOccupied();
		int IsServerOccupied();

	//private:
	//	int id;
	//	LinkedList linux;
	//	LinkedList windows;
	//	int* Servers;
	//	int numberOfLinuxServers;
	//	int numberOfWindowsServers;
	};

}