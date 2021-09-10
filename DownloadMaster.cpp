#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>
#include <thread>
#include <fstream>
#include <ctime>

const std::string DASHES{ "-----------------------------------------------------------------------------------------------------------------------" };
std::string constantTime{};
std::string slowedTime{};

void computeTime(float downloadSize, float downloadSpeed);
float computeSize(float downloadTime, float downloadSpeed);
void renderScreen();
void hideCursor();
void clearScreen();
void option1(int choice, float downloadSize, float downloadSpeed, float downloadSpeedMbit);
void option2(int choice, float downloadTime, float downloadSpeed, float downloadSpeedMbit);
void log(int choice, float downloadSize, float downloadSpeed, float downloadSpeedMbit, std::string constantTime, std::string slowedTime, float downloadTime);

int main() {
	int choice{};
	float downloadSize{};
	float downloadSpeed{};
	float downloadSpeedMbit{};
	float downloadTime{};
	SetConsoleTitle(L"--DownloadMaster Beta by Neolouker--");
	hideCursor();
	system("Color A");
	renderScreen();
	std::cout << "(1) Calculate duration of a given download" << std::endl;
	std::cout << "(2) Calculate maximum download size in a given time" << std::endl << std::endl;
	std::cout << "Choice: ";
	std::cin >> choice;
	std::cout << DASHES << std::endl << std::endl;

	switch (choice)
	{
	case 1:
		option1(choice, downloadSize, downloadSpeed, downloadSpeedMbit);
		break;
	case 2:
		option2(choice, downloadTime, downloadSpeed, downloadSpeedMbit);
		break;
	default:
		std::cout << "ERROR Entered wrong number" << std::endl;
		break;
	}
	system("pause");
	return 0;
}

void option1(int choice, float downloadSize, float downloadSpeed, float downloadSpeedMbit) {
	float download_time{};
	std::cout << "Enter Download Size in Gigabyte: |	";
	std::cin >> downloadSize;
	std::cout << "Enter Download Speed in MB/s:    |	";
	std::cin >> downloadSpeed;
	downloadSpeedMbit = downloadSpeed * 8;
	std::cout << "Your Download Speed in mbit/s:   |	" << downloadSpeedMbit << std::endl << std::endl;
	std::cout << DASHES << std::endl << std::endl;
	computeTime(downloadSize, downloadSpeed);
	std::cout << DASHES << std::endl << std::endl;
	log(choice, downloadSize, downloadSpeed, downloadSpeedMbit, constantTime, slowedTime, download_time);
}

void option2(int choice, float downloadTime, float downloadSpeed, float downloadSpeedMbit) {
	std::cout << "Enter Download Time in Minutes:  |	";
	std::cin >> downloadTime;
	std::cout << "Enter Download Speed in MB/s:    |	";
	std::cin >> downloadSpeed;
	downloadSpeedMbit = downloadSpeed * 8;
	std::cout << "Your Download Speed in mbit/s:   |	" << downloadSpeedMbit << std::endl << std::endl;
	std::cout << DASHES << std::endl << std::endl;
	float downloadSize = computeSize(downloadTime, downloadSpeed);
	std::cout << "Estimated Download Size in GB:   |	" << downloadSize << std::endl << std::endl;
	std::cout << DASHES << std::endl << std::endl;
	log(choice, downloadSize, downloadSpeed, downloadSpeedMbit, constantTime, slowedTime, downloadTime);
}

void computeTime(float downloadSize, float downloadSpeed) {	 // Calculation of the download time and the output
	downloadSpeed = downloadSpeed / 1000;	// Transform MB/s into GB/s
	float slowedDownloadSpeed = downloadSpeed - (downloadSpeed * 5 / 100);	// 5% Reduction
	float rawResult = { downloadSize / downloadSpeed };
	float rawResultDeduction = { downloadSize / slowedDownloadSpeed };
	int slowedSeconds = static_cast<int>(rawResultDeduction);
	int constantSeconds = static_cast<int>(rawResult);
	std::chrono::seconds slowedSecondsChrono(slowedSeconds);
	std::chrono::seconds constantSecondsChrono(constantSeconds);
	constantTime = std::to_string(std::chrono::duration_cast<std::chrono::hours>(constantSecondsChrono).count()) + ':' + std::to_string(std::chrono::duration_cast<std::chrono::minutes>(constantSecondsChrono).count() % 60) + ':' + std::to_string(constantSecondsChrono.count() % 60);
	slowedTime = std::to_string(std::chrono::duration_cast<std::chrono::hours>(slowedSecondsChrono).count()) + ':' + std::to_string(std::chrono::duration_cast<std::chrono::minutes>(slowedSecondsChrono).count() % 60) + ':' + std::to_string(slowedSecondsChrono.count() % 60);
	std::cout << "Constant Download Time:  " << constantTime << "	| If the actual speed stays unchanged during the download" << std::endl;
	std::cout << "Estimated Download Time: " << slowedTime << "	| If the actual speed slowes down by 5% during the download" << std::endl << std::endl;
}

float computeSize(float downloadTime, float downloadSpeed) {
	downloadSpeed = downloadSpeed / 1000;	// Transform MB/s into GB/s
	downloadTime = downloadTime * 60; // Tranform Minutes into Seconds
	return downloadSpeed * downloadTime;
}

void renderScreen() {
	std::string screen[6]{};
	screen[0] = R"(  _____                      _                 _ __  __           _            )";
	screen[1] = R"( |  __ \                    | |               | |  \/  |         | |           )";
	screen[2] = R"( | |  | | _____      ___ __ | | ___   __ _  __| | \  / | __ _ ___| |_ ___ _ __ )";
	screen[3] = R"( | |  | |/ _ \ \ /\ / / '_ \| |/ _ \ / _` |/ _` | |\/| |/ _` / __| __/ _ \ '__|)";
	screen[4] = R"( | |__| | (_) \ V  V /| | | | | (_) | (_| | (_| | |  | | (_| \__ \ ||  __/ |   )";
	screen[5] = R"( |_____/ \___/ \_/\_/ |_| |_|_|\___/ \__,_|\__,_|_|  |_|\__,_|___/\__\___|_|   )";
	for (int i = 0; i < std::size(screen); i++) {
		std::cout << screen[i] << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(350));
	}
	std::cout << DASHES << std::endl << std::endl;
}

void log(int choice, float downloadSize, float downloadSpeed, float downloadSpeedMbit, std::string constantTime, std::string slowedTime, float downloadTime) {
	std::ofstream logfile;
	logfile.open("history.log", std::fstream::app);
	auto start = std::chrono::system_clock::now();
	auto legacyStart = std::chrono::system_clock::to_time_t(start);
	char tmBuff[30];
	ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
	logfile << tmBuff << std::endl;
	logfile << "Choice: " << choice << std::endl;
	logfile << "Download Size: " << downloadSize << std::endl;
	logfile << "Download Speed MB/s: " << downloadSpeed << std::endl;
	logfile << "Download Speed mbit/s: " << downloadSpeedMbit << std::endl;
	if (choice == 1) {
		logfile << "Constant Time: " << constantTime << std::endl;
		logfile << "Estimated Time: " << slowedTime << std::endl << std::endl;
	}
	else {
		logfile << "Entered Time: " << downloadTime << std::endl << std::endl;
	}
	logfile.close();
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void clearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;	//Get the number of cells in the current buffer
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(	// Fill the entire buffer with spaces
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	if (!FillConsoleOutputAttribute(	//Fill the entire buffer with the current colors and attributes
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	SetConsoleCursorPosition(hStdOut, homeCoords);	// Move the cursor home
}