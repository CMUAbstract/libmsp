#ifndef _MY_ASSERT_H
#define _MY_ASSERT_H

#define ASSERT(cond,message) \
    if(!(cond)) { \
        printf("%s \r\n", #message);\
        while(1); \
    } \


#endif
