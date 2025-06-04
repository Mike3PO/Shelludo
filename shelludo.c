#include "shelludo-helper.h"

int main(int argc, char **argv) {
    char line[MAXCOM];
    char* args[MAXLIST];
    char* args_piped[MAXLIST];
    int exec_flag= 0;

    shelludo_init();

    while (1) {
        /* Print directory */
        print_dir();
        if (shelludo_read(line))
            continue;
        exec_flag= shelludo_process(line, args, args_piped);

        if (exec_flag == 1)
            shelludo_exec(args);

        if (exec_flag == 2)
            shelludo_exec_piped(args, args_piped);
    }

    return 0;
}