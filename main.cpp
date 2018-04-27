#include <chrono>
#include <cstdio>
#include <ctime>
#include <algorithm>

const int N = 5;
const int Nd2 = N/2 + N%2;
const int NN = N*N;

FILE * pfile;

std::chrono::time_point<std::chrono::steady_clock> startTime, stopTime;

void print(int a[][N]){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            fprintf(pfile, "%*i", 3, a[i][j]);
        }
        fprintf(pfile, "\n");
    }
    fprintf(pfile, "\n");
}

void foo(int a[][N], int i0, int j0, int num){

    int b[N][N];
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            b[i][j] = a[i][j];
        }
    }

    if (i0 > -1 && i0 < N && j0 > -1 && j0 < N && b[i0][j0] == 0){
        b[i0][j0] = num;

        if(num == NN){
            print(b);
            stopTime = std::chrono::steady_clock::now();
            int ms = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
            printf("%s%i%s", "Program executed in ",  ms, " milliseconds.\n");
            fclose(pfile);
            exit(0);
        }

        int random_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
        std::random_shuffle(random_array, random_array + 8);

        for(int i = 0; i < 8; ++i){

            bool b1 = i0 > 1;
            bool b2 = i0 > 0;
            bool b3 = i0 < N - 1;
            bool b4 = i0 < N - 2;

            switch(random_array[i]){

                case 1: if (b1 && j0 > 0)     foo(b, i0-2, j0-1, num+1); break;
                case 2: if (b1 && j0 < N - 1) foo(b, i0-2, j0+1, num+1); break;

                case 3: if (b2 && j0 > 1)     foo(b, i0-1, j0-2, num+1); break;
                case 4: if (b2 && j0 < N - 2) foo(b, i0-1, j0+2, num+1); break;

                case 5: if (b3 && j0 < N - 2) foo(b, i0+1, j0+2, num+1); break;
                case 6: if (b3 && j0 > 1)     foo(b, i0+1, j0-2, num+1); break;

                case 7: if (b4 && j0 < N - 1) foo(b, i0+2, j0+1, num+1); break;
                case 8: if (b4 && j0 > 0)     foo(b, i0+2, j0-1, num+1); break;

            }
        }
    }
}

int main(){

    pfile = fopen("output.txt", "w");
    startTime = std::chrono::steady_clock::now();
    int a[N][N];

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            a[i][j] = 0;
        }
    }

    srand(time(NULL));

    int index_array1[Nd2];
    int index_array2[Nd2];

    for(int i = 0; i < Nd2; ++i){
        index_array1[i] = i;
        index_array2[i] = i;
    }
    std::random_shuffle(index_array1, index_array1+3);
    std::random_shuffle(index_array2, index_array2+3);

    for(int i = 0; i < Nd2; ++i){
        for(int j = 0; j < Nd2; ++j){
            foo(a, index_array1[i], index_array2[j], 1);
        }
    }

    return 0;
}
