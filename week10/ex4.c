#include <stdio.h>
#include <sys/types.h>
#include <sys/dir.h>

// List of all traversed files
int filesCount = 0;
struct dirent fileList[1024];

// List of files with >= 2 links
int wantedFilesCount = 0;
int wantedFiles[1024];


int main() {
    DIR *tmp = opendir("tmp");
    if (tmp == NULL) {
        printf("Error opening tmp directory\n");
        return 1;
    }

    struct dirent *entry;
    // Go through each entry in the directory
    while ((entry = readdir(tmp)) != NULL) {
//        printf("File is: %s; %d\n", entry->d_name, entry->d_ino);
        
        // Save the file information
        fileList[filesCount++] = *entry;

        // Check if file with the same inode is already in the directory
        for (int i = 0; i < filesCount - 1; i++) {
            if (fileList[i].d_ino == entry->d_ino) {
//                printf("Found a file with the same inode\n");
//
                // If it is, check if we already added it to the wanted list
                // (for example, if it is the third occurence of the same file)
                int contains = 0;
                for (int j = 0; j < wantedFilesCount; j++) {
                    if (wantedFiles[j] == entry->d_ino) {
                        contains = 1;
                        break;
                    }
                }

                // If we didn't add it yet, do it now
                if (!contains) {
                    wantedFiles[wantedFilesCount++] = entry->d_ino;
                }
            }
        }
    }

    // Go through each wanted file and print all its filenames
    for (int i = 0; i < wantedFilesCount; i++) {
        int inode = wantedFiles[i];

        printf("Files with inode %d: ", inode);
        for (int j = 0; j < filesCount; j++) {
            if (fileList[j].d_ino == inode)
                printf("%s ", fileList[j].d_name);
        }
        printf("\n");
    }

    return 0;
}


