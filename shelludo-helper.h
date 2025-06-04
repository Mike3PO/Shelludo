#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#include "man-helper.h"

#define MAXCOM 1024 /* Max number of letters supported */
#define MAXLIST 100 /* Max number of commands supported */
#define CMDS_SUPPORTED 10 /* Number of custom commands */

/* Color Codes */

/* Foreground */
#define BLK "\e[30m"
#define RED "\e[31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define BLU "\e[34m"
#define MAG "\e[35m"
#define CYN "\e[36m"
#define WHT "\e[37m"

/* Background */
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

#define CRESET "\e[0m"

#define clear() printf("\033[2J\033[H")

void print_color(char* color) {
    printf("%s", color);
    clear();
}

void print_testudo() {
    
    printf("\n\n\n");
    printf("\t\t            /^\\\n");
    printf("\t\t           |   |\n");
    printf("\t\t     /\\     |_|     /\\\n");
    printf("\t\t     | \\___/\' `\\___/ |\n");
    printf("\t\t      \\_/  \\___/  \\_/\n");
    printf("\t\t       |\\__/   \\__/|");
    printf("\t<- Testudo for good luck\n");
    printf("\t\t       |/  \\___/  \\|\n");
    printf("\t\t      ./\\__/   \\__/\\,\n");
    printf("\t\t      | /  \\___/  \\ |\n");
    printf("\t\t      \\/     V     \\/\n");

}

void load_preset() {
    FILE* fptr;
    fptr= fopen("color-data", "r");
    char line[50];
    fgets(line, 50, fptr);
    print_color(line);
    fgets(line, 50, fptr);
    print_color(line);
}

void shelludo_init() {
    char* username= getenv("USER");

    load_preset();
    
    printf("\n************************************************************");
    printf("\n\n\n\t\t   Welcome to Shelludo!!!");
    printf("\n\n\n\t\t  A shell for UMD students");
    
    /* Print out the testudo ASCII art*/
    print_testudo();

    printf("\n\n\n\t       Made by Michael Kittredge 2025");
    
    printf("\n\n\nUSER is: @%s", username);
    printf("\n************************************************************");
    sleep(3);
    clear();
}

int shelludo_read(char *line) {
    char *buf;

    buf = readline("\n>>> ");

    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(line, buf);
        return 0;
    } else {
        return 1;
    }
}

int print_dir() {
    char cwd[MAXCOM];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

void shelludo_exec(char** args) {
    // Fork a child
    pid_t pid = fork();

    if (pid > 0) {
        wait(NULL); /* Only one child, so this works */
        return;
    } else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            printf("\nFailed to execute command...");
        }
        /* Reaching here means something catastrophic happened */
        exit(0);
    } else if (pid == -1) {
        printf("\nFailed forking child...");
        return;
    }
}

void shelludo_exec_piped(char** args, char** argspipe) {
    // 0 read, 1 write
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        printf("\n Pipe could not be initialized");
        return;
    }

    p1= fork();

    if (p1 < 0) {
        printf("\nCouldn't fork");
        return;
    }

    if (p1 > 0) {
        /* Parent */
        p2= fork();

        if (p2 > 0) {
            /* Parent, wait for both children */
            wait(NULL);
            wait(NULL);
        } else if (p2 == 0) {
            /* Reading child */
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            execvp(argspipe[0], argspipe);
            printf("\n Could not execute command 2...");
            exit(0);
        } else {
            printf("\nCould not fork");
            return;
        }
    } else if (p1 == 0) {
        /* First child, writing */
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execvp(args[0], args);
        printf("\nCould not execute command 1...");
        exit(0);
    }
}

void help() {
    printf("\n***WELCOME TO SHELLUDO HELP***"
        "\nCopyright @ Michael Kittredge"
        "\nList of Commands supported:"
        "\n>cd"
        "\n>exit"
        "\n>hello"
        "\n>jason"
        "\n>foreground"
        "\n>background"
        "\n>departments"
        "\n>courses"
        "\nall other general commands in UNIX shell"
        ">basic pipe handling (independent commands, no blocking)"
        "\nimproper space handling");

    return;
}

int man_handle(char** parsed, char** custom_cmds) {
    int i;
    if (parsed[1] != NULL) {
        for(i= 0; i < CMDS_SUPPORTED; i++) {
            if (strcmp(custom_cmds[i], parsed[1]) == 0) {
                return custom_man(i + 1);
            }
        }
    }

    return 0;
}

void change_foreground_color(char** parsed) {
    char colors[8][10]= {"black", "red", "green", "yellow", "blue", 
                "magenta", "cyan", "white"};
    char color_codes[8][10]= {BLK, RED, GRN, YEL, BLU, MAG, CYN, WHT};
    int i;
    for(i= 0; i < sizeof(colors), parsed[1] != NULL; i++) {
        if(strcmp(parsed[1], colors[i]) == 0) {
            /* Store the color to defaults */
            FILE* fptr1, *fptr2;
            char line[50];

            /* Change the color */
            print_color(color_codes[i]);

            fptr1= fopen("color-data", "r");

            if (fptr1 == NULL) {
                printf("File opening failed");
            } else {
                fgets(line, 50, fptr1);
                fgets(line, 50, fptr1); /* Read the second line */
                fptr2= fopen("color-data", "w");
                fputs(color_codes[i], fptr2);
                fputs("\n", fptr2);
                printf("%s", color_codes[i]);
                fputs(line, fptr2);
                fclose(fptr1);
                fclose(fptr2);
            }

            return;
        }
    }
}

void change_background_color(char** parsed) {
    char colors[8][10]= {"black", "red", "green", "yellow", "blue", 
        "magenta", "cyan", "white"};
    char color_codes[8][10]= {BLKB, REDB, GRNB, YELB, BLUB, MAGB, CYNB, WHTB};
    int i;
    
    for (i= 0; i < sizeof(colors), parsed[1] != NULL; i++) {
        if(strcmp(parsed[1], colors[i]) == 0) {
            FILE* fptr1, *fptr2;
            char line[50];

            print_color(color_codes[i]);
            
            fptr1= fopen("color-data", "r");

            if (fptr1 == NULL) {
                printf("File opening failed");
            } else {
                fgets(line, 50, fptr1);
                fptr2= fopen("color-data", "w");
                fputs(line, fptr2);
                fputs(color_codes[i], fptr2);
                fclose(fptr1);
                fclose(fptr2);
            }

            return;
        }
    }
}

void get_departments(char** parsed) {
    char curl[200]= "curl -l curl -l https://app.testudo.umd.edu/soc/";
    if (parsed[1] == NULL) {
        strcat(curl, " | grep -oP \'(?<=<span class=\"prefix-name nine columns\">).*?(?=</span>)\' > socoutput");
    } else if (strcmp(parsed[1], "-c") == 0) {
        strcat(curl, " | grep -oP \'(?<=<span class=\"prefix-abbrev push_one two columns\">).*?(?=</span>)\'");
    } else {
        return;
    }

    system("touch socoutput");
    system(curl);
    system("cat socoutput");
    system("rm -f socoutput");
}

void search_courses(char** parsed) {
    char curl[200]= "curl -l https://app.testudo.umd.edu/soc/202508/";
    char* str= parsed[1];
    if (parsed[1] == NULL || strlen(parsed[1]) != 4) {
        return;
    }

    while (*str) {
        *str = toupper(*str);
        str++;
    }
    strcat(curl, parsed[1]);
    strcat(curl, " | grep -oP \'(?<=<span class=\"course-title\">).*?(?=</span>)\' > courseoutput");
    system("touch courseoutput");
    system(curl);
    system("cat courseoutput");
    system("rm -f courseoutput");
}

int shelludo_cmds(char** parsed) {
    int i, switch_custom_arg= 0;
    char* custom_cmds[CMDS_SUPPORTED];
    char* username;

    custom_cmds[0]= "exit";
    custom_cmds[1]= "man";
    custom_cmds[2]= "cd";
    custom_cmds[3]= "help";
    custom_cmds[4]= "hello";
    custom_cmds[5]= "jason";
    custom_cmds[6]= "foreground";
    custom_cmds[7]= "background";
    custom_cmds[8]= "departments";
    custom_cmds[9]= "courses";

    for (i= 0; i < CMDS_SUPPORTED; i++) {
        if (strcmp(parsed[0], custom_cmds[i]) == 0) {
            switch_custom_arg= i + 1;
            break;
        }
    }

    switch (switch_custom_arg) {
        case 1:
            printf("\nGoodbye!\n");
            print_color(CRESET);
            sleep(1);
            exit(0);
        case 2:
            return man_handle(parsed, custom_cmds);
        case 3:
            chdir(parsed[1]);
            return 1;
        case 4:
            help();
            return 1;
        case 5:
            username= getenv("USER");
            printf("Hello %s. Quit messing around.", username);
            return 1;
        case 6:
            printf("Hi Jason! Thanks for using my shell.");
            return 1;
        case 7:
            change_foreground_color(parsed);
            return 1;
        case 8:
            change_background_color(parsed);
            return 1;
        case 9:
            get_departments(parsed);
            return 1;
        case 10:
            search_courses(parsed);
            return 1;
        default:
            break;
    }

    return 0;
}

void shelludo_split(char* line, char** parsed) {
    int i;

    for (i= 0; i < MAXLIST; i++) {
        parsed[i]= strsep(&line, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int shelludo_split_pipe(char* line, char** linepiped) {
    int i;

    for (i= 0; i < 2; i++) {
        linepiped[i]= strsep(&line, "|");
        if (linepiped[i] == NULL)
            break;
    }

    if (linepiped[1] == NULL)
        return 0; /* No pipe found */
    else
        return 1; /* Success */
}

int shelludo_process(char* line, char** parsed, char** parsedpipe) {
    char* linepiped[2];
    int piped= 0;

    piped= shelludo_split_pipe(line, linepiped);

    if (piped) {
        shelludo_split(linepiped[0], parsed);
        shelludo_split(linepiped[1], parsedpipe);
    } else {
        shelludo_split(line, parsed);
    }

    if (shelludo_cmds(parsed))
        return 0;
    else 
        return 1 + piped;
}

