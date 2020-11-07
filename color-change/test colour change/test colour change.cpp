// test colour change.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <lowlevelmonitorconfigurationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <bitset>

#pragma comment(lib, "Dxva2.lib")

int main()
{

	DWORD cb = 0;
	DWORD minb = 0;
	DWORD maxb = 0;
	DWORD numMonitors;

	DWORD monitorCapabilites;
	DWORD supportColourTemps;

	MC_COLOR_TEMPERATURE curTemp;

	LPPHYSICAL_MONITOR physicalMonitors = NULL;
	HMONITOR hmonitor = MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY);
	BOOL gotMonitors = GetNumberOfPhysicalMonitorsFromHMONITOR(hmonitor, &numMonitors);

	if (gotMonitors) {

		physicalMonitors = (LPPHYSICAL_MONITOR)malloc(numMonitors * sizeof(PHYSICAL_MONITOR));

		if (physicalMonitors != NULL) {

			gotMonitors = GetPhysicalMonitorsFromHMONITOR(hmonitor, numMonitors, physicalMonitors);

			HANDLE working = physicalMonitors[0].hPhysicalMonitor;

			#pragma region use mointors

			GetMonitorCapabilities(working, &monitorCapabilites, &supportColourTemps);
			std::cout << std::bitset<13>(monitorCapabilites).to_string() << "\n";
			std::cout << std::bitset<9>(supportColourTemps).to_string() << "\n";

			//GetMonitorBrightness(working, &minb, &cb, &maxb);
			GetMonitorColorTemperature(working, &curTemp);
			std::cout << "Tempature: " << curTemp;
			//SetMonitorColorTemperature(working, MC_COLOR_TEMPERATURE_10000K);

			//SetMonitorBrightness(working, 25);
			//Sleep(3000);
			//SetMonitorBrightness(working, 75);
			//SetMonitorColorTemperature(working, curTemp);

			#pragma endregion

			gotMonitors = DestroyPhysicalMonitors(numMonitors, physicalMonitors);
			free(physicalMonitors);
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


