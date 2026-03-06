#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    struct timeval tv1;
    struct timeval tv2;
    int fd = open("/dev/log", O_RDONLY);

    int x = 1000000;

    int t1Status = gettimeofday(&tv1, NULL);
    char buffer[5];

    for (int i = 0; i < x; i++)
        read(fd, buffer, sizeof(buffer));
    
    int t2Status = gettimeofday(&tv2, NULL);

    if (t1Status == 0 && t2Status == 0) {
        long timeTaken = (long long)(tv2.tv_sec - tv1.tv_sec) * 1000000 + (long long)(tv2.tv_usec - tv1.tv_usec);
        printf("Intervention total time: %ld\n", timeTaken);
        printf("Avarage time: %lld\n", timeTaken / (x - 1));
    }

    printf("%ld - %ld\n", tv1.tv_usec, tv1.tv_sec);
    printf("%ld - %ld\n", tv2.tv_usec, tv2.tv_sec);

    close(fd);
}