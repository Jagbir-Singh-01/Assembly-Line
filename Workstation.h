// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 05/04/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca 
{
	extern std::deque<CustomerOrder>g_pending;
	extern std::deque<CustomerOrder>g_completed;
	extern std::deque<CustomerOrder>g_incomplete;

	class Workstation :public Station 
	{
	private:
		std::deque<CustomerOrder>m_orders;
		Workstation* m_pNextStation{ nullptr };

	public:
		Workstation() = default;
		Workstation(const std::string str);
		Workstation(const Workstation& src) = delete;
		Workstation& operator=(const Workstation& src) = delete;
		Workstation(Workstation&& src) = delete;
		Workstation operator=(Workstation&& src) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station=nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}
#endif
