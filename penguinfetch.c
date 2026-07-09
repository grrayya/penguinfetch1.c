#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#include <getopt.h>

#define MAX_S 15
#define BUF_S 256
#define PAD "                   " // 19 spaces

const char *art_c[] = {
    "      \033[1;30m.---\033[0m.      ",
    "     \033[1;30m/\033[1;37m ^ ^ \033[1;30m\\\033[0m     ",
    "    \033[1;30m|\033[1;37m  \033[1;33m(>)\033[1;37m  \033[1;30m|\033[0m    ",
    "    \033[1;30m|\033[1;37m \033[1;35mo   o\033[1;37m \033[1;30m|\033[0m    ",
    "     \033[1;30m\\\033[1;37m '-'\033[1;30m /\033[0m     ",
    "   \033[1;30m___|     |___\033[0m   ",
    "  \033[1;30m/\033[1;37m  _       _  \033[1;30m\\\033[0m  ",
    " \033[1;30m|\033[1;37m  | |     | |  \033[1;30m|\033[0m ",
    " \033[1;30m\\\033[1;37m  \\_\033[1;33m|_   _|\033[1;37m_/  \033[1;30m/\033[0m ",
    "  \033[1;30m'---. \033[1;33m'-'\033[1;30m .---'\033[0m  ",
    "       \033[1;33m'---'\033[0m       "
};

const char *art_p[] = {
    "      .---.      ",
    "     / ^ ^ \\     ",
    "    |  (>)  |    ",
    "    | o   o |    ",
    "     \\ '-' /     ",
    "   ___|     |___   ",
    "  /  _       _  \\  ",
    " |  | |     | |  | ",
    " \\  \\_|_   _|_/  / ",
    "  '---. '-' .---'  ",
    "       '---'       "
};

void build_stats(char st[][BUF_S], int *n, int clr) {
    const char *c = clr ? "\033[1;36m" : "";
    const char *r = clr ? "\033[0m" : "";

    struct utsname ut; uname(&ut);
    struct sysinfo si; sysinfo(&si);
    struct passwd *pw = getpwuid(getuid());
    const char *usr = pw ? pw->pw_name : "user";
    
    int hlen = strlen(usr) + 1 + strlen(ut.nodename);
    if (hlen >= BUF_S) hlen = BUF_S - 1;
    
    char sep[BUF_S] = {0};
    memset(sep, '-', hlen);

    long up_m = si.uptime / 60;
    unsigned long ram_u = (si.totalram - si.freeram) / 1024 / 1024;
    unsigned long ram_t = si.totalram / 1024 / 1024;
    long cpus = sysconf(_SC_NPROCESSORS_ONLN);
    char *sh = getenv("SHELL");

    snprintf(st[(*n)++], BUF_S, "%s%s%s@%s%s%s", c, usr, r, c, ut.nodename, r);
    snprintf(st[(*n)++], BUF_S, "%s", sep);
    snprintf(st[(*n)++], BUF_S, "%sOS:%s %s", c, r, ut.sysname);
    snprintf(st[(*n)++], BUF_S, "%sKernel:%s %s", c, r, ut.release);
    snprintf(st[(*n)++], BUF_S, "%sUptime:%s %ldh %ldm", c, r, up_m / 60, up_m % 60);
    snprintf(st[(*n)++], BUF_S, "%sRAM:%s %lu / %lu MB", c, r, ram_u, ram_t);
    snprintf(st[(*n)++], BUF_S, "%sCPU:%s %ld cores", c, r, cpus);
    if (sh) snprintf(st[(*n)++], BUF_S, "%sShell:%s %s", c, r, sh);
}

void print_out(char st[][BUF_S], int n, int art, int clr) {
    int max = (11 > n && art) ? 11 : n;
    putchar('\n');
    
    for (int i = 0; i < max; i++) {
        if (art) {
            if (i < 11) printf("%s   ", clr ? art_c[i] : art_p[i]);
            else printf("%s   ", PAD);
        }
        if (i < n) printf("%s", st[i]);
        putchar('\n');
    }
    putchar('\n');
}

int main(int argc, char **argv) {
    int clr = isatty(STDOUT_FILENO);
    int art = 1;
    int opt;

    while ((opt = getopt(argc, argv, "ca")) != -1) {
        if (opt == 'c') clr = 0; // -c: disable colors
        if (opt == 'a') art = 0; // -a: disable ascii art
    }

    char st[MAX_S][BUF_S];
    int n = 0;
    
    build_stats(st, &n, clr);
    print_out(st, n, art, clr);

    return 0;
}
