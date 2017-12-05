#include <iostream>
#include "Writer.h"
#include "ThreadPool.h"
#include "Factorizator.h"
#include <getopt.h>
int getopt(int argc, char * const argv[],
           const char *optstring);
extern char *optarg;
int main(int argc, char *argv[]) {
    Writer &writer=Writer::Instance();
    writer.open("res.txt");//No setting
    std::ifstream read;
    bool isOpen = false;
    uint64_t in;
    int res = 0;
    while((res = getopt(argc, argv, "i:o:")) != -1){
        if(res == 'i'){
            isOpen = true;
            //std::cout << optarg << std::endl;
            read.open(optarg);
        }
        if(res == 'o'){
            writer.open(optarg);
        }
        if(res == '?'){
            std::clog << "Wrong or unknown arguments\n";
        }
    }
    if(!isOpen){
        std::cout << "Please use -i, to input file with numbers\n";
        return 0;
    }

    ThreadPool pool(4);

    while(read >> in){
        //std::cout << in << std::endl;
        auto fun = [&writer, in] {

            std::string res = Factorizator(in).getFactorization() + "\n";
            writer.push(res);
        };
        pool.execute(fun);
    }


    std::thread work =std::thread([&pool]{
        std::string in;
        while(pool.jobs() > 0){
            std::cin >> in;
            if(in == "pause"){
                pool.stop();
            }
            if(in == "resume"){
                pool.resume();
            }
            if(in == "exit"){
                pool.exit();
            }
        }
    });
    work.detach();
}