#ifndef QQ_H_
#define QQ_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#ifdef __APPLE__
    #include <sys/uio.h>
#else
    #include <sys/io.h>
#endif

struct Quote {
    uint32_t time;
    double price;
};

struct Quote_List {
    uint32_t size;
    struct Quote *Quotes;
};

struct Quote_List qq_file_to_Quote_List(char *filename);

#endif // QQ_H_
