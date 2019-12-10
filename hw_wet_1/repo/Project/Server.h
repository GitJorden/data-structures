#include <iostream>

namespace hw_wet_1
{
	enum OS
	{
		LINUX = 0,
		WINDOWS = 1
	};

	class Server
	{
	public:
		Server() {}
		Server(int id)
			:id(id)
		{
			this->os = LINUX;
			this->isOccupied = false;
		}

		int GetServerId() { return this->id; }
		OS GetServerOS() { return this->os; }
		void SetServerOS(OS os) { this->os = os; }
		bool IsServerOccupied() { return this->isOccupied; }
		void ChangeServersOccupationStatus() { this->isOccupied = !this->isOccupied; }

	private:
		int id;
		OS os;
		bool isOccupied;
	};
}