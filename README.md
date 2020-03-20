# SoalShiftSISOP20_modul2_E05
## Soal 1
#### Code 1-1:
```
int main (int argc, char*argv[]) 
{
	bool flag[]={false,false,false};
	bool error = false;
	bool nol = false;
	int sec,min,hour;
	char path[50];
	//printf("cmdline args count=%d\n", argc);
	char buffer[128];
	if (argc>4){
	error = true;}
	printf("%s\n%s\n%s\n%s\n",argv[1],argv[2],argv[3],argv[4]);
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
```
Dalam code ini, kita akan menerima 4 argumen, yaitu sec,min,hour,path. Untuk mencegah adanya error pada argument, ada beberapa hal yang diperhatikan, yaitu :
    • Jika argc lebih dari 4, maka terjadi error
    • Jika argument waktu (sec,min,hour) diinput sebuah huruf, maka hasil atoi akan menjadi 0, sehingga perlu di check ketika nilai waktu (sec,min,hour) = 0, apakah itu merupakan input user atau kesalahan input dari sebuah huruf yang dilakukan user
    • Jika panjang argument lebih dari 2 array, maka error, karena waktu hanya membutuhkan paling banyak 2 array
    • Jika panjang argument = 2, namun hasil atoi dari waktu (sec,min,hour) < 10, maka dipastikan inputan error (salah satu merupakan huruf)
    • Jika sec < 0 atau sec > 59 maka error
    • Jika min < 0 atau min > 59 maka error
    • Jika hour < 0 atau hour > 23 maka error
    • Jika path tidak ada, maka error
Dan pada code ini juga, proses pembuatan daemon dilakukan.
#### Code 1-2:
```
	char *argv2[] = {"bash",path,NULL};	
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
```
Dalam code ini, proses yang akan dilakukan daemon ialah mengeksekusi file yang diinginkan user sesuai dengan jadwal yang telah diterima. Pertama, kita harus menginisialisasikan child_id untuk membuat fork(). Dimana child ini yang akan menjalankan perintah yang diterima.
Untuk memilih schedule mana yang akan dipilih, disediakan 3 flag, yaitu :
- flag[0] = sec
- flag[1] = min
- flag[2] = hour

Ketika flag ini bernilai false, maka menandakan bahwa jadwal perintah dieksekusi diterima oleh system. Namun ketika flag bernilai true, maka menandakan bahwa jadwal perintah dieksekusi tidak diterima oleh system (input = ‘*’), oleh karena itu, program akan mengeksekusinya setiap waktu nya (sec/min/hour).
Ketika program telah mengetahui schedule mana yang akan digunakan, maka dilakukan loop while (true). Disini lah child akan dijalankan dimana child akan mengeksekusi perintah yang diterima jika waktu saat ini sesuai dengan permintaan user. Namun jika waktu nya belum sesuai, maka program akan sleep selama 1 detik (sleep(1)), dan akan mengupdate waktu saat ini hingga waktu sesuai dengan permintaan user.

## Soal 2
#### Code:
```
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

```
Dalam soal 2, program melalui proses untuk menjadikan daemon program. Dalam daemon program ini, pertama - tama program akan membuat program kill yang executable untuk menghentikan proses yang dijalankan oleh program ini, dimana terdapat 2 opsi berdasarkan input argumen dari user. 
- Opsi pertama ialah mematikan seluruh proses dari program ini. Menggunakan command "kill -9 -pid".
- Opsi kedua ialah menunggu proses yang telah berjalan hingga selesai, dan menghentikan proses dari program ini. Menggunakan command "kill pid"

Untuk membuat program ini, digunakan fungsi "fopen" untuk membuat file, dan "fprintf" untuk menulis kedalam file tersebut. Ketika program kill ini dijalankan, maka command akan berjalan dan kemudian file dari program kill akan dihapus.

Kemudian, program membuat sebuah proses untuk membuat direktori tiap 30 detik per direktorinya. Setelah direktori dibuat, program akan mendownload foto dengan ukuran "t2 = (t2%1000) + 100" berdasarkan time dan dari "https://picsum.photos/" sebanyak 20 buah kedalam direktori tersebut tiap 5 detik per fotonya. Setelah direktori telah diisi oleh 20 foto yang didownload, maka direktori tersebut akan di zip dan folder dari direktori tersebut dihapus.

## Soal 3
#### Code:
```
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
```
Dalam soal 3, terdapat tiga proses child utama. Child pertama untuk membuat directory indomie, child kedua untuk membuat directory sedaap, dan child 3 untuk unzip jpg.zip ke modul2. Setelah ketiga proses dilakukan, file dan folder dipindah ke tempat yang ditentukan. Terjadi beberapa operasi string, directory dan penggunaan fungsi checkfile untuk mengecek direktori atau file. Direktori dipindah ke folder indomie, dan file lalu dipindah ke folder sedaap. Setelah pemindahan direktori, dilakukan lagi operasi directory dan string. Digunakan fungsi fill untuk membuat beberapa child proses untuk mengisi direktori2 yang ada dengan file coba1.txt dan coba2.txt.
