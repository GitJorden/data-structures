#include "DataCenter.h"

namespace hw_wet_1
{
	int DataCenter::NumberOfServers()
	{
		return linux->GetListLength() + windows->GetListLength();
	}

	int DataCenter::NumberOfLinuxServers() const
	{
		return linux->GetListLength();
	}

	int DataCenter::NumberOfWindowsServers() const
	{
		return windows->GetListLength();
	}

	void DataCenter::RemoveServerFromList(Server& s)
	{
		Node<Server>& serversIterator = this->linux->GetHead();
		int length = NumberOfLinuxServers();
		if (s.GetServerOS() != LINUX)
		{
			serversIterator = this->windows->GetHead();
			length = NumberOfWindowsServers();
		}

		for (int i = 0; i < length; i++)
		{
			if (serversIterator.data.GetServerId() == s.GetServerId())
			{
				windows->DeleteNodeAndSaveTheData(serversIterator);
			}
			serversIterator = *serversIterator.next;
		}
	}

	void DataCenter::AddServerToListOfOS(Server& s)
	{
		if (s.GetServerOS() == LINUX)
		{
			this->linux->CreateNewNodeFromHead(s);
		}
		else
		{
			this->windows->CreateNewNodeFromHead(s);
		}
	}

	void DataCenter::InstallLinux(Server& s)
	{
		s.SetServerOS(LINUX);
		linux->CreateNewNodeFromHead(s);

		Node<Server>& serversIterator = this->windows->GetHead();
		for (int i = 0; i < this->NumberOfWindowsServers(); i++)
		{
			if (serversIterator.data.GetServerId() == s.GetServerId())
			{
				windows->DeleteNode(serversIterator);
			}
			serversIterator = *serversIterator.next;
		}
	}

	void DataCenter::InstallWindows(Server& s)
	{
		s.SetServerOS(WINDOWS);
		windows->CreateNewNodeFromHead(s);

		Node<Server>& serversIterator = this->linux->GetHead();
		for (int i = 0; i < this->NumberOfLinuxServers(); i++)
		{
			if (serversIterator.data.GetServerId() == s.GetServerId())
			{
				linux->DeleteNode(serversIterator);
			}
			serversIterator = *serversIterator.next;
		}
	}

	Server& DataCenter::GetServerById(int serverId)
	{
		Node<Server>& s = this->linux->GetHead();
		for (int i = 0; i < this->NumberOfLinuxServers(); i++)
		{
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
		for (int i = 0; i < this->NumberOfWindowsServers(); i++)
		{
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

	void DataCenter::ComapreBy(OS os)
	{
		this->_compareByLinuxOrWindows = os;
		if (this->_compareByLinuxOrWindows == WINDOWS)
		{
			this->_numberOfServersToComapre = NumberOfWindowsServers();
		}
		else
		{
			this->_numberOfServersToComapre = NumberOfLinuxServers();
		}
	}

	int DataCenter::NumberOfServersToComapre() const
	{
		return this->_numberOfServersToComapre;
	}

	void DataCenter::SetServerAsOccupied(Server& s)
	{
		if (!s.IsServerOccupied())
		{
			s.ChangeServersOccupationStatus();
		}

		RemoveServerFromList(s);
	}
}