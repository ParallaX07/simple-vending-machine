#include <stdio.h>
#include <string.h>
#include <math.h>

struct vendingMachine{
    char name[20];
    int price;
    float weight;
    int num;
};
//Functions used
void readInventory(int n, struct vendingMachine products[]);
void writeInventory(int n, struct vendingMachine products[]);
void displayProducts(int n, struct vendingMachine products[]);
void change(int notes);
void updateSales(int bill);
int countLines();

int main(){
    int n;
    char ans;
    n = countLines()/4;
    struct vendingMachine products[n];
    readInventory(n, products);
    printf("\n\tWelcome to the virtual Vending Machine!\n");
    displayProducts(n, products);
    int productNum, bill = 0, quantity = 1;
    while (1){
        printf("\nWhich product do you want to buy?: ");
        scanf(" %d", &productNum);
        if (products[productNum - 1].num == 0)
            printf("\nInvalid product number, choose another product.\n");
        else if ((productNum - 1) >= n || productNum <= 0){
            printf("\nProduct not in inventory, choose another product.\n");
        }
        else{
            printf("\nHow many do you want to buy?: ");
            scanf(" %d", &quantity);
            if (quantity > products[productNum - 1].num)
                printf("\nRequested amount not available, please change quantity or choose another product.\n");
            
            else{
                products[productNum - 1].num -= quantity;
                bill += products[productNum - 1].price * quantity;
            }
        }
         // Add the line to clear the terminal after each loop
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        displayProducts(n, products);
        printf("\nDo you want to buy anything else? (y/n): ");
        
        scanf(" %c", &ans);
        if(ans == 'n')
            break;

        // Add the line to clear the terminal after each loop
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
        if(cash < bill)
            printf("\nInsufficient amount entered. Please enter an amount greater or equal to your bill of Tk. %d!\n", bill);
        else {
            printf("\nTk. %d change returned with: \n", cash - bill);
            change(cash - bill);
            break;
        }
    }
    writeInventory(n, products); 
    updateSales(bill);

    return 0;
}


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


void displayProducts(int n, struct vendingMachine products[]){
    printf("\nName\t\tPrice (BDT)\tWeight (g)\tProducts available\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++){
        printf("[%d] %s\t\t%d\t%.2f\t\t%d\n", i+1, products[i].name, products[i].price, products[i].weight, products[i].num);
    }
}

void change(int notes){
    int rem = notes;
    if (rem >= 1000)
        printf("%d note(s) of Tk. 1,000\n", notes/1000);
    rem = (rem%1000);
    if (rem >= 500)
        printf("%d note(s) of Tk. 500\n", rem/500);
    rem = (rem%500);
    if (rem >= 200)
        printf("%d note(s) of Tk. 200\n", rem/200);                                                                                                                        
    rem = (rem%200);
    if (rem >= 100)
        printf("%d note(s) of Tk. 100\n", rem/100);
    rem = (rem%100);
    if (rem >= 50)
        printf("%d note(s) of Tk. 50\n", rem/50);
    rem = (rem%50);
    if (rem >= 20)
        printf("%d note(s) of Tk. 20\n", rem/20);
    rem = (rem%20);
    if (rem >= 10)
        printf("%d note(s) of Tk. 10\n", rem/10);
    rem = (rem%10);
    if (rem >= 5)
        printf("%d note(s) of Tk. 5\n", rem/5);
    rem = (rem%5);
    if (rem >= 1)
        printf("%d note(s) of Tk. 1\n", rem);
}

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




