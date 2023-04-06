#include <stdio.h>

float old_average = 0;
float new_average = 0;
float data[5] = { 0, 0, 0, 0, 0 };

void moving_average(float a, float K) {
    new_average = (old_average * K) + (a * (1 - K));
    old_average = new_average;
}

void moving_average_5data(float a) {
    for (int i = 0; i < 4; i++) {
        data[i] = data[i + 1];
    }
    data[4] = a;
    new_average = old_average + (data[4] - data[0]) / 5;
    old_average = new_average;
}

int main(void) {
    float b = 0;
    float K = 0.7;
    int count = 0;

    while (1) {
        printf("값을 넣으세요 : ");
        scanf("%f", &b);

        if (count < 5) {
            moving_average(b, K);
            printf("%f \n", new_average);
            data[count] = b;
            count++;
        }
        else {
            moving_average_5data(b);
            printf("%f \n", new_average);
        }
    }
    return 0;
}
