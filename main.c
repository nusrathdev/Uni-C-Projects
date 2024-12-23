#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PATH 1024

// Function prototypes
void print_tree(const char *base_path, int depth);

// Print indentation based on depth
void print_indentation(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|   ");
    }
}

// Recursive function to visualize folder structure
void print_tree(const char *base_path, int depth) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(base_path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Print current file or directory
        print_indentation(depth);
        printf("|-- %s\n", entry->d_name);

        // Construct new path
        char path[MAX_PATH];
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

        // Check if it's a directory and recursively call print_tree
        struct stat path_stat;
        stat(path, &path_stat);
        if (S_ISDIR(path_stat.st_mode)) {
            print_tree(path, depth + 1);
        }
    }

    closedir(dir);
}

int main() {
    char path[MAX_PATH];

    printf("Enter directory path to visualize: ");
    scanf("%s", path);

    printf("Folder Tree for: %s\n", path);
    print_tree(path, 0);

    printf("\nVisualization complete.\n");
    return 0;
}
