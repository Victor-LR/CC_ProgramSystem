#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <algorithm>
#include <thread>

const int LECTURE = 0;
const int ECRITURE = 1;

class Premiers{
public:
    Premiers(unsigned int x, unsigned int y, unsigned int p){
        generepremiers(x,y,p);
    }

    bool estpremier(unsigned long e) {
            for (unsigned int i=2; i<e/2; ++i)
                    if ((e%i) == 0)
                            return false;
            return true;
    }

    void calculepremiers(unsigned long d, unsigned long f, unsigned int fd) {
            for (unsigned long l(d); l<=f; ++l)
                    if (estpremier(l))
                            write(fd,&l,sizeof (l));

    }

    void generepremiers(unsigned long x, unsigned long y, unsigned int p) {
        std::vector<unsigned long> premiers;
        int piperesultats[2];
        pipe(piperesultats);
        for (unsigned int i=0; i<p; ++i) {
            pid_t pid=fork();
            if (pid == 0)
            {
                unsigned long i1=i*((x+y)/p)+1;
                unsigned long i2=(i+1)*((x+y)/p);
                if (i == (p-1))
                    i2=x+y;
                close(piperesultats[LECTURE]);
                calculepremiers(i1,i2, piperesultats[ECRITURE]);
                exit(0);
            }
        }
        ssize_t l;
        close(piperesultats[ECRITURE]);
        do{
            unsigned long p;
            l=read(piperesultats[LECTURE],&p,sizeof (p));
            if (l!=0)
                    premiers.push_back(p);
        }while(l!=0);
        std::sort(premiers.begin(),premiers.end());
        for (auto i:premiers) {
            std::cout<<i<<std::endl;
        }
        for (unsigned int i=0 ;i<p;++i)
                wait(NULL);
    }
};
