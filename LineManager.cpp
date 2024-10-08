// Name: Jagbir Singh
// Seneca Student ID: 144019221
// Seneca email: jagbir-singh1@myseneca.ca
// Date of completion: 05/04/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <vector>
#include <algorithm>
#include <fstream>
#include "Station.h"
#include "Utilities.h"
#include "LineManager.h"

using namespace std;
namespace seneca
{
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations)
	{
		try
		{
			ifstream in(file);
			m_cntCustomerOrder = g_pending.size();
			while (in)
			{
				Utilities ut;
				bool more{ true };
				size_t pos{};
				string str{};
				string first{};
				string next{};

				getline(in, str);
				first = ut.extractToken(str, pos, more);
				if (more)
					next = ut.extractToken(str, pos, more);

				for_each(stations.begin(), stations.end(), [&](Workstation* firstWorkstation)
					{
						if (firstWorkstation->getItemName() == first)
						{
							for_each(stations.begin(), stations.end(), [&](Workstation* nextWorkstation)
								{
									if (nextWorkstation->getItemName() == next)
										firstWorkstation->setNextStation(nextWorkstation);
								});
							m_activeLine.push_back(firstWorkstation);
						} });

				m_firstStation = m_activeLine.front();
			}
		}
		catch (...)
		{
			throw "ERROR: LineManager Constructor";
		}
	}

	void LineManager::reorderStations()
	{
		vector<Workstation*> tempVec;
		Workstation* tempWorkstation{ nullptr };
		size_t cnt{};
		while (cnt < m_activeLine.size())
		{
			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workstation)
				{ if (workstation->getNextStation() == tempWorkstation)
			{
				tempVec.push_back(workstation);
				tempWorkstation = workstation;
				cnt++;
			} });
		}
		reverse(tempVec.begin(), tempVec.end());
		m_firstStation = tempVec[0];
		m_activeLine = tempVec;
	}

	bool LineManager::run(ostream& os)
	{
		static size_t cnt{};
		os << "Line Manager Iteration: " << ++cnt << endl;

		if (!g_pending.empty())
		{
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}

		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workstation)
			{ workstation->fill(os); });

		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workstation)
			{ workstation->attemptToMoveOrder(); });

		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
	}

	void LineManager::display(ostream& os) const
	{
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workstation)
			{ workstation->display(os); });
	}
}