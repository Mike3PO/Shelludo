int custom_man(int cmd) {
    switch (cmd) {
        case 1:
            printf("SYNOPSIS\nexit\nDESCRIPTION\nBid farewell to your beloved shell program"
                " as it enters willingly into the cold embrace"
                " of death. :(");
            return 1;
        case 2:
            return 0;
        case 3:
            printf("SYNOPSIS\n"
                    "cd [DIRECTORY]\n"
                    "DESCRIPTION\nChange directory");
            return 1;
        case 4:
            printf("SYNOPSIS\nhelp\nDESCRIPTION\nLoki's favorite, GET HELP!");
            return 1;
        case 5:
            printf("SYNOPSIS\nhello\nDESCRIPTION\nFriendly reminder to lock in" 
                " and remember your own name");
            return 1;
        case 6:
            printf("SYNOPSIS\njason\nDESCRIPTION\nThank you to my brother.");
            return 1;
        case 7:
            printf("SYNOPSIS\nforeground [COLOR]\nDESCRIPTION\nChange the foreground color.\n"
                    "COLOR OPTIONS:\n\t-black\n\t-red\n\t-green\n\t-yellow\n\t-blue\n\t-magenta\n\t-cyan\n\t-white");
            return 1;
        case 8:
            printf("SYNOPSIS\nbackground [COLOR]\nDESCRIPTION\nChange the background color.\n"
                    "COLOR OPTIONS:\n\t-black\n\t-red\n\t-green\n\t-yellow\n\t-blue\n\t-magenta\n\t-cyan\n\t-white");
            return 1;
        case 9:
            printf("SYNOPSIS\ndepartments [-c concise]\nDESCRIPTION\nlists all departments at UMD.\n"
                    "\n-c - prints just the 4 letter codes");
            return 1;
        case 10:
            printf("SYNOPSIS\ncourses [DEPARTMENT]\nDESCRIPTION\nlists all the courses in the given department."
                    "\nThis information can be found with departments -c");
            return 1;
        default:
            printf("Catastrophic error, man page not found");
            break;
    }

    return 0;
}