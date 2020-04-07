#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <algorithm>
#include <fstream>
#include "bitmap_image.hpp"
#include "convertgris.cpp"

using namespace std;

void changegris(bitmap_image & bmp, unsigned int l1, unsigned int l2){
    unsigned int cs2=bmp.width();
    for (auto l=l1;l<=l2;l++) {
        for (unsigned int c=0;c<=cs2;++c) {
            unsigned char r1,g1,b1;
            bmp.get_pixel(c,l,r1,g1,b1);
            unsigned char total = (r1+g1+b1)/3;
            bmp.set_pixel(c,l,total,total,total);
        }
    }
}

void convertirgris(std::string const & filename, unsigned int N){
    bitmap_image bmp(filename);
    std::vector<std::thread> threads;
    for (int i = 0; i < N; ++i) {
        unsigned int i1=i*(bmp.height()/N);
        unsigned int i2=(i+1)*(bmp.height()/N)-1;
        if(i == (N-1))
            i2=bmp.height()-1;
        threads.push_back(std::thread(changegris,std::ref(bmp),i1,i2));
    }
    for(auto & t : threads)
        t.join();
    bmp.save_image("sortie.bmp");
}

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

          compt++;
        }
    }else
        wait(NULL);

    return 0;
}
