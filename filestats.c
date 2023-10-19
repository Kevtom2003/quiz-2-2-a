#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <grp.h>

//Kevin Thomas
//132002474

//helper function to convert octal access mode to symbolic
char* converOctal(mode_t modes){
    //need to generate symbolic character for each octal number
    int flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    char flagSym[] = {"rwxrwxrwx"};
    char flagAccess[10];
   //use & bit operator to check if permission flag is set
    for(int i = 0; i < 9;i++){
        if((modes & flags[i])){
            flagAccess[i] = flagSym[i];
        }else{
            flagAccess[i] = '-';
        }
    }
    flagAccess[9] = '\0';
    return strdup(flagAccess);
}

int main(int argc, char *argv[])
{
    // todo
    //open directory from argv and iterate through named files
    //use dirent to hold directory info
    DIR *dp;
    struct dirent *dirp;
    //use stat to get link and owner info
    struct stat file_stats;
    //use passwd and group to get usr and group info
    struct passwd *pwd;
    struct group *grp;
    //handle situation when usr does not enter a dir name
    if (argc != 2){
        fprintf(stderr, "usage: filestats directory_name\n");
        exit(-1);
    }
    //error handling for incorrect directory
    if ((dp = opendir(argv[1])) == NULL){
        fprintf(stderr, "can’t open %s\n", argv[1]);
        exit(-1);
    }
        
    while ((dirp = readdir(dp)) != NULL){
        //store filepath in a buf to get stats later
        char file_path[1024];
        snprintf(file_path, 1024, "%s/%s", argv[1], dirp->d_name);
        //print name of directory
        printf("Filename: %s\n", dirp->d_name);
        //print inode number
        printf("inode number: %ld\n", dirp->d_ino);
        //make lstat sys call to get info for that specific file
        lstat(file_path, &file_stats);
        //print number of links
        printf("number of links: %ld\n", file_stats.st_nlink);
        // use getpwuid and getgrgid to get id of usr and group owner
        pwd = getpwuid(file_stats.st_uid);
        grp = getgrgid(file_stats.st_gid);
        printf("User ID of owner: %d\n", pwd->pw_uid);
        printf("Group ID of owner: %d\n",grp->gr_gid);
        //use stat struct we made earlier to get size in bytes
        printf("Size in bytes: %ld bytes\n", file_stats.st_size);
        //get access, modification, status change times using stat
        char* accessTime;
        char* modTime;
        char* statusTime;
        //use ctime to turn timestamp to string
        accessTime = ctime(&file_stats.st_atime);
        modTime = ctime(&file_stats.st_mtime);
        statusTime = ctime(&file_stats.st_ctime);
        printf("Last access: %s", accessTime);
        printf("Last modification: %s", modTime);
        printf("Last status change: %s", statusTime);
        printf("Number of disk blocks allocated: %ld\n", file_stats.st_blocks);
        printf("Access mode in octal: %o\n", file_stats.st_mode);
        char* accessflags = converOctal(file_stats.st_mode);
        printf("Access mode flags: %s\n",accessflags);
        //newlines
        printf("\n");
    }
    closedir(dp);
    exit(0);


    
}