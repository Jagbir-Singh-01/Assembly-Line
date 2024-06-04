// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <iomanip>
#include "Utilities.h"

namespace seneca
{
	class Station
	{
		size_t m_id = 0;
		std::string m_name = "";
		std::string m_description = "";
		size_t m_serialNumber = 0;
		size_t m_stock = 0;

		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station() = default;
		Station(const std::string& line);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif