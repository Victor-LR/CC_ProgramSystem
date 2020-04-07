#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <algorithm>
#include <thread>
#include "bitmap_image.hpp"


class ConvertGris {

public:

    ConvertGris(std::string const & filename,unsigned int N){
        convertirgris(filename,N);
    };

    void static changegris(bitmap_image & bmp, unsigned int l1, unsigned int l2){
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
        bmp.save_image("sortiegris.bmp");
    }

};

