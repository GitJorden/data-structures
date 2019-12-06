#include "DataCenter.h"

namespace hw_wet_1 {
	int DataCenter::NumberOfServers()
	{
		return this->numberOfLinuxServers + this->numberOfWindowsServers;
	}

	int DataCenter::NumberOfLinuxServers()
	{
		return this->numberOfLinuxServers;
	}

	int DataCenter::NumberOfWindowsServers()
	{
		return this->numberOfLinuxServers;
	}

	void DataCenter::InstallLinux(Server& s)
	{
		s.SetServerOS(LINUX);
		linux->CreateNewNodeFromHead(s);

		Node<Server>& serversIterator = this->windows->GetHead();
		for (int i = 0; i < this->numberOfWindowsServers; i++) {
			if (serversIterator.data.GetServerId() == s.GetServerId())
			{
				linux->DeleteNode(serversIterator);
			}
			serversIterator = *serversIterator.next;
		}
	}

	void DataCenter::InstallWindows(Server& s)
	{
		s.SetServerOS(WINDOWS);
		windows->CreateNewNodeFromHead(s);

		Node<Server>& serversIterator = this->linux->GetHead();
		for (int i = 0; i < this->numberOfLinuxServers; i++) {
			if (serversIterator.data.GetServerId() == s.GetServerId())
			{
				windows->DeleteNode(serversIterator);
			}
			serversIterator = *serversIterator.next;
		}
	}

	Server& DataCenter::GetServerById(int serverId)
	{
		Node<Server>& s = this->linux->GetHead();
		for (int i = 0; i < this->numberOfLinuxServers; i++) {
			if (serverId != s.data.GetServerId())
			{
				s = *s.next;
				continue;
			}
			else
			{
				break;
			}
		}

		s = windows->GetHead();
		for (int i = 0; i < this->numberOfWindowsServers; i++) {
			if (serverId != s.data.GetServerId())
			{
				s = *s.next;
				continue;
			}
			else
			{
				break;
			}
		}

		return s.data;
	}

	void DataCenter::SetServerAsOccupied(Server& s)
	{
		if (!s.IsServerOccupied())
		{
			s.ChangeServersOccupationStatus();
		}
	}
}