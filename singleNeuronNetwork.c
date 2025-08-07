#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

float train_data[][2] = {
    {0,0},
    {1,2},
    {2,4},
    {4,8},
    {5,10},
    {6,12}
};

float rand_float(void){
    return (float) rand()/(float) RAND_MAX;
}

int main()
{
    srand(time(NULL));
    float intial_random_weight = rand_float()*10.0f;
    printf("Generated Weight : %f \n ",intial_random_weight);
    return 0;
}
