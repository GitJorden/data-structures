#include "Server.h"
#include "DoublyLinkedList.h"

namespace hw_wet_1
{
	class DataCenter
	{
	public:
		DataCenter(int id, int numberOfServers)
			:id(id)
		{
			this->Servers = new Server[numberOfServers];

			for (int i = 0; i < numberOfServers; i++)
			{
				Server* s = new Server(i);
				linux->CreateNewNodeFromHead(*s);
				Servers[i] = *s;
			}
		};

		virtual ~DataCenter()
		{
			delete linux;
			delete windows;
		}

		int GetDataCenterId() const { return this->id; }
		void InstallLinux(Server& s);
		void InstallWindows(Server& s);
		void SetServerAsOccupied(Server& s);
		Server& GetServerById(int serverId);
		void ComapreBy(OS os);
		int NumberOfServersToComapre() const;

		///Operator overloading
		bool operator==(const DataCenter& rightDataCenter) const
		{
			if (this->id == rightDataCenter.id)
			{
				return true;
			}

			return false;
		}

		bool operator==(int comparedId) const
		{
			if (this->id == comparedId)
			{
				return true;
			}

			return false;
		}

		bool operator>(const DataCenter& rightDataCenter) const
		{
			if (this->NumberOfServersToComapre() > rightDataCenter.NumberOfServersToComapre())
			{
				return true;
			}
			else
			{
				if (this->NumberOfServersToComapre() == rightDataCenter.NumberOfServersToComapre())
				{
					if (this->id > rightDataCenter.id)
					{
						return true;
					}
				}

				return false;
			}
		}

		bool operator<(const DataCenter& rightDataCenter) const
		{
			if (this->NumberOfServersToComapre() < rightDataCenter.NumberOfServersToComapre())
			{
				return true;
			}
			else
			{
				if (this->NumberOfServersToComapre() == rightDataCenter.NumberOfServersToComapre())
				{
					if (this->id < rightDataCenter.id)
					{
						return true;
					}
				}

				return false;
			}
		}

	private:

		int NumberOfServers();
		int NumberOfLinuxServers() const;
		int NumberOfWindowsServers() const;

		void AddServerToListOfOS(Server& s);
		void RemoveServerFromList(Server& s);

	private:
		int id;
		DoublyLinkedList<Server>* linux = new DoublyLinkedList<Server>();
		DoublyLinkedList<Server>* windows = new DoublyLinkedList<Server>();

		Server* Servers;

		OS _compareByLinuxOrWindows = LINUX;
		int	_numberOfServersToComapre = NumberOfLinuxServers();
	};
}