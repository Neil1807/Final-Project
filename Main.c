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

    // Prompt for username
    printf("\nEnter username (letters, numbers, and underscore only): ");
    scanf("%s", username);

    // Create filename based on username
    sprintf(filename, "%s_appliances.txt", username);

    // Check if file exists
    FILE *fp = fopen(filename, "r");

    // If file doesn't exist, create it
    if(fp == NULL){
        printf("New user detected. Creating file...\n");
        fp = fopen(filename, "w");

        if(fp == NULL) {
            printf("Error creating file!\n");
            return;
        } 

        fclose(fp);

        printf("Welcome, %s!\n", username);

        } 
    // If file exists, welcome back user
    else{
        printf("Welcome back, %s!\n", username);
        fclose(fp);
        }
    }

// Function to load electricity cost from file
void loadElectricityCost(){
    // Open file to read electricity cost
    FILE *fp = fopen("electricityRate.cfg", "r");

    // If file doesn't exist, return
    if(fp == NULL){
        printf("File not found\n");
        return;
    }

    // Read electricity cost from file
    fscanf(fp, "%lf", &elec_cost);
    fclose(fp);
}

// Function to save electricity cost to file
void saveElectricityCost(){
    // Open file to write electricity cost
    FILE *fp = fopen("electricityRate.cfg", "w");

    // If file doesn't exist, return
    if(fp == NULL){
        printf("File not found\n");
        return;
    }

    // Write electricity cost to file
    fprintf(fp, "%lf", elec_cost);
    fclose(fp);

}

// Function to load appliances from file
void loadAppliances(){
    // Open file to read appliances
    FILE *fp = fopen(filename, "r");

    // If file doesn't exist, return
    if(fp == NULL) {
        return;
    }

    // Read appliances from file into array
    app_count = 0;

    // Read each line of the file and populate the appliances array
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
    // Open file to write appliances
    FILE *fp = fopen(filename, "w");

    // If file doesn't exist, return
    if(fp == NULL){
        printf("Error saving appliances.\n");
        return;
    }

    // Write appliances from array to file
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
    // Calculate daily and monthly kWh consumption for the appliance at the given index
    appliances[index].daily_kwh = (appliances[index].wattage * appliances[index].hours_used) / 1000.0;
    appliances[index].monthly_kwh = appliances[index].daily_kwh * 30.0;
}

// Function to get total monthly kWh consumption
float getTotalMonthlyKwh() {
    // Calculate total monthly kWh consumption by summing the monthly_kwh of all appliances
    float total = 0;
    for(int i = 0; i < app_count; i++)
        total += appliances[i].monthly_kwh;
    return total;
}

// Function to change electricity rate
void changeElectrictyRate() {
    // Prompt user to enter new electricity cost per kWh and validate input
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
    // Check if appliance list is full
    if(app_count >= MAX) {
        printf("Appliance list is full!\n");
        return;
    }

    // Prompt user to enter appliance details and validate input
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
    // Prompt user to enter appliance name to remove and validate input
    char name[100];
    int found = 0;

    // Check if there are appliances to remove
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    // Prompt user to enter appliance name to remove
    printf("Enter appliance name to remove: ");
    scanf(" %[^\n]", name);

    // Search for appliance by name (case-insensitive)
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
    // If appliance not found, display message
    if(!found) {
        printf("Appliance not found.\n");
    }
}

// Function to view list of appliances
void viewAppliancesList(){
    // Check if there are appliances to display
    if (app_count == 0) {
        printf("\nNo appliances found.\n");
        return;
    }
    // Display list of appliances in a formatted table
    printf("\n%-4s %-20s %-10s %-10s\n", "ID", "Name", "Watts", "Hours/Day");
    printf("----------------------------------------------\n");

    // Loop through appliances and display their details
    for (int i = 0; i < app_count; i++) {
        printf("%-4d %-20s %-10.2f %-10.2f\n", 
            i + 1, appliances[i].name, appliances[i].wattage, appliances[i].hours_used);
    }
}

// Function to view daily consumption of appliances
void viewDailyConsump(){
    // Check if there are appliances to display
    float total = 0;

    // If no appliances added, prompt user to add first
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    // Display daily consumption of each appliance and total consumption
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
    // Check if there are appliances to display
    float total = 0;

    // If no appliances added, prompt user to add first
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    // Display monthly consumption of each appliance and total consumption
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
    // Check if there are appliances to display
    float total_kwh = 0;

    // If no appliances added, prompt user to add first
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    // If electricity rate not set, prompt user to set it first
    if(elec_cost <= 0) {
            printf("No electricity rate set. Please set one now.\n");
            changeElectrictyRate();
    }

    // Calculate total monthly kWh consumption and display it along with estimated cost
    total_kwh = getTotalMonthlyKwh();
    printf("----- Total Bill -----\n");
    printf("Total kWh: %.2f\n", total_kwh);
    printf("Estimated Cost: ₱%.2f\n", total_kwh * elec_cost);
}

// Function to compare estimated bill with actual bill
void compareBill() {
    // Check if there are appliances to display
    float total_kWh = 0;
    float estimated_bill;
    float actual_bill;

    // If no appliances added, prompt user to add first
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    // If electricity rate not set, prompt user to set it first
    if(elec_cost <= 0) {
            printf("No electricity rate set. Please set one now.\n");
            changeElectrictyRate();
    }

    // Calculate estimated bill based on total monthly kWh consumption and electricity rate
    total_kWh = getTotalMonthlyKwh();
    estimated_bill = total_kWh * elec_cost;

    printf("-*-*- Bill Comparison -*-*-*\n");
    printf("Estimated Bill: ₱%.2f\n", estimated_bill);

    printf("Enter actual electricity bill: ");
    scanf("%f", &actual_bill);

    float difference = actual_bill - estimated_bill;

    printf("Difference: ₱%.2f\n", difference);

    // Provide feedback to user based on whether they are using more, less, or the same amount of electricity compared to the estimate
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
    // Check if there are appliances to display
    int max_index = 0;

    // If no appliances added, prompt user to add first
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    // Loop through appliances to find the one with the highest monthly kWh consumption
    for(int i = 1; i < app_count; i++){
        if(appliances[i].monthly_kwh > appliances[max_index].monthly_kwh) {
            max_index = i;
        }
    }

    // Display the highest consuming appliance and its consumption
    printf("Highest consuming appliance: %s\n", appliances[max_index].name);
    printf("Consumption: %.2f kWh/month\n", appliances[max_index].monthly_kwh);
}

// Function to provide suggestions based on consumption
void suggestions() { 
    // Check if there are appliances to display
    if(app_count == 0){
        printf("No appliances added. Add first!\n");
        return;
    }

    // Calculate average monthly kWh consumption and provide suggestions for appliances that consume significantly more than the average
    float total = getTotalMonthlyKwh();
    float average = total / app_count;
    int flagged = 0;

    // Display suggestions for appliances that consume more than 70% of the average monthly kWh consumption
    printf("----- Suggestions -----\n");

    for(int i = 0; i < app_count; i++) {
        if(appliances[i].monthly_kwh > average * 0.7) 
        {  
            printf("- Consider reducing usage of %s\n", appliances[i].name);
            flagged++;
        }
    }

    // If no appliances are flagged, provide feedback that usage looks balanced
    if(flagged == 0)
        printf("All appliances have similar consumption. Usage looks balanced!\n");
}