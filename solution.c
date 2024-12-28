#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long h(char *s, int m,
            long long *qst, long long r){
    long long sm = 0;
    for (int i = 0; i < m; i++){
        sm += (s[i]*qst[m-i-1])%r;
    }
    return sm % r;
}

long long nexth(long long *qst, long long q, int m,
                char i, char j, long long h_pred, long long r) {
    long long new_hash = (h_pred * q) % r;
    new_hash = (new_hash - (i * qst[m]) % r + j) % r;
    if (new_hash < 0) {
        new_hash += r;
    }

    return new_hash;
}

int eql(char *T, char *S, int start, int end){
    int i = 0;
    while (start != end){
        if (T[start] != S[i])
            return 0;
        start++;
        i++;
    }
    return 1;
}

int main(int argc, char** argv) {
    char *S = argv[1];
    char *T = argv[2];
    long long r = 4294967296;
    long long q = 7;
    int m = strlen(S);
    long long *qst = calloc(m + 1, sizeof(long long ));
    qst[0] = 1;
    for (int i = 1; i < m+1; i++){
        qst[i] = ((qst[i - 1] % r) * (q % r))%r;
    }
    int k = 0;
    long long hS = h(S, m, qst, r);
    long long hT = h(T, m, qst, r);
    int lT = strlen(T), lS = strlen(S);
    while (k < lT - lS + 1){
        if (hS == hT && eql(T, S, k, k + lS)){
            printf("%d ", k);
        }
        hT = nexth(qst, q, m, T[k], T[k + lS], hT, r);
        k++;
    }
    free(qst);
    return 0;
}