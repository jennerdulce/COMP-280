double sqrt(double num){
        double alteredNum;
        double estimate = 1;
        for(int i = 0; i < 5; i++){
                alteredNum = (estimate + (num / estimate)) / 2.0;
                if(i == 4){
                        printf("Final Estimate: %lf \n", alteredNum);
                } else {
                        printf("Current Estimate: %lf \n", alteredNum);

                }
                double errVar = num - (estimate * estimate);
                printf("Error: %lf \n \n", errVar);
                estimate = alteredNum;
        }
        return alteredNum;
}
int main(){
        double someNum;
        printf("Enter a Number: ");
        int result = scanf("%lf", &someNum);
        if(result == 1){
                sqrt(someNum);
        }
        return 0;
}
