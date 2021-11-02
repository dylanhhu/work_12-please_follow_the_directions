#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


int main() {
    DIR *curr_dir;
    curr_dir = opendir(".");

    struct dirent *curr_file;
    curr_file = readdir(curr_dir);

    unsigned long total_bytes = 0;  // including directory files
    unsigned long file_bytes = 0;   // excluding directory files
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
    printf("Total Directory Size: %lu\n", total_bytes);
    printf("Total Files Size: %lu\n", file_bytes);

    closedir(curr_dir);

    return 0;
}
