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
//methods for calculating the accuracy of the model

// float accuracy(float weight){
//     float original_total = 0.0f,calculated_total=0.0f,percentage=0.0f;
//     for (size_t i = 0; i < train_count; i++)
//     {
//         original_total+=train_data[i][1];
//         calculated_total+= train_data[i][0]*weight;
//     }
//     return calculated_total/train_count;
    
// }

float r2_score(float weight){
    float ss_res = 0.0f; // residual sum of squares
    float ss_tot = 0.0f; // total sum of squares
    float mean_y = 0.0f;

    // Step 1: Calculate mean of actual values
    for (size_t i = 0; i < train_count; i++){
        mean_y += train_data[i][1];
    }
    mean_y /= train_count;

    // Step 2: Calculate SS_res and SS_tot
    for (size_t i = 0; i < train_count; i++){
        float predicted = train_data[i][0] * weight;
        float actual = train_data[i][1];

        ss_res += (actual - predicted) * (actual - predicted);
        ss_tot += (actual - mean_y) * (actual - mean_y);
    }

    return 1.0f - (ss_res / ss_tot);
}


//most suitable method for computing the accuracy

// int regression_accuracy_percent(float weight) {
//     float r2 = r2_score(weight);
//     float accuracy = r2 * 100.0f;

//     if (accuracy < 0) accuracy = 0; // clamp to 0
//     if (accuracy > 100) accuracy = 100; // clamp to 100 (not usually needed)
    
//     return (int)accuracy;
// }




int main()
{
    srand(5000);
    float weight = 1.0f + rand_float()*9.0f;// to make the numbers generate between 1 and 10 . im just gonna rawdog a constant .
    printf("Generated Weight : %f \n",weight);

    float rate = 1e-3;
    float eps = 1e-3;

    printf("predicted values before training \n");
    for (size_t i = 0; i < train_count; i++)
    {
        printf("input value: %f actual output : %f , predicted output : %f difference : %f \n",train_data[i][0],train_data[i][1],train_data[i][0]*weight, fabs(train_data[i][1]-train_data[i][0]*weight));
    }
    

    for (size_t i = 0; i < 100000; i++)
    {
        float updated_cost = (cost(weight+eps)-cost(weight))/eps;
    
        weight-= rate*updated_cost;
        // printf("updated cost after iteration %d : %f \n",i+1,cost(weight));
    }

    printf("calibrated weight : %f \n",weight);

    printf("predicted values after training \n");
    float diff = 0.0f;
    for (size_t i = 0; i < train_count; i++)
    {
        printf("input value: %f actual output : %f , predicted output : %f difference : %f \n",train_data[i][0],train_data[i][1],train_data[i][0]*weight,fabs(train_data[i][1]-train_data[i][0]*weight));
        diff+=fabs(train_data[i][1]-train_data[i][0]*weight);
    }
    printf("total diff between predicted result : %f \n",diff);

    printf("accuracy of model : %f ",r2_score(weight));

    return 0;       
}
