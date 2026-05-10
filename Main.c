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
double updateElectrictyCost();
void loadAppliances();
void saveAppliances();
void viewAppliancesList();
void calculateConsumption(int index);
void addAppliance();
void removeAppliance();
void viewDailyConsump();
void viewMonthlyConsump();
void viewTotalConsump();
void highestConsumpApp();
void suggestions();
void compareBill();

int main(void){
    int choice;

    loadElectricityCost();
    loadAppliances();

    printf("Welcome User!\n");

    if (elec_cost <= 0) {
        updateElectrictyCost();
    }

    do {
        printf("\n========== MENU ==========\n");
        printf("1. View List of Appliances\n");
        printf("2. Change Electricity Cost\n");
        printf("3. Add Appliance\n");
        printf("4. Remove Appliance\n");
        printf("5. View Daily Consumption\n");
        printf("6. View Monthly Consumption\n");
        printf("7. View Total Consumption\n");
        printf("8. Compare Actual Bill\n");
        printf("9. Highest Consuming Appliance\n");
        printf("10. Suggestions/Recommendations\n");
        printf("11. Exit\n");

        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: viewAppliancesList(); break;
            case 2: elec_cost = updateElectrictyCost(); break;
            case 3: addAppliance(); break;
            case 4: removeAppliance(); break;
            case 5: viewDailyConsump(); break;
            case 6: viewMonthlyConsump(); break;
            case 7: viewTotalConsump(); break;
            case 8: compareBill(); break;
            case 9: highestConsumpApp(); break;
            case 10: suggestions(); break;
            case 11: printf("\nBye bye!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 11);
}

void loadElectricityCost(){
    FILE *fp = fopen("electricityRate.cfg", "r");
    if(fp == NULL){
        printf("File not found.\n");
        return;
    }
    fscanf(fp, "%lf", &elec_cost);
    fclose(fp);
}

void saveElectricityCost(){
    FILE *fp = fopen("electricityRate.cfg", "w");
    if(fp == NULL){
        printf("File not found.\n");
        return;
    }
    fprintf(fp, "%lf", elec_cost);
    fclose(fp);
}

double updateElectrictyCost(){
    double new_cost;

    printf("Enter updated electricity cost: ");
    
    while (scanf("%lf", &new_cost) != 1 || new_cost <= 0){
        printf("Invalid input. Please enter a positive numerical number.");

        while(getchar() != '\n');
    }

    elec_cost = new_cost;
    saveElectricityCost();
}

void addAppliance(){
    if (app_count >= MAX) {
        printf("Maximum appliances reached.\n");
        return;
    }

    printf("\nEnter appliance name: ");
    scanf(" %[^\n]", appliances[app_count].name);

    printf("Enter wattage: ");
    scanf("%f", &appliances[app_count].wattage);

    printf("Enter hours used per day: ");
    scanf("%f", &appliances[app_count].hours_used);

    calculateConsumption(app_count);
    app_count++;
    saveAppliances();

    printf("Appliance added successfully.\n");
}

void loadAppliances(){
    FILE *fp = fopen("appliances.txt", "r");
    if (fp == NULL) return;

    if (fscanf(fp, "%d\n", &app_count) != 1) {
        fclose(fp);
        return;
    }

    for (int i = 0; i < app_count; i++) {
        fscanf(fp, " %[^|]|%f|%f\n", appliances[i].name, &appliances[i].wattage, &appliances[i].hours_used);
        calculateConsumption(i);
    }

    fclose(fp);
}

void saveAppliances(){
    FILE *fp = fopen("appliances.txt", "w");
    if (fp == NULL) return;

    fprintf(fp, "%d\n", app_count);
    for (int i = 0; i < app_count; i++) {
        fprintf(fp, "%s|%.2f|%.2f\n", appliances[i].name, appliances[i].wattage, appliances[i].hours_used);
    }
    fclose(fp);
}

void calculateConsumption(int index){
    appliances[index].daily_kwh = (appliances[index].wattage * appliances[index].hours_used) / 1000.0;
    appliances[index].monthly_kwh = appliances[index].daily_kwh * 30.0;
}

void viewAppliancesList(){
    if (app_count == 0) {
        printf("\nNo appliances found.\n");
        return;
    }
    
    printf("\n%-4s %-20s %-10s %-10s\n", "ID", "Name", "Watts", "Hours/Day");
    printf("----------------------------------------------\n");

    for (int i = 0; i < app_count; i++) {
        printf("%-4d %-20s %-10.2f %-10.2f\n", 
            i + 1, appliances[i].name, appliances[i].wattage, appliances[i].hours_used);
    }
}

void removeAppliance(){}
void viewDailyConsump(){}
void viewMonthlyConsump(){}
void viewTotalConsump(){}
void highestConsumpApp(){}
void suggestions(){}
void compareBill(){}