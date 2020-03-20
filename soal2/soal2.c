#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main(int args, char **argv) {
  if(args != 2){
    exit(0);
  }
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/dimasadh/Documents/Praktikum2/soal2/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


  //PROSES MEMBUAT PROGRAM KILL.SH
  int ppid = getpid();
  FILE *fp;
  fp = fopen("kill.sh","w");
  if(strcmp(argv[1],"-a")==0)
  {
	  fprintf(fp,"#!/bin/bash\nkill -9 -%d\nrm kill",ppid);
  }
  if(strcmp(argv[1],"-b")==0)
  {
	  fprintf(fp,"#!/bin/bash\nkill %d\nrm kill",ppid);
  }
  fclose(fp);
  pid_t kill;
  //PROSES MENGGANTI CHMOD AGAR EXECUTABLE DAN MENGHILANGKAN .SH
  if (kill=fork()==0)
  {
		pid_t chm;
		if(chm=fork()==0)
		{
			char *argv[] = {"chmod","+x","kill.sh",NULL};
			execv("/bin/chmod",argv);
		}
		else
		{
			wait(NULL);		  
			char *argv[] = {"mv", "kill.sh", "kill", NULL};
			execv("/bin/mv",argv);
		}
  }


  while (1) 
  {
	pid_t parent;
	parent = fork();
	if(parent==0)
	{
		char pathdir[128];
		time_t t  =time(NULL);
		struct tm tm = *localtime(&t),tm2;
		snprintf(pathdir,sizeof(pathdir),"%d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		
		pid_t child1;
		//PROSES MEMBUAT DIREKTORI
		if (child1=fork()==0){
			char *argv[] = {"mkdir","-p",pathdir,NULL};
		    	execv("/bin/mkdir", argv);
		}
		//PROSES DOWNLOAD
		else{
			wait(NULL);
			if(fork()==0){
				int i =20;
				pid_t parent;
				while (i--){
					pid_t downloads;
					downloads = fork();
					if(downloads==0){
						time_t t2  =time(NULL);
						struct tm tm = *localtime(&t2);
						t2 = (t2%1000) + 100;
						char time[128];
						snprintf(time,sizeof(time),"%d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
						char buffer2[128];
						char link[128] = "https://picsum.photos/";
						snprintf(buffer2,sizeof(buffer2),"%ld",t2);
						strcat(link,buffer2);
						strcat(pathdir,"/");
						strcat(pathdir,time);
						char *argv2[] = {"wget","-O",pathdir,link,NULL};
						execv("/usr/bin/wget",argv2);
					}
					else{
						sleep(5);
					}
				}
			exit(0);
			}
			//PROSES ZIP
			else{
				wait(NULL);
				pid_t zip;
				char temp [128];
				strcpy(temp,pathdir);
				strcat(temp,".zip");
				if (zip=fork() == 0){
					char *argv3[] = {"zip", "-r", temp, pathdir, NULL};
					execv("/usr/bin/zip", argv3);
				}
				else{
					wait(NULL);
					char *argv4[] = {"rm", "-r", pathdir, NULL};
					execv("/bin/rm", argv4);
				}
			}
		}
	}
	else{
		sleep(30);
	}
  }
}
