#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <algorithm>
#include <thread>
#include "bitmap_image.hpp"


class Pixeliser {

    public:

    Pixeliser(std::string const & filename,unsigned int nthreads){
        pixeliser(filename,nthreads);
    };


    void static pixel(bitmap_image & bmp, unsigned int l1, unsigned int l2){
        unsigned int cs2=bmp.width();
        for (auto l=l1;l<=l2;l++) {
            for (unsigned int c=0;c<=cs2;++c) {
                unsigned char r1,g1,b1;
                for (int i = 0; i <10 ;i++) {
                    bmp.get_pixel(c,l,r1,g1,b1);

                }
                bmp.get_pixel(c,l,r1,g1,b1);
                unsigned char total = (r1+g1+b1)/3;
                bmp.set_pixel(c,l,total,total,total);
            }
        }
    }

    void pixeliser(std::string const & filename, unsigned int nthreads) {
        bitmap_image bmp(filename);
        std::vector<std::thread> threads;
        for (unsigned int i=0; i<nthreads; ++i) {
            unsigned int i1=i*(bmp.height()/nthreads);
            unsigned int i2=(i+1)*(bmp.height()/nthreads)-1;
            if (i == (nthreads-1))
                i2=bmp.height()-1;
            std::cout << i1 << " " << i2 << std::endl;
            threads.push_back(std::thread(pixel, std::ref(bmp), i1, i2));
        }
        for (auto & t : threads)
            t.join();
        bmp.save_image("result.bmp");

    }
};
