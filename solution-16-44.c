#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long h(unsigned char *s, unsigned int m,
                     unsigned long long *qst, unsigned long long r){
    unsigned long long sm = 0;
    for (int i = 0; i < m; i++){
        sm += ((unsigned int)s[i] * qst[m-i-1]) % r;
    }
    return sm % r;
}

unsigned long long nexth(unsigned long long *qst, unsigned long long q, unsigned int m,
                unsigned char i, unsigned char j, unsigned long long h_pred, unsigned long long r) {
    unsigned long long new_hash = (h_pred * q) % r;
    new_hash = (new_hash - ((unsigned int)i * qst[m]) % r + (unsigned int)j) % r;
    return new_hash;
}

int eql(unsigned char *T, unsigned char *S, int start, int end){
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
    unsigned char *S = (unsigned char *)argv[1];
    unsigned char *T = (unsigned char *)argv[2];
    if (strlen(T) < strlen(S)){
        return 0;
    }
    long long r = 4294967296;
    long long q = 3;
    unsigned int m = strlen(S);
    unsigned long long *qst = calloc(m + 1, sizeof(unsigned long long));
    qst[0] = 1;
    for (int i = 1; i < m+1; i++){
        qst[i] = ((qst[i - 1] % r) * (q % r)) % r;
    }

    int k = 0;
    unsigned long long hS = h(S, m, qst, r);
    unsigned long long hT = h(T, m, qst, r);
    unsigned int lT = strlen(T), lS = strlen(S);

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