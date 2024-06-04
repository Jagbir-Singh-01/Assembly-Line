// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 05/04/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include <vector>
#include "Workstation.h"

namespace seneca 
{
	class LineManager 
	{
	private:
		std::vector<Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder{0};
		Workstation* m_firstStation{nullptr};

	public:
		LineManager() = default;
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os = std::cout);
		void display(std::ostream& os = std::cout) const;
	};
}
#endif