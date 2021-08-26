// Commenting Code
// Use OOP when learned
// Exceptions

#include <iostream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <thread>
#include <fstream>

const std::string dashes{ "-----------------------------------------------------------------------------------------------------------------------" };
const int tolerance{};

void calc_time(float download_size, float download_speed);
float calc_size(float download_time, float download_speed);
void render_screen();
void hidecursor();
void clearScreen();
void option1();
void option2();

int main() {
	int choice{};
	SetConsoleTitle(L"--DownloadMaster Beta by Neolouker--");
	hidecursor();
	system("Color A");
	render_screen();
	std::cout << "(1) Calculate duration of a given download" << std::endl;
	std::cout << "(2) Calculate maximum download size in a given time" << std::endl << std::endl;
	std::cout << "Choice: ";
	std::cin >> choice;
	std::cout << dashes << std::endl << std::endl;

	switch (choice)
	{
	case 1:
		option1();
		break;
	case 2:
		option2();
		break;
	default:
		std::cout << "ERROR Entered wrong number" << std::endl;
		system("pause");
		break;
	}

	return 0;
}

void option1() {
	float download_size{};
	float download_speed{};
	float download_speed_mbit{};

	std::cout << "Enter Download Size in Gigabyte: |	";
	std::cin >> download_size;
	std::cout << "Enter Download Speed in MB/s:    |	";
	std::cin >> download_speed;
	download_speed_mbit = download_speed * 8;
	std::cout << "Your Download Speed in mbit/s:   |	" << download_speed_mbit << std::endl << std::endl;
	std::cout << dashes << std::endl << std::endl;
	calc_time(download_size, download_speed);
	std::cout << dashes << std::endl << std::endl;
	system("pause");
}

void option2() {
	float download_time{};
	float download_speed{};
	float download_speed_mbit{};

	std::cout << "Enter Download Time in Minutes:  |	";
	std::cin >> download_time;
	std::cout << "Enter Download Speed in MB/s:    |	";
	std::cin >> download_speed;
	download_speed_mbit = download_speed * 8;
	std::cout << "Your Download Speed in mbit/s:   |	" << download_speed_mbit << std::endl << std::endl;
	std::cout << dashes << std::endl << std::endl;
	float download_size = calc_size(download_time, download_speed);
	std::cout << "Estimated Download Size in GB:   |	" << download_size << std::endl << std::endl;
	std::cout << dashes << std::endl << std::endl;
	system("pause");
}

void calc_time(float download_size, float download_speed) {	 // Calculation of the download time and the output
	download_speed = download_speed / 1000;	// Transform MB/s into GB/s
	float download_speed_slowed = download_speed - (download_speed * 5 / 100);	// 5% Reduction
	float raw_calc = { download_size / download_speed };
	float raw_calc_tolerance = { download_size / download_speed_slowed };
	int seconds_slowed = static_cast<int>(raw_calc_tolerance);
	int seconds = static_cast<int>(raw_calc);
	std::chrono::seconds seconds_s(seconds_slowed);
	std::chrono::seconds seconds_c(seconds);
	std::cout << "Constant Download Time:  " << std::chrono::duration_cast<std::chrono::hours>(seconds_c).count() << ':'
		<< std::chrono::duration_cast<std::chrono::minutes>(seconds_c).count() % 60 << ':'
		<< seconds_c.count() % 60 << "	| If the actual speed stays unchanged during the download" << std::endl;
	std::cout << "Estimated Download Time: " << std::chrono::duration_cast<std::chrono::hours>(seconds_s).count() << ':'
		<< std::chrono::duration_cast<std::chrono::minutes>(seconds_s).count() % 60 << ':'
		<< seconds_s.count() % 60 << "	| If the actual speed slowes down by 5% during the download  " << std::endl << std::endl;
}

float calc_size(float download_time, float download_speed) {
	download_speed = download_speed / 1000;	// Transform MB/s into GB/s
	download_time = download_time * 60; // Tranform Minutes into Seconds
	return download_speed * download_time;
}

void render_screen() {
	std::string menu_printout[6]{};
	menu_printout[0] = R"(  _____                      _                 _ __  __           _            )";
	menu_printout[1] = R"( |  __ \                    | |               | |  \/  |         | |           )";
	menu_printout[2] = R"( | |  | | _____      ___ __ | | ___   __ _  __| | \  / | __ _ ___| |_ ___ _ __ )";
	menu_printout[3] = R"( | |  | |/ _ \ \ /\ / / '_ \| |/ _ \ / _` |/ _` | |\/| |/ _` / __| __/ _ \ '__|)";
	menu_printout[4] = R"( | |__| | (_) \ V  V /| | | | | (_) | (_| | (_| | |  | | (_| \__ \ ||  __/ |   )";
	menu_printout[5] = R"( |_____/ \___/ \_/\_/ |_| |_|_|\___/ \__,_|\__,_|_|  |_|\__,_|___/\__\___|_|   )";
	for (int i = 0; i < std::size(menu_printout); i++) {
		std::cout << menu_printout[i] << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(375));
	}
	std::cout << dashes << std::endl << std::endl;
}

void hidecursor()
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