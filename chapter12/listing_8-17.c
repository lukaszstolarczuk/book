/*
Copyright (c) 2019, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * listing_8-17.c -- example of reading from persistent memory with a write
 *                   dependency
 */

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd, *ptr, *data, *flag;

    fd = open("/mnt/pmem/file", O_CREAT|O_RDWR, 0666);
    posix_fallocate(fd, 0, 2 * sizeof(int));

    ptr = (int *) mmap(NULL, 2 * sizeof(int), PROT_READ|PROT_WRITE,
            MAP_SHARED_VALIDATE | MAP_SYNC, fd, 0);

    data = &(ptr[1]);
    flag = &(ptr[0]);
    if (*flag == 1)
        printf("data = %d\n", *data);

    munmap(ptr, 2 * sizeof(int));
    return 0;
}
