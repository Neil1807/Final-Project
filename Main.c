#include <stdio.h>

#define MAX 20

struct Appliances{
    char name[100];
    float wattage;
    float hours_used;
    float daily_kwh;
    float monthly_kwh;
};

struct Appliances appliances[MAX];

int app_count = 0;
double elec_cost = 0.0;

void loadElectricityCost();
void saveElectricityCost();

int main(void){

    int choice;

    loadElectricityCost();

    printf("Welcome User!\n");

    if (elec_cost <= 0){
        printf("Enter electricity cost per kwh");
        scanf("%lf", &elec_cost);

        while(elec_cost <= 0){
            printf("Enter electricity cost per kwh");
            scanf("%lf", &elec_cost);
        }

        saveElectricityCost();
    }

    do {
        printf("========== MENU ==========\n");

        printf("1. Change Electricity Rate\n");
        printf("2. Add Appliance\n");
        printf("3. Remove Appliance\n");
        printf("4. View Daily Consumption\n");
        printf("5. View Monthly Consumption\n");
        printf("6. View Total Consumption\n");
        printf("7. Compare Actual Bill\n");
        printf("8. Highest Consuming Appliance\n");
        printf("9. Suggestions/Recommendations\n");
        printf("10. Exit\n");

        printf("Enter choice");
        scanf("%d", &choice);

        switch (choice){

            case 1: 
                changeElectrictyBill();
                break;
            
            case 2: 
                addAppliance();
                break;

            case 3: 
                removeAppliance();
                break;

            case 4: 
                viewDailyConsump();
                break;

            case 5: 
                viewMonthlyConsump();
                break;

            case 6: 
                viewTotalConsump();
                break;

            case 7: 
                compareBill();
                break;

            case 8: 
                highestConsumpApp();
                break;

            case 9: 
                suggestions();
                break;
            
            case 10:
                printf("\nBye bye!\n");
                break;
            
            default:
                printf("Invalid choice");


            }
    } while (choice != 10);


    
}

void loadElectricityCost(){
    FILE *fp = fopen("electricityRate.cfg", "r");

    if(fp == NULL){
        printf("File not found\n");
        return;
    }
    
    fscanf(fp, "%lf", elec_cost);
    fclose(fp);
}

void saveElectricityCost(){
    FILE *fp = fopen("electricityRate.cfg", "w");

    if(fp == NULL){
        printf("File not found\n");
        return;
    }

    fprintf(fp, "%lf", elec_cost);
    fclose(fp);

}