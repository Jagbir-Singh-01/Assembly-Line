// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <string>
#include <iostream>

namespace seneca
{
	class Utilities
	{
		size_t m_widthField = 1;
		static char m_delimiter;

		static std::string trim(const std::string& str);

	public:
		Utilities() = default;
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}

#endif