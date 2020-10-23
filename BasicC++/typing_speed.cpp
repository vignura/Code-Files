#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>

#define TEXT_SIZE			(4 * 1024)
#define CHARS_PER_WORD		5
using namespace std;

char text[TEXT_SIZE];

int main(int argc, char const *argv[])
{
	double time = 0;
	double speed_wpm = 0;
	double words  = 0;

	cout << "Typing speed calculator\n";
	
	clock_t start = clock();
	gets(text);
	time = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	words = (strlen(text) / CHARS_PER_WORD);
	speed_wpm = (words / time) * 60;
	cout << "words typed: "  << words << " time: " << time << "sec" << endl;
	cout << "Speed: " << speed_wpm << " wpm" << " @ " << CHARS_PER_WORD << " cpw" << endl;

	return 0;
}
