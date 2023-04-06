#include <stdio.h>

float old_average = 0;
float new_average = 0;

void moving_average(float new_data, int n, float *average) {
    *average += (new_data - *average) / n;
}

int main() {
    float new_data = 0;

    while (1) {
        printf("값을 넣으세요: ");
        scanf("%f", &new_data);

        moving_average(new_data, 5, &new_average);
        printf("%f\n", new_average);
    }

    return 0;
}
