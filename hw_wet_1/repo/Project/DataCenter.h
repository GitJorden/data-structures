#include "Server.h"
#include "DoublyLinkedList.h"


namespace hw_wet_1 {
	class DataCenter {
	public:
		DataCenter(int id, int numberOfLinuxServers)
			:id(id), numberOfLinuxServers(numberOfLinuxServers) {

			for (int i = 0; i < this->numberOfLinuxServers; i++) {
				Server* s = new Server(i);
				linux->CreateNewNodeFromHead(*s);
			}
		};

		virtual ~DataCenter()
		{
			delete linux;
			delete windows;
		}

	private:
		int NumberOfServers();
		int NumberOfLinuxServers();
		int NumberOfWindowsServers();
		Server& GetServerById(int serverId);

		void InstallLinux(Server& s);
		void InstallWindows(Server& s);
		void SetServerAsOccupied(Server& s);

	private:
		int id;
		DoublyLinkedList<Server>* linux = new DoublyLinkedList<Server>();
		DoublyLinkedList<Server>* windows = new DoublyLinkedList<Server>();

		int* Servers;
		int numberOfLinuxServers = 0;
		int numberOfWindowsServers = 0;
	};
}