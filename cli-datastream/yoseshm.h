/**
    \file yoseshm.h
    \brief raw shm functions
**/
#ifndef __YOSESHM_H__
#define __YOSESHM_H__

#include <stdint.h>

typedef unsigned char byte;

class myShm
{
private:
    const int SHMKEY = 0x0111C0DE;
public:
    static void saveToShm(uint32_t size, const void* buffer);
    static void readFromShm(uint32_t& size, void* buffer);
    static void removeShm();

};

#endif  // __YOSESHM_H__
