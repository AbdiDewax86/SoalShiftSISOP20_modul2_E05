#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

void download (char pathdir[])
{
	int i =3;
	while (i--){
		sleep(5);
		pid_t downloads;
		downloads = fork();
		if(downloads==0){
			time_t t2  =time(NULL);
			struct tm tm = *localtime(&t2);
			t2 = (t2%1000) + 100;
			char time[128];
			snprintf(time,sizeof(time),"%d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			//strcat(pathdir,time);
			char buffer2[128];
			char link[128] = "https://picsum.photos/";
			snprintf(buffer2,sizeof(buffer2),"%ld",t2);
			strcat(link,buffer2);
			strcat(pathdir,"/");
			strcat(pathdir,time);
			char *argv2[] = {"wget","-O",pathdir,link,NULL};
			execv("/usr/bin/wget",argv2);
		}
	}
}

int main() {
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
      	pid_t pid, sid;        // Variabel untuk menyimpan PID
  	pid = fork();     // Menyimpan PID dari Child Process
 	 int i =0;
 	 while (i<2) 
 	 {
		pid_t parent;
		parent = fork();
		if(parent==0)
		{
			char buffer[128];
			time_t t  =time(NULL);
			struct tm tm = *localtime(&t),tm2;
			snprintf(buffer,sizeof(buffer),"%d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			char pathdir[128] ="/home/dimasadh/Documents/Praktikum2/tess/";
			strcat(pathdir,buffer);
			
			pid_t child1;
			if (child1=fork()==0){
				char *argv[] = {"mkdir","-p",pathdir,NULL};
			    	execv("/bin/mkdir", argv);
			}
			else{
				wait(NULL);
				download(pathdir);
			}
			sleep(10);
		}
		i++;
		sleep(5);
 	 }
  }
}
