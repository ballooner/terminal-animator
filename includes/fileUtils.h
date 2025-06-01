#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <dirent.h>

// Checks if a directory is empty
// returns:
// -1 on failure
// 0 on non-empty
// 1 on empty
int isDirEmpty(char *dirPath);
int doesDirExist(char *dirPath);
int createDir(DIR *parent, char *dirName);
int createFile(DIR *parent, char *fileName);
int deleteDir(DIR *parent, char *dirName);

#endif
