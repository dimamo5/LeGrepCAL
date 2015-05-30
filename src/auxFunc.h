#include <windows.h>

/**< Macros de cores para usar no menu */
#define BLACK 0  // 0000
#define BLUE 1   // 0001
#define GREEN 2  // 0010
#define AQUA 3   // 0011
#define RED 4    // 0100        ----> MSB is the intensity and 3 LSB are the colors
#define PURPLE 5 // 0101
#define YELLOW 6 // 0110       Windows API has 8 bits for colors, 4 for the background and
#define WHITE 7  // 0111       then 4 for the foreground
#define GRAY 8   // 1000
#define LIGHT_GREEN 10 // 1010  -> GREEN with intensity at 1
#define LIGHT_RED 12  // 1100  -> RED with intensity at 1

void cor(int background, int foreground) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foreground + 16 * background);
}
