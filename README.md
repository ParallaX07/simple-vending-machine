# Virtual Vending Machine

This C program simulates a virtual vending machine where users can buy products and receive change in notes. The vending machine's inventory is loaded from a file, and the sales data is updated after each transaction.

## Features

- Read and write inventory from/to a file
- Display available products
- Allow the user to select and buy products
- Calculate and return change in notes
- Update sales data in a file
- Clear the terminal for better user experience

## Usage

1. Ensure you have a C compiler installed (e.g., GCC or Visual Studio).
2. Compile the program using the C compiler.
3. Run the compiled program.
4. Follow the on-screen prompts to select products and enter payment information.
5. The program will calculate and return the change in notes, update the inventory, and update the sales data.

## Files

- `main.c`: The main source code of the virtual vending machine program.
- `inventory.txt`: The file containing the vending machine's inventory, with each product's name, price, weight, and quantity.
- `sales.txt`: The file containing the total sales data, which is updated after each transaction.

## Sample Inventory File

The inventory file should have the following format:

```
ProductName
Price
Weight
Quantity
```

Example:

```
Coke
50
300
10
Pepsi
45
330
8
Water
20
500
15
```
