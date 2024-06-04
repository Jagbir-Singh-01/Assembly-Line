// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

using namespace std;

namespace seneca
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& line)
	{
		Utilities ut;
		size_t start_pos = 0u;
		bool more = true;

		m_id = ++id_generator;
		m_name = ut.extractToken(line, start_pos, more);
		m_serialNumber = stoi(ut.extractToken(line, start_pos, more));
		m_stock = stoi(ut.extractToken(line, start_pos, more));

		if (m_widthField < ut.getFieldWidth())
		{
			m_widthField = ut.getFieldWidth();
		}

		m_description = ut.extractToken(line, start_pos, more);
	}

	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return m_stock;
	}

	void Station::updateQuantity()
	{
		if (m_stock > 0)
		{
			m_stock--;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		if (full)
		{
			os << setfill('0') << setw(3) << right << m_id << " | " << setfill(' ') << left << setw(m_widthField) << m_name << " | " << right << setfill('0') << setw(6) << m_serialNumber << " | " << setfill(' ') << setw(4) << m_stock << " | " << m_description << endl;
		}
		else
		{
			os << setfill('0') << setw(3) << right << m_id << " | " << setfill(' ') << left << setw(m_widthField) << m_name << " | " << right << setfill('0') << setw(6) << m_serialNumber << " | " << endl;
		}
	}
}