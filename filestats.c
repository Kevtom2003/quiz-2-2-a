#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // todo
    //open directory from argv and iterate through named files
    //use dirent to hold directory info
    DIR *dp;
    struct dirent *dirp;
    //use stat to get link and owner info
    struct stat file-stats;
    //use passwd and group to get usr and group info
    struct passwd *pwd;
    struct group *grp;
    //handle situation when usr does not enter a dir name
    if (argc != 2){
        fprintf(stderr, "usage: ls directory_name");
        exit(-1);
    }
    //error handling for incorrect directory
    if ((dp = opendir(argv[1])) == NULL){
        printf("can’t open %s", argv[1]);
    }
        
    while ((dirp = readdir(dp)) != NULL){
        //print name of directory
        printf("Filename: %s\n", dirp->d_name);
        //print inode number
        printf("inode number: %s\n", dirp->d_ino);
        //make stat sys call to get next bit of info
        //print number of links
        printf("number of links: %s\n", dirp->d_name);
    }
    closedir(dp);
    exit(0);


    
    ctime(t);
}