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

#define train_count sizeof(train_data)/sizeof(train_data[0]) // to dynamically generate the number of the elements in the train data


float rand_float(void){
    return (float) rand()/(float) RAND_MAX;
}

float cost(float weight){
    float result=0.0f,y,prediction,distance;
    for (size_t i = 0; i < train_count; i++)
    {
        y=train_data[i][0];
        prediction = y*weight;
        distance = train_data[i][1]-prediction;
        distance*=distance;
        result+=distance;
    }
    return result/train_count;
    
}


int main()
{
    srand(5000);
    float intial_random_weight = 1.0f + rand_float()*9.0f;// to make the numbers generate between 1 and 10 . im just gonna rawdog a constant .
    printf("Generated Weight : %f \n ",intial_random_weight);

    printf("initial cost : %f \n ",cost(intial_random_weight));

    return 0;       
}
