// #include <unistd.h>
// #include <time.h>
// #include <stdio.h>

// int main()
// {
//     struct timespec res;
//     double resolution;

//     printf("UserHZ   %ld\n", sysconf(_SC_CLK_TCK));

//     clock_getres(CLOCK_REALTIME, &res);
//     resolution = res.tv_sec + (((double)res.tv_nsec)/1.0e9);

//     printf("SystemHZ %ld\n", (unsigned long)(1/resolution + 0.5));
//     return 0;
//  }