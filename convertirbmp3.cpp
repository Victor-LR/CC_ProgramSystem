#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <algorithm>
#include <thread>
#include "bitmap_image.hpp"


class ConvertBMP3 {

public:

    ConvertBMP3(std::string entree,std::string sortie){
        convertirBMP3(entree,sortie);
    };

         void convertirBMP3(std::string entree,std::string sortie){
            std::string str ="convert " + entree + " BMP3:" + sortie;
            std::cout << str <<std::endl;
             const char *command =str.c_str();
            system(command);
	 }

};


