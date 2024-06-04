// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 12/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

using namespace std;

namespace seneca
{
	char Utilities::m_delimiter = '\n';

	string Utilities::trim(const string& str)
	{
		size_t start = 0;
		size_t end = str.length() - 1;

		while (start <= end && isspace(str[start]))
		{
			start++;
		}

		while (end > start && isspace(str[end]))
		{
			end--;
		}

		return str.substr(start, (end - start + 1));
	}


	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
	{
		string temp = "";

		if (str[next_pos] == m_delimiter)
		{
			more = false;
			throw "ERROR: No token.";
		}


		while (next_pos < str.length() && str[next_pos] == m_delimiter) {
			next_pos++;
		}

		if (next_pos == str.length()) {
			more = false;
			return temp;
		}

		size_t end_pos = str.find(m_delimiter, next_pos);
		if (end_pos == string::npos) {
			end_pos = str.length();
		}

		temp = trim(str.substr(next_pos, end_pos - next_pos));

		next_pos = end_pos + 1;
		more = (next_pos < str.length());

		if (m_widthField < temp.length()) {
			m_widthField = temp.length();
		}

		return temp;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}