#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

// We define our custom ASCII penguin as an array of strings.
// This makes it much easier to print it line-by-line next to our stats.
const char *penguin_ascii[] = {
    "       .---.       ",
    "      /     \\      ",
    "     | O   O |     ",
    "     |   >   |     ",
    "     \\ '---' /     ",
    "   ___|     |___   ",
    "  /  _       _  \\  ",
    " |  | |     | |  | ",
    " \\  \\_|_   _|_/  / ",
    "  '---. '-' .---'  ",
    "       '---'       "
};
const int penguin_height = 11;

int main() {
    // The utsname struct holds system information
    struct utsname sys_info;

    // uname() returns 0 on success, non-zero on failure
    if (uname(&sys_info) != 0) {
        perror("uname error"); // Print error to standard error
        return EXIT_FAILURE;   // Exit safely
    }

    // We'll prepare an array to hold our system stats as strings
    // We format them using snprintf for safe memory handling
    char stats[5][256];
    snprintf(stats[0], sizeof(stats[0]), "\033[1;36mOS:\033[0m %s", sys_info.sysname);
    snprintf(stats[1], sizeof(stats[1]), "\033[1;36mRelease:\033[0m %s", sys_info.release);
    snprintf(stats[2], sizeof(stats[2]), "\033[1;36mVersion:\033[0m %s", sys_info.version);
    snprintf(stats[3], sizeof(stats[3]), "\033[1;36mMachine:\033[0m %s", sys_info.machine);
    snprintf(stats[4], sizeof(stats[4]), "\033[1;36mNode:\033[0m %s", sys_info.nodename);
    
    int stats_count = 5;

    printf("\n"); // Give it some breathing room at the top

    // The tricky part: printing the ASCII art side-by-side with the stats.
    // We loop through whichever is taller (the penguin or the stats list).
    int max_lines = (penguin_height > stats_count) ? penguin_height : stats_count;

    for (int i = 0; i < max_lines; i++) {
        // Print the penguin line if it exists
        if (i < penguin_height) {
            printf("%s", penguin_ascii[i]);
        } else {
            // Print padding spaces if the penguin is out of lines but stats remain
            printf("                   "); 
        }

        // Print some spacing between the art and the text
        printf("   "); 

        // Print the stat line if it exists
        if (i < stats_count) {
            printf("%s", stats[i]);
        }

        // Move to the next line
        printf("\n");
    }

    printf("\n"); // Breathing room at the bottom
    return EXIT_SUCCESS;
}
