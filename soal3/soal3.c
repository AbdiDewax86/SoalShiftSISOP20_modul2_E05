#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>
#include <fts.h>
#include <dirent.h>
#include <string.h>

void fill(char *folder){
    pid_t child_id;

    child_id = fork();
    
    int status;
    
    char coba1[200];
    char coba2[200];

    strcpy(coba1,folder);
    strcpy(coba2,folder);

    strcat(coba1,"/coba1.txt");
    strcat(coba2,"/coba2.txt");

    if(child_id < 0)
        exit(EXIT_FAILURE);
    if(child_id == 0){
        pid_t child_id2;
        child_id2 = fork();
        int status2;

        if(child_id2 < 0)
            exit(EXIT_FAILURE);
        if(child_id2 == 0){
            char *argv[] = {"touch", coba1, NULL};
            execv("/usr/bin/touch",argv);
        }
        else{
            while ((wait(&status2)) > 0);
            sleep(3);

            char *argv[] = {"touch", coba2, NULL};
            execv("/usr/bin/touch",argv);
        }
    }
}

int checkfile(char * source){
    struct stat path_stat;
    stat(source, &path_stat);
    return S_ISREG(path_stat.st_mode);  //0 jika directory
}

int main(void){
    pid_t child_id;     //indomie
    pid_t child_id2;    //mi sedap
    pid_t child_id3;    //unzip jpg.zip
    
    int status;
    int status2;
    int status3;

    child_id = fork();
    child_id2 = fork();
    child_id3 = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE);
    }
    if (child_id == 0){             //buat indomie
        char *argv[] = {"mkdir", "-p", "/home/jiahstrike/modul2/indomie", NULL};
        execv("/bin/mkdir", argv);
    }
    else{   //else parent
        while ((wait(&status)) > 0);
        sleep(5);

        if (child_id2 < 0) {
            exit(EXIT_FAILURE);
        }
        if (child_id2 == 0){        //rebus mi sedap
            char *argv[] = {"mkdir", "-p", "/home/jiahstrike/modul2/sedaap", NULL};
            execv("/bin/mkdir", argv);
        }

        if(child_id3 < 0){
            exit(EXIT_FAILURE);
        }
        if(child_id3 == 0){
            char *argv[] = {"unzip", "jpg.zip", "-d", "/home/jiahstrike/modul2", NULL};
            execv("/usr/bin/unzip", argv);
        }
        
        else{
            //pindah file dan folder
            while ((wait(&status3)) > 0);
            sleep(1);

            struct dirent *dirpent;
            DIR *dir;

            dir= opendir("/home/jiahstrike/modul2/jpg");

            if(dir)
            {
                while((dirpent=readdir(dir)) != NULL){
                    printf("test\n");
                    pid_t child_id4;
                    child_id4 = fork();
                    if(child_id4 < 0)
                        exit(EXIT_FAILURE);

                    if(!strcmp(dirpent->d_name,".") || !strcmp(dirpent->d_name,"..")) {
                        continue;
                    }

                    char source[200] = "/home/jiahstrike/modul2/jpg/";
                    char *target;
                    strcat(source,dirpent->d_name);

                    if( checkfile(source)==0 ){
                        target = "/home/jiahstrike/modul2/indomie/";
                    }
                    else{
                        target = "/home/jiahstrike/modul2/sedaap/";
                    }
                    //printf("%s -> %s\n",source,target);

                    if(child_id4 == 0){
                        char *arg[] = {"mv",source,target,NULL};
                        execv("/bin/mv",arg);
                    }
                }
                closedir(dir);
            }

            //isi folder
            sleep(3);

            dir = opendir("/home/jiahstrike/modul2/indomie");

            //printf("test");

            if(dir){
                while((dirpent=readdir(dir)) != NULL){
                    printf("%s\n",dirpent->d_name);
                    if(!strcmp(dirpent->d_name,".") || !strcmp(dirpent->d_name,"..")) {
                    continue;
                    }
                    char folder[200] = "/home/jiahstrike/modul2/indomie/";

                    strcat(folder,dirpent->d_name);

                    fill(folder);
                    printf("%s\n",folder);
                }
            }
        }
    }
}
