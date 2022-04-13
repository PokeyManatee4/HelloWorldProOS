#include <stddef.h>
#include <stdint.h>
 
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
// By default, the VGA textmode buffer has a size of 80x25 characters
const int VGA_COLS = 80;
const int VGA_ROWS = 25;
 
// We start displaying text in the top-left of the screen (column = 0, row = 0)
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F; // Black background, White foreground
 
// This function initiates the terminal by clearing it
void term_init()
{
	// Clear the textmode buffer
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			// The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
			// Given this, we find an index into the buffer for our character
			const size_t index = (VGA_COLS * row) + col;
			// Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
			// - B is the background color
			// - F is the foreground color
			// - C is the ASCII character
			vga_buffer[index] = ((uint16_t)term_color << 8) | ' '; // Set the character to blank (a space character)
		}
	}
}
 
// This function places a single character onto the screen
void term_putc(char c)
{
	// Remember - we don't want to display ALL characters!
	switch (c)
	{
	case '\n':
		{
			term_col = 0;
			term_row ++;
			break;
		}
 
	default: // Normal characters just get displayed and then increment the column
		{
			const size_t index = (VGA_COLS * term_row) + term_col; // Like before, calculate the buffer index
			vga_buffer[index] = ((uint16_t)term_color << 8) | c;
			term_col ++;
			break;
		}
	}
 
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		term_row ++;
	}

	if (term_row >= VGA_ROWS)
	{
		term_col = 0;
		term_row = 0;
	}
}
 
void term_print(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; i ++) // Keep placing characters until we hit the null-terminating character ('\0')
		term_putc(str[i]);
}
 
 
 
// This is our kernel's main function
eextern "C" void kernel_main()
{
	term_init();
 
	term_print("\n");
	term_print(" Welcome to\n");
	term_print(" _     _  ______  _       _       ______     ______________     ______________\n");
	term_print("| |   | ||  ____|| |     | |     |  __  |   /              \\   /              \\\n");
	term_print("| |___| || |____ | |     | |     | |  | |  /    _________   \\ /    ___________/\n");
	term_print("|  ___  ||  ____|| |     | |     | |  | |  |   |         |  | |   |\n");
	term_print("| |   | || |____ | |____ | |____ | |__| |  |   |         |  | |   | \n");       
	term_print("|_|   |_||______||______||______||______|  |   |         |  | |   |___________\n");        
	term_print(" _     _  ______  _____   _       _____    |   |         |  | \\               \\\n");
	term_print("| | _ | ||  __  ||  _  | | |     |  __ \\   |   |         |  |  \\___________   |\n");
	term_print("| |/ \\| || |  | || |_| | | |     | |  | |  |   |         |  |              |  |\n");
	term_print("|       || |  | ||     | | |     | |  | |  |   |_________|  |  ____________|  |\n");
	term_print("|  /\\   || |__| || |\\  \\ | |____ | |  | |  \\                / /               /\n");
	term_print("|_/  \\__||______||_| \\__\\|______||_____/    \\______________/  \\______________/\n");
	term_print("\n                                                    Pro Version 1.0.0\n");
}
