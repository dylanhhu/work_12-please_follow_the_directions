#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[]) {
    DIR *curr_dir;

    // check if the user provided a path, prompt if not
    if (argc <= 1) {
        char dir_path[100];

        printf("Directory path required.\nEnter a directory: ");
        fgets(dir_path, sizeof(dir_path), stdin);
        printf("\n");

        sscanf(dir_path, "%s", dir_path); // to remove the trailing newline

        curr_dir = opendir(dir_path);
    }
    else {
        curr_dir = opendir(argv[1]);
    }

    // check if errors occurred
    if (curr_dir == NULL) {
        printf("Error: %s\n", strerror(errno));
        return errno;
    }


    struct dirent *curr_file;
    curr_file = readdir(curr_dir);
    struct stat info;

    unsigned long long total_bytes = 0;
    int num_files = 0;

    // get total file sizes
    while (curr_file) {
        num_files++;

        if (curr_file->d_type == DT_REG) {
            stat(curr_file->d_name, &info);
            total_bytes += info.st_size;  // unreliable, st_size's size is not well defined
        }

        curr_file = readdir(curr_dir);
    }

    printf("Directory Statistics:\n");
    printf("Number of files: %d\n", num_files);
    printf("Total Directory Size: %llu\n", total_bytes);
    

    rewinddir(curr_dir);
    curr_file = readdir(curr_dir);
    char printed = 0;
    printf("\nDirectories:\n");
    while (curr_file) {
        if (curr_file->d_type == DT_DIR) {
            printf("%s\n", curr_file->d_name);
            printed = 1;
        }
        curr_file = readdir(curr_dir);
    }
    if (!printed) printf("(none)\n");


    rewinddir(curr_dir);
    curr_file = readdir(curr_dir);
    printed = 0;
    printf("\nFiles:\n");
    while (curr_file) {
        if (curr_file->d_type != DT_DIR) {
            printf("%s\n", curr_file->d_name);
            printed = 1;
        }
        curr_file = readdir(curr_dir);
    }
    if (!printed) printf("(none)\n");

    closedir(curr_dir);
    return 0;
}
