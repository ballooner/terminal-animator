#include "fileUtils.h"
#include <dirent.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>

// Checks if a directory is empty
// returns:
// -1 on failure
// 0 on non-empty
// 1 on empty
int isDirEmpty(char *dirPath)
{
    DIR *directory = opendir(dirPath);

    if (!directory)
	return -1;

    int fileCounter = 0;
    
    // Check for a file and return if found
    while (readdir(directory) != NULL)
	fileCounter++;

    // '.' and '..' are always in a directory
    if (fileCounter == 2)
	return true;

    return false;
}

int doesDirExist(char *dirPath)
{
    opendir(dirPath);

    if (errno == ENOENT || errno == ENOTDIR)
	return false;
    
    return true;
}


// Create specified directory at parent directory with dirName
// returns:
// -2 on error
// -1 on dir already exists
// 0 on success
int createDir(DIR *parent, char *dirName)
{
    if (doesDirExist(dirName) == 1)
	return -1;

    size_t buffSize = sizeof(parent->d_name) / sizeof(char) +
		      sizeof(dirName)        / sizeof(char) + 1;
    char buff[buffSize];
    if (sprintf(buff, buffSize, "%s/%s", parent->d_name, dirName) != 0)
	return -2;

    // Set dirMode to make a directory
    mode_t dirMode = S_IFDIR;

    if (mkdir(buff, dirMode) != 0)
	return -2;

    return 0;
}
