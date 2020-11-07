// test colour change.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <lowlevelmonitorconfigurationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <bitset>
#include <string>

#pragma comment(lib, "Dxva2.lib")


// MMC = min max current
struct MMC {

	DWORD min;
	DWORD max;
	DWORD cur;

	std::string toString() {
		return "(min = " + std::to_string(min) + ", cur = " + std::to_string(cur) + ", max = " + std::to_string(max) + ")";
	}
};

struct MonitorRBG {
	MMC red;
	MMC green;
	MMC blue;

	std::string toString() {
		return "(" + std::to_string(red.cur) + "," + std::to_string(green.cur) + "," + std::to_string(blue.cur) + ")";
	}
};

struct RBG {

	DWORD r;
	DWORD g;
	DWORD b;
};

MonitorRBG GetMonitorRBGGain(HANDLE handle) {

	MonitorRBG out = {};

	DWORD n = 0;
	
	GetMonitorRedGreenOrBlueGain(handle, MC_RED_GAIN, &out.red.min, &out.red.cur, &out.red.max);
	GetMonitorRedGreenOrBlueGain(handle, MC_GREEN_GAIN, &out.green.min, &out.green.cur, &out.green.max);
	GetMonitorRedGreenOrBlueGain(handle, MC_BLUE_GAIN, &out.blue.min, &out.blue.cur, &out.blue.max);

	return out;
}

void SetMonitorRBGGain(HANDLE handle, RBG newValues) {

	SetMonitorRedGreenOrBlueGain(handle, MC_RED_GAIN, newValues.r);
	SetMonitorRedGreenOrBlueGain(handle, MC_RED_GAIN, newValues.g);
	SetMonitorRedGreenOrBlueGain(handle, MC_RED_GAIN, newValues.b);
}

int main()
{

	DWORD cb = 0;
	DWORD minb = 0;
	DWORD maxb = 0;
	DWORD numMonitors;

	MC_COLOR_TEMPERATURE curTemp;

	LPPHYSICAL_MONITOR physicalMonitors = NULL;
	HMONITOR hmonitor = MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY);
	BOOL gotMonitors = GetNumberOfPhysicalMonitorsFromHMONITOR(hmonitor, &numMonitors);

	if (gotMonitors) {

		physicalMonitors = (LPPHYSICAL_MONITOR)malloc(numMonitors * sizeof(PHYSICAL_MONITOR));

		if (physicalMonitors != NULL) {

			gotMonitors = GetPhysicalMonitorsFromHMONITOR(hmonitor, numMonitors, physicalMonitors);

			HANDLE working = physicalMonitors[0].hPhysicalMonitor;

			#pragma region check support

			DWORD monitorCapabilites;
			DWORD supportColourTemps;
			GetMonitorCapabilities(working, &monitorCapabilites, &supportColourTemps);

			std::cout << "Supports Nothing: " << bool(monitorCapabilites & MC_CAPS_NONE) << std::endl;
			std::cout << "Supports RGB Drive: " << bool(monitorCapabilites & MC_CAPS_RED_GREEN_BLUE_DRIVE) << std::endl;
			std::cout << "Supports RGB Gain: " << bool(monitorCapabilites & MC_CAPS_RED_GREEN_BLUE_GAIN) << std::endl;
			std::cout << "Supports Colour Tempature: " << bool(monitorCapabilites & MC_CAPS_COLOR_TEMPERATURE) << std::endl;
			std::cout << "Supports Brightness: " << bool(monitorCapabilites & MC_CAPS_BRIGHTNESS) << std::endl;
			std::cout << "Supports Contrast: " << bool(monitorCapabilites & MC_CAPS_CONTRAST) << std::endl;

			#pragma endregion


			#pragma region use mointors

			/*MonitorRBG monitorRBG = GetMonitorRBG(working);

			std::cout << "RGB: " << monitorRBG.toString() << std::endl;

			Sleep(3000);
			SetMonitorRBG(working, RBG{ 10, 5, 5 });

			MonitorRBG newRBG = GetMonitorRBG(working);
			std::cout << "RGB: " << newRBG.toString() << std::endl;

			Sleep(3000);
			SetMonitorRBG(working, RBG{ 5, 5, 5 });*/

			//std::cout << std::bitset<13>(monitorCapabilites).to_string() << "\n";
			//std::cout << std::bitset<9>(supportColourTemps).to_string() << "\n";

			//GetMonitorBrightness(working, &minb, &cb, &maxb);
			//GetMonitorColorTemperature(working, &curTemp);
			//std::cout << "Tempature: " << curTemp;
			//SetMonitorColorTemperature(working, MC_COLOR_TEMPERATURE_10000K);

			//SetMonitorBrightness(working, 25);
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


