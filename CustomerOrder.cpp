// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 23/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"

using namespace std;

namespace seneca
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const string& line)
	{
		Utilities ut;
		size_t startPos = 0u;
		bool more = true;


		m_name = ut.extractToken(line, startPos, more);
		m_product = ut.extractToken(line, startPos, more);
		size_t currentPos = startPos;

		while (more)
		{
			ut.extractToken(line, startPos, more);
			++m_cntItem;
		}

		m_lstItem = new Item*[m_cntItem];

		more = true;

		for (size_t i = 0; i < m_cntItem && more; ++i)
		{
			m_lstItem[i] = new Item(ut.extractToken(line, currentPos, more));
		}

		if (m_widthField < ut.getFieldWidth())
			m_widthField = ut.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw "Error";
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			delete m_lstItem[i];
		}

		delete[] m_lstItem;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src)noexcept
	{
		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		src.m_cntItem = 0;

		m_lstItem = src.m_lstItem;
		src.m_lstItem = nullptr;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src)noexcept
	{
		if (this != &src)
		{
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];

			delete[] m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0;

			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
		}
		return *this;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool res = true;
		for (size_t i = 0; i < m_cntItem && res; ++i)
		{
			if (!m_lstItem[i]->m_isFilled)
				res = false;
		}
		return res;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool res = true;
		for (size_t i = 0; i < m_cntItem && res; ++i)
		{
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
				res = false;
		}
		return res;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		if (m_lstItem == nullptr) {
			os << "Customer order has no items." << std::endl;
			return;
		}

		for (size_t i = 0; i < m_cntItem; ++i) {
			Item* item = m_lstItem[i];

			if (item->m_itemName == station.getItemName() && !item->m_isFilled) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					item->m_serialNumber = station.getNextSerialNumber();
					item->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << item->m_itemName << "]" << std::endl;
					break;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << item->m_itemName << "]" << std::endl;
				}
			}
		}
	}



	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << setfill('0') << right << setw(6) << m_lstItem[i]->m_serialNumber << "] " << left << setfill(' ') << setw(m_widthField) << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}
}