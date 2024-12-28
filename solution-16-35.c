#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int h(unsigned char *s, unsigned int m,
                     unsigned int *qst, unsigned int r){
    unsigned int sm = 0;
    for (int i = 0; i < m; i++){
        sm += ((unsigned int)s[i] * qst[m-i-1]) % r;
    }
    return sm % r;
}

unsigned int nexth(unsigned int *qst, unsigned int q, unsigned int m,
                unsigned char i, unsigned char j, unsigned int h_pred, unsigned int r) {
    unsigned int new_hash = (h_pred * q) % r;
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
    int r = 1073741824;
    int q = 37;
    unsigned int m = strlen(S);
    unsigned int *qst = calloc(m + 1, sizeof(unsigned int));
    qst[0] = 1;
    for (int i = 1; i < m+1; i++){
        qst[i] = ((qst[i - 1] % r) * (q % r)) % r;
    }

    int k = 0;
    unsigned int hS = h(S, m, qst, r);
    unsigned int hT = h(T, m, qst, r);
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
