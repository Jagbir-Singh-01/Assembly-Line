// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 05/04/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Workstation.h"

namespace seneca 
{
	std::deque<CustomerOrder>g_pending;
	std::deque<CustomerOrder>g_completed;
	std::deque<CustomerOrder>g_incomplete;

	Workstation::Workstation(const std::string str) : Station(str) {}

	void Workstation::fill(std::ostream& os) 
	{
		if (!m_orders.empty()) 
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() 
	{
		bool moved = false;
		if (!m_orders.empty()) 
		{
			if (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName())) {
				if (m_pNextStation) {
					*m_pNextStation += std::move(m_orders.front());
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(std::move(m_orders.front()));
					}
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
					}
				}
				m_orders.pop_front();
				moved = true;
			}
		}
		return moved;
	}

	void Workstation::setNextStation(Workstation* station) 
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << (this)->getItemName() << " --> ";
		(m_pNextStation) ? (os << m_pNextStation->getItemName()) : (os << "End of Line");
		os << "\n";
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) 
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}