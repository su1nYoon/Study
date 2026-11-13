#include <stdio.h>

int main() {
    int i;
    int coin[6] = {500, 100, 50, 10, 5, 1};
    int count[6] = {0};
    int input, rinput;
    scanf("%d", &input);
    rinput = input;

    for(i = 0; i < 6; i++) {
        count[i] = rinput / coin[i];
        rinput = rinput % coin[i];
    }

    for(i = 0; i < 6; i++) 
        printf("%d : %d\n", coin[i], count[i]);
    return 0;
}