#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>

int main (int argc, char*argv[])
{
	bool flag[]={false,false,false};
	bool error = false;
	bool nol = false;
	int sec,min,hour;
	char path[50];
	printf("cmdline args count=%d\n", argc);
    if (argc>5){
        error = true;
    }
	char buffer[128];
	printf("sec = %s\nmin = %s\nhour = %s\n%s\n",argv[1],argv[2],argv[3],argv[4]);
	//printf("exe name=%s\n", argv[0]);
	if(strlen(argv[1])<3){
		if(strcmp(argv[1], "*") != 0)
		{
			if(strcmp(argv[1], "0") == 0){
				nol = true;
			}
			sec = atoi(argv[1]);
			if(sec>59 || sec<0 || (nol==false && sec==0) || (strlen(argv[1])==2 && sec <10)){
				error = true;
			}
		}
		else{
			flag[0]=true;
			sec = -1;
		}
	}
	else {error = true;}
	if(strlen(argv[2])<3){
		if(strcmp(argv[2], "*") != 0)
		{
			if(strcmp(argv[2], "0") == 0){
				nol = true;
			}
			min = atoi(argv[2]);
			if(min>59 || min<0 || (nol==false && min==0) || (strlen(argv[2])==2 && min <10)){
				error = true;
			}
		}
		else{
			flag[1]=true;
			min = -1;
		}
	}
	else {error = true;}
	if(strlen(argv[3])<3){
		if(strcmp(argv[3], "*") != 0)
		{
			if(strcmp(argv[3], "0") == 0){
				nol = true;
			}
			hour = atoi(argv[3]);
			if(hour>23 || hour<0 || (nol==false && hour==0) || (strlen(argv[3])==2 && hour <10)){
				error = true;
			}
		}
		else{
			flag[2]=true;
			hour = -1;
		}
	}
	else {error = true;}
	struct stat stats;
	strcpy(path,argv[4]);
	if(stat(path,&stats)!=0){
		error = true;
		printf ("Datapath error!\n");
		exit(EXIT_FAILURE);
	}
	if(error==true){
		printf ("Argument error!! Process stopped\n");
		exit(EXIT_FAILURE);
	}

	//DAEMON TEMPLATE

	pid_t pid, sid;        // Variabel untuk menyimpan PID

	pid = fork();     // Menyimpan PID dari Child Process
	//printf("%s\n%s\n%s\n%s\n",argv[1],argv[2],argv[3],argv[4]);
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

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

		//printf ("%d %d %d %s\n",sec,min,hour,path);
		char *argv2[] = {"bash",path,NULL};
		//execv("/bin/bash", argv2);



	while(1){
		pid_t jalan;
		time_t t  =time(NULL);
		struct tm tm = *localtime(&t);
		/*snprintf(buffer,sizeof(buffer),"%d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, 			tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);*/
		 /* First argument is executable name only */

		if (flag[0]==false && flag[1]==false && flag[2]==false){
		while(1){
			if (tm.tm_sec == sec && tm.tm_min == min && tm.tm_hour == hour){
				if (jalan = fork() == 0){
				execv("/bin/bash", argv2);
			}}
			sleep(1);
			t = time(NULL);
                        tm = *localtime(&t);
		}}
		if (flag[0]==false && flag[1]==false && flag[2]==true){
		while(1){
			if (tm.tm_sec == sec && tm.tm_min == min){
				if (jalan = fork() == 0){
				execv("/bin/bash", argv2);
			}}
			sleep(1);
			t = time(NULL);
			tm = *localtime(&t);
		}}
		if (flag[0]==false && flag[1]==true && flag[2]==false){
		while(1){
			if (tm.tm_sec == sec && tm.tm_hour == hour){
				if (jalan = fork() == 0){
				execv("/bin/bash", argv2);
			}}
			sleep(1);
			t = time(NULL);
			tm = *localtime(&t);
		}}
		if (flag[0]==false && flag[1]==true && flag[2]==true){
		while(1){
			if (tm.tm_sec == sec){
				if (jalan = fork() == 0){
				execv("/bin/bash", argv2);
			}}
			sleep(1);
			t = time(NULL);
			tm = *localtime(&t);
		}}
		if (flag[0]==true && flag[1]==false && flag[2]==false){
		while(1){
			if (tm.tm_min == min && tm.tm_hour == hour){
				if (jalan = fork() == 0){
				execv("/bin/bash", argv2);
			}}
			sleep(1);
			t = time(NULL);
			tm = *localtime(&t);
		}}
		if (flag[0]==true && flag[1]==false && flag[2]==true){
		while(1){
			if (tm.tm_min == min){
				if (jalan = fork() == 0){
				execv("/bin/bash", argv2);
			}}
			sleep(1);
			t = time(NULL);
			tm = *localtime(&t);
		}}
		if (flag[0]==true && flag[1]==true && flag[2]==false){
		while(1){
			if (tm.tm_hour == hour){
				if (jalan = fork() == 0){
				execv("/bin/bash", argv2);
			}}
			sleep(1);
			t = time(NULL);
			tm = *localtime(&t);
		}}
		if (flag[0]==true && flag[1]==true && flag[2]==true){
			int i=0;
		while(1){
			if (jalan = fork() == 0){
			execv("/bin/bash", argv2);
			}
			sleep(1);
			t = time(NULL);
			tm = *localtime(&t);
		}}
	}
 }
