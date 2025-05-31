#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <dirent.h>

int isDirEmpty(DIR *dir);
struct dirent findDir(DIR *dir, char *target);
int createDir(DIR *parent, char *dirName);
int deleteDir(DIR *parent, char *dirName);

#endif
