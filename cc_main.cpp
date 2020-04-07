#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <algorithm>
#include <fstream>
#include <thread>
#include "bitmap_image.hpp"
#include "convertgris.cpp"
#include "convertirbmp3.cpp"

using namespace std;

int main(int argc, char*argv[])
{
    unsigned int N = std::atoi(argv[1]);

    const char * ligne_c;
    string ligne_s;

    char * argu[2];
    argu[1] = NULL;
    int compt = 0;

    pid_t pid = fork();

    if (pid == 0) {
        while( compt < 100) {
           printf("MonShell> ");
           std::cin >> ligne_s;
          // ligne_c = ligne_s.c_str();

           argu[0] = (char*) ligne_c;

          // cout << ligne_s << endl;

           pid_t pid_2 = fork();

           if (pid_2 == 0) {
           //   cout << pid_2 << endl;
               execvp(ligne_c,argu);

           }else
               wait(NULL);

           if (ligne_s.compare("quitter") == 0){
               exit(0);
           }

           if (ligne_s.compare("convertirgris") == 0){
                ConvertGris G("image.bmp",N);
           }

           if (ligne_s.compare("convertirbmp3") == 0){
                ConvertBMP3 B("Illustration_campus_sciences2.jpg","toto.bmp");
           }

          compt++;
        }
    }else
        wait(NULL);

    return 0;
}
