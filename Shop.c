#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure representing a vending machine product
struct vendingMachine{
    char name[20];
    int price;
    float weight;
    int num;
};

// Function prototypes
void readInventory(int n, struct vendingMachine products[]);
void writeInventory(int n, struct vendingMachine products[]);
void displayProducts(int n, struct vendingMachine products[]);
void change(int notes);
void updateSales(int bill);
int countLines();

int main(){
    int n;
    char ans;
    // Count the number of products in the inventory
    n = countLines()/4;
    // Create an array of vending machine products
    struct vendingMachine products[n];
    // Read the inventory from the file
    readInventory(n, products);

    printf("\n\tWelcome to the virtual Vending Machine!\n");
    // Display the products in the vending machine
    displayProducts(n, products);
    int productNum, bill = 0, quantity = 1;
    while (1){
        printf("\nWhich product do you want to buy?: ");
        scanf(" %d", &productNum);

        // Check if the product number is valid
        if (products[productNum - 1].num == 0)
            printf("\nInvalid product number, choose another product.\n");
        else if ((productNum - 1) >= n || productNum <= 0){
            printf("\nProduct not in inventory, choose another product.\n");
        }
        else{
            printf("\nHow many do you want to buy?: ");
            scanf(" %d", &quantity);

            // Check if the requested quantity is available
            if (quantity > products[productNum - 1].num)
                printf("\nRequested amount not available, please change quantity or choose another product.\n");
            
            else{
                // Update the product quantity and bill
                products[productNum - 1].num -= quantity;
                bill += products[productNum - 1].price * quantity;
            }
        }

        // Clear the terminal after each loop
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Display the updated products
        displayProducts(n, products);

        printf("\nDo you want to buy anything else? (y/n): ");
        
        scanf(" %c", &ans);
        if(ans == 'n')
            break;

        // Clear the terminal after each loop
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        displayProducts(n, products);
    }

    printf("\nYour total bill is = Tk. %d\n", bill);
    int cash = 0;

    while(1){
        printf("Enter amount you want to pay with: ");
        scanf(" %d", &cash);

        // Check if the entered amount is sufficient
        if(cash < bill)
            printf("\nInsufficient amount entered. Please enter an amount greater or equal to your bill of Tk. %d!\n", bill);
        else {
            printf("\nTk. %d change returned with: \n", cash - bill);
            // Calculate and display the change
            change(cash - bill);
            break;
        }
    }

    // Update the inventory and sales
    writeInventory(n, products); 
    updateSales(bill);

    return 0;
}


// Function to read the inventory from a file
void readInventory(int n, struct vendingMachine products[]){
    FILE *ptr = fopen("inventory.txt", "r");
        for (int i = 0; i < n; i++){
            fscanf(ptr, "%s", products[i].name);
            fscanf(ptr, "%d", &products[i].price);
            fscanf(ptr, "%f", &products[i].weight);
            fscanf(ptr, "%d", &products[i].num);
        }
    fclose(ptr);
}

// Function to write the updated inventory to a file
void writeInventory(int n, struct vendingMachine products[]){
    FILE *ptr = fopen("inventory.txt", "w");
        for (int i = 0; i < n; i++){
            fprintf(ptr, "%s\n", products[i].name);
            fprintf(ptr, "%d\n", products[i].price);
            fprintf(ptr, "%.2f\n", products[i].weight);
            fprintf(ptr, "%d\n", products[i].num);
        }
    fclose(ptr);
}

// Function to display the products in the vending machine
void displayProducts(int n, struct vendingMachine products[]){
    printf("\nName\t\tPrice (BDT)\tWeight (g)\tProducts available\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++){
        printf("[%d] %s\t\t%d\t%.2f\t\t%d\n", i+1, products[i].name, products[i].price, products[i].weight, products[i].num);
    }
}

// Function to calculate and display the change
void change(int notes){
    int denominations[] = {1000, 500, 200, 100, 50, 20, 10, 5, 1};
    int counts[sizeof(denominations)/sizeof(denominations[0])] = {0};
    int remaining = notes;

    for (int i = 0; i < sizeof(denominations)/sizeof(denominations[0]); i++) {
        if (remaining >= denominations[i]) {
            counts[i] = remaining / denominations[i];
            remaining %= denominations[i];
        }
    }

    for (int i = 0; i < sizeof(denominations)/sizeof(denominations[0]); i++) {
        if (counts[i] > 0) {
            printf("%d note(s) of Tk. %d\n", counts[i], denominations[i]);
        }
    }
}


// Function to update the sales
void updateSales(int bill){
    int sales = 0;
    FILE *ptr = fopen("sales.txt", "r");
        if (ptr == NULL){
            FILE *ptr = fopen("sales.txt", "w");
            sales = 0;
            fprintf(ptr, "%d", sales);
            fclose(ptr);
        }
        fscanf(ptr, "%d", &sales);
    fclose(ptr);

    sales += bill;

    ptr = fopen("sales.txt", "w");
        fprintf(ptr, "%d", sales);
    fclose(ptr);
}

// Function to count the number of lines in the inventory file
int countLines(){
    char ch;
    int lines = 0;
    FILE *ptr = fopen("inventory.txt", "r");
    while((ch=getc(ptr))!=EOF){
    if(ch=='\n')
    lines++;
    }
    fclose(ptr);
    return lines;
}
