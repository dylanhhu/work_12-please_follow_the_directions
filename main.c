#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


void get_path(char *dest, int length);


int main(int argc, char *argv[]) {
    char dir_path[100];

    // check if the user provided a path
    if (argc <= 1) {
        get_path(dir_path, sizeof(dir_path));
    }
    else {
        // not working
        strcpy(dir_path, argv[1]);
    }

    DIR *curr_dir;
    curr_dir = opendir(dir_path);

    if (!curr_dir) {
        printf("Error: %s\n", strerror(errno));

        return errno;
    }


    struct dirent *curr_file;
    curr_file = readdir(curr_dir);

    unsigned long long total_bytes = 0;  // including directory files
    unsigned long long file_bytes = 0;   // excluding directory files
    int num_files = 0;
    
    while (curr_file) {
        struct stat info;
        stat(curr_file->d_name, &info);

        num_files++;
        total_bytes += info.st_size;

        if (S_ISDIR(info.st_mode)) printf("Directory:\t");
        else {
            printf("File:\t\t");
            file_bytes += info.st_size;
        }

        printf("%s\n", curr_file->d_name);
        
        curr_file = readdir(curr_dir);
    }

    printf("\nStatistics for directory: .\n");
    printf("Number of files: %d\n", num_files);
    printf("Total Directory Size: %llu\n", total_bytes);
    printf("Total Files Size: %llu\n", file_bytes);

    closedir(curr_dir);

    return 0;
}


void get_path(char *dest, int length) {
    printf("Directory path required.\nEnter a directory: ");
    fgets(dest, length, stdin);
}
