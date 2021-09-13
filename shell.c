/*
Shell
=====
Shell adalah program yang membuat proses child untuk menjalankan string perintah yang diberikan.
Shell berupa infinite looping yang berisi siklus fork--exec--wait.
Lengkapilah kode berikut ini untuk membuat program shell sederhana!
Contoh masukan dan keluaran
---------------------------
    $ date
    Tue Dec  9 13:34:17 WIB 2014
    $ whoami
    auriza
    $ exit
*/


/*
ANGGOTA KELOMPOK:
G64190061 Bobby Williams K. Hara
G64190069 Rizal Mujahiddan
G64190072 Matthew Martianus Henry
G64190105 Maxdha Maxiwinata

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

// pecah string per kata
void split_words(char *string, char **words)
{
    int i;
    words[0] = strtok(string, " \n");
    for (i = 0; words[i]; i++)
        words[i+1] = strtok(NULL, " \n");
}

int main()
{
    long int kosong = -1;
    char **pendata = (char**)malloc(10000000 * sizeof(char*));
    char cmd[1000];                           //  string perintah
    char *args[20];                         //  argumen string perintah
    pid_t pid;

    while (1)
    {
        //  cetak prompt "$ "
        char cwd[PATH_MAX];
        printf("$ %s : ", getcwd(cwd, sizeof(cwd)));
          fgets(cmd, 1000, stdin);
        //  baca string perintah
        if(*cmd != '\n')
        {
            kosong++;
            pendata[kosong] = (char*)malloc((strlen(cmd) + 1) * sizeof(char));
            strcpy(pendata[kosong],cmd);
        }
        else
        {
            continue;
        }
        //  pecah string perintah per argumen
        split_words(cmd, args);

        //  jika perintah = "exit"
        //      break
     
        if(!strcmp(args[0], "exit"))
        {
            free(pendata);
            break;
        }

        //  jika perintah = "cd"
        //      ganti direktori
        //      continue
        
        if(!strcmp(args[0], "cd"))
        {
            if(!strcmp(args[1], "-"))
            {
                chdir("..");
                continue;
            }
            chdir(args[1]);
            continue;
        }

        //  buat proses child:
        //      exec string perintah
        //      cetak pesan error
        //      keluar dengan kode -1
     
        pid = fork();
        if(pid == -1)
        {
            printf("Error!");
            exit(0);
        }
        else if(pid == 0)
        {
            if(!strcmp(args[0],"history")){
                 for(long int i = 0; i<= kosong; i++){
                     printf("%ld %s", i + 1, pendata[i]);
                 }
                 break;
             }
            if(execvp(args[0], args) < 0)
            {
                printf("%s : No such file or directory!\n", args[0]);
                break;
            }
            execvp(args[0], args);
            break;
        }
        else
        {
            wait(NULL);
        }


        //  tunggu child selesai
    }

    return 0;
}
