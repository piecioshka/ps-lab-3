#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../lib/libutils.c"

void usage() {
    fprintf(stderr, "Searching program in each directory include in PATH.\n");
    fprintf(stderr, "Usage: program\n");
    exit(1);
}

int user_have_rights_to_execute(int user_id, char * filename) {
    int rights = access(filename, X_OK);
    struct stat info;
    stat(filename, &info);
    return (info.st_uid == user_id && info.st_mode & S_IXUSR && rights == 0);
}

int main(int argc, char * argv[]) {
    if (argc != 2) usage();

    char * path = getenv("PATH");
    // printf("%s\n\n", path);

    uid_t user_id = geteuid();
    char * login = uid_to_name(user_id);
    printf("User: %s (%d)\n", login, user_id);
    printf("Searching '%s'...\n\n", argv[1]);

    char * sp = strtok(path, ":");
    char * filename = malloc(1000);
    char * rights;

    while (sp != NULL) {
        sp = strtok(NULL, ":");
        if (sp == NULL) continue;
        // printf("%s\n", sp);

        snprintf(filename, strlen(sp) + strlen(argv[1]) + 2, "%s/%s", sp, argv[1]);

        if (file_exists(filename)) {
            if (user_have_rights_to_execute(user_id, filename)) {
                rights = "yes";
            } else {
                rights = "no";
            }
            printf(" - %s -> rights: %s\n", filename, rights);
        }
    }

    exit(0);
}

