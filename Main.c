#include <stdio.h> 
#include <string.h>

#define MAX 20 // Maximum number of appliances

struct Appliances{ 
    char name[100];
    float wattage;
    float hours_used;
    float daily_kwh;
    float monthly_kwh;
}; // Structure to hold appliance information

struct Appliances appliances[MAX]; // Array to store appliances

// Global variables
int app_count = 0;
double elec_cost = 0.0;
char filename[100];

// Function prototypes
void loginUser();
void loadElectricityCost();
void saveElectricityCost();
void loadAppliances();
void saveAppliances();
void changeElectrictyRate();
void calculateConsumption(int index);
float getTotalMonthlyKwh();
void addAppliance();
void removeAppliance();
void viewAppliancesList();
void viewDailyConsump();
void viewMonthlyConsump();
void viewTotalConsump();
void compareBill();
void highestConsumpApp();
void suggestions();


int main(void){
    int choice;

    // Load electricity cost and user information
    loadElectricityCost();
    printf("===== ELECTRICITY USAGE ANALYZER =====\n");

    loginUser();
    loadAppliances();

    do {
        // Display menu
        printf("========== MENU ==========\n");
        printf("1. Update Electricity Rate\n");
        printf("2. Add Appliance\n");
        printf("3. Remove Appliance\n");
        printf("4. View Daily Consumption\n");
        printf("5. View Monthly Consumption\n");
        printf("6. View Total Consumption\n");
        printf("7. Compare Actual Bill\n");
        printf("8. Highest Consuming Appliance\n");
        printf("9. Suggestions/Recommendations\n");
        printf("10. View List of Appliances\n");
        printf("11. Exit\n");
        printf("\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        // Handle user choice
        switch (choice){

            case 1: 
                changeElectrictyRate();
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
                viewAppliancesList();
                break;

            case 11:
                printf("\nThank you for using the program! Bye...\n");
                break;

            default:
                printf("Invalid choice!");
            }

    } while (choice != 11);

    return 0;

}

// Function definitions

// Function to handle user login and file management
void loginUser(){

    char username[50];

    printf("\nEnter username (letters, numbers, and underscore only): ");
    scanf("%s", username);

    sprintf(filename, "%s_appliances.txt", username);

    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        printf("New user detected. Creating file...\n");
        fp = fopen(filename, "w");

        if(fp == NULL) {
            printf("Error creating file!\n");
            return;
        } 

        fclose(fp);

        printf("Welcome, %s!\n", username);

        } else {
            printf("Welcome back, %s!\n", username);
            fclose(fp);
        }
    }

// Function to load electricity cost from file
void loadElectricityCost(){
    FILE *fp = fopen("electricityRate.cfg", "r");

    if(fp == NULL){
        printf("File not found\n");
        return;
    }

    fscanf(fp, "%lf", &elec_cost);
    fclose(fp);
}

// Function to save electricity cost to file
void saveElectricityCost(){
    FILE *fp = fopen("electricityRate.cfg", "w");

    if(fp == NULL){
        printf("File not found\n");
        return;
    }

    fprintf(fp, "%lf", elec_cost);
    fclose(fp);

}

// Function to load appliances from file
void loadAppliances(){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        return;
    }

    app_count = 0;

    while(app_count < MAX && fscanf(fp, "%s %f %f %f %f", 
        appliances[app_count].name,
        &appliances[app_count].wattage,
        &appliances[app_count].hours_used,
        &appliances[app_count].daily_kwh,
        &appliances[app_count].monthly_kwh) == 5) 
    {
    app_count++;
    }
    fclose(fp);
}

// Function to save appliances to file
void saveAppliances() {
    FILE *fp = fopen(filename, "w");

    if(fp == NULL){
        printf("Error saving appliances.\n");
        return;
    }

    for(int i = 0; i < app_count; i++){
        fprintf(fp, "%s %.2f %.2f %.2f %.2f\n", appliances[i].name,
        appliances[i].wattage,
        appliances[i].hours_used,
        appliances[i].daily_kwh,
        appliances[i].monthly_kwh);
    }
    fclose(fp);
}

// Function to change electricity rate
void calculateConsumption(int index){
    appliances[index].daily_kwh = (appliances[index].wattage * appliances[index].hours_used) / 1000.0;
    appliances[index].monthly_kwh = appliances[index].daily_kwh * 30.0;
}

// Function to get total monthly kWh consumption
float getTotalMonthlyKwh() {
    float total = 0;
    for(int i = 0; i < app_count; i++)
        total += appliances[i].monthly_kwh;
    return total;
}

// Function to change electricity rate
void changeElectrictyRate() {
    printf("----- Change Electricity Rate -----\n");

    printf("Enter new electricity cost per kWh: ");
    scanf("%lf", &elec_cost);

    while(elec_cost <= 0) {
        printf("Invalid input. Enter again: ");
        scanf("%lf", &elec_cost);
    }
    saveElectricityCost();
    printf("Electricity rate updated successfully.\n");
}

// Function to add a new appliance
void addAppliance() {
    if(app_count >= MAX) {
        printf("Appliance list is full!\n");
        return;
    }

    printf("Enter appliance name: ");
    scanf(" %[^\n]", appliances[app_count].name);

    printf("Enter wattage: ");
    scanf("%f", &appliances[app_count].wattage);
    while(appliances[app_count].wattage <= 0) 
    {  
        printf("Invalid. Enter again: ");
        scanf("%f", &appliances[app_count].wattage);
    }

    printf("Enter hours used per day: ");
    scanf("%f", &appliances[app_count].hours_used);
    while(appliances[app_count].hours_used <= 0 || appliances[app_count].hours_used > 24) 
    { 
        printf("Invalid. Enter again: ");
        scanf("%f", &appliances[app_count].hours_used);
    }

    calculateConsumption(app_count);

    app_count++;

    saveAppliances();

    printf("Appliance added successfully.\n");
}

// Function to remove an appliance
void removeAppliance() {
    char name[100];
    int found = 0;

    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    printf("Enter appliance name to remove: ");
    scanf(" %[^\n]", name);

    for(int i = 0; i < app_count; i++) {
        if(strcasecmp(appliances[i].name, name) == 0) {
            found = 1;

        for(int j = i; j < app_count -1; j++) {
            appliances[j] = appliances [j+1];
        }

        app_count--;

        saveAppliances();

        printf("Appliance removed successfully!\n");
        break;
        }
    }
    
    if(!found) {
        printf("Appliance not found.\n");
    }
}

// Function to view list of appliances
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

// Function to view daily consumption of appliances
void viewDailyConsump(){
    float total = 0;

    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    printf("*-*-* Daily Consumption *-*-*\n");

    for(int i = 0; i< app_count; i++) {
        printf("%s - %.2f kWh/day\n",
            appliances[i].name,
            appliances[i].daily_kwh);
        total += appliances[i].daily_kwh;
    }
    printf("Total: %.2f kWh/day\n", total);
}

// Function to view monthly consumption of appliances
void viewMonthlyConsump() {
    float total = 0;

    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    printf("*-*-* Monthly Consumption *-*-*\n");

    for(int i = 0; i < app_count; i++) {
        printf("%s - %.2f kWh/month\n",
            appliances[i].name,
            appliances[i].monthly_kwh);
        total += appliances[i].monthly_kwh;
    }
    printf("Total: %.2f kWh/month\n", total);
}

// Function to view total consumption and estimated bill
void viewTotalConsump() {
    float total_kwh = 0;

    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    if(elec_cost <= 0) {
            printf("No electricity rate set. Please set one now.\n");
            changeElectrictyRate();
    }

    total_kwh = getTotalMonthlyKwh();
    printf("----- Total Bill -----\n");
    printf("Total kWh: %.2f\n", total_kwh);
    printf("Estimated Cost: ₱%.2f\n", total_kwh * elec_cost);
}

// Function to compare estimated bill with actual bill
void compareBill() {
    float total_kWh = 0;
    float estimated_bill;
    float actual_bill;

    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    if(elec_cost <= 0) {
            printf("No electricity rate set. Please set one now.\n");
            changeElectrictyRate();
    }

    total_kWh = getTotalMonthlyKwh();
    estimated_bill = total_kWh * elec_cost;

    printf("-*-*- Bill Comparison -*-*-*\n");
    printf("Estimated Bill: ₱%.2f\n", estimated_bill);

    printf("Enter actual electricity bill: ");
    scanf("%f", &actual_bill);

    float difference = actual_bill - estimated_bill;

    printf("Difference: ₱%.2f\n", difference);

    if (difference > 0) {
        printf("You are using more electricity than estimated.\n");
    } else if (difference < 0) {
        printf("You are using less electricity than estimated.\n");
    } else {
        printf("Your usage matches the estimate.\n");
    }
}

// Function to identify highest consuming appliance
void highestConsumpApp() {
    int max_index = 0;

    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    for(int i = 1; i < app_count; i++){
        if(appliances[i].monthly_kwh > appliances[max_index].monthly_kwh) {
            max_index = i;
        }
    }
    printf("Highest consuming appliance: %s\n", appliances[max_index].name);
    printf("Consumption: %.2f kWh/month\n", appliances[max_index].monthly_kwh);
}

// Function to provide suggestions based on consumption
void suggestions() { 
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    float total = getTotalMonthlyKwh();
    float average = total / app_count;
    int flagged = 0;

    printf("----- Suggestions -----\n");

    for(int i = 0; i < app_count; i++) {
        if(appliances[i].monthly_kwh > average * 0.7) 
        {  
            printf("- Consider reducing usage of %s\n", appliances[i].name);
            flagged++;
        }
    }
    
    if(flagged == 0)
        printf("All appliances have similar consumption. Usage looks balanced!\n");
}