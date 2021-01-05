#include <stdio.h>
#include <stdlib.h>

void init(int*, int*, int);
int index(int*, int);
int genNext(int*, int*, int);
void swap(int*, int*);

int main() {
    int n;
    scanf("%d", &n); 

    int* A = (int*)malloc((n+1)*sizeof(int));
    int* B = (int*)malloc((n+1)*sizeof(int));

    init(A, B, n);

    int flag, invCnt = 0, ind = 0;
    while(1) {

        flag = 0;
        for(int i = 1; i <=n; i++) {
            if(B[i] != 0) 
                flag = 1;
        }
        if(flag == 0) break;

        for(int i = 1; i <= n; i++) {
            printf("%d ", A[i]);
        }

        printf("\t%d\t%d\n", invCnt, ind);

        invCnt = genNext(A, B, n);
        ind = index(A, n);

    }

    return 0;
}

void init(int* A, int* B, int n) {

    for(int i = 1; i <= n; i++) {
        A[i] = i;
        B[i] = -1;
    }
    B[1] = 0;

    return;
}

int index(int* A, int n) {
    int idx = 0;
    for(int i = 1; i <= n-1; i++) {
        if(A[i] > A[i+1])
            idx += i;
    }

    return idx;
}

int genNext(int* A, int* B, int n) {

    static int invCount = 0;
    int idx, max = 0;
    for(int i = 1; i <= n; i++) {
        if((A[i] > max)&&(B[i] != 0)) {
            max = A[i];
            idx = i;
        }
    }

    int idx_new = idx + B[idx];
    swap(&A[idx], &A[idx_new]);
    swap(&B[idx], &B[idx_new]);
    
    if(idx_new < idx)   invCount++;
    else    invCount--;
    
    if((A[1]==max)||(A[n]==max)||(A[idx_new + B[idx_new]] > max))
        B[idx_new] = 0;

    for(int j = 1; j <= n; j++) {
        if((A[j] > max) && (B[j] == 0)) {
            if(j > idx_new) 
                B[j] = -1;
            else if(j < idx_new) 
                B[j] = 1;
        }
    }
    return invCount;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}