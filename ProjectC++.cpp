#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

// Item class represents a product in the inventory
class Item
{
public:
    string name;
    int quantity;
    double price;

    // Constructor
    Item(string n, int q, double p)
    {
        name = n;
        quantity = q;
        price = p;
    }
};

// Global inventory list using vector
vector<Item> inventory;

// Function prototypes
void menu();
void addItem();
void displayInventory();
void updateQuantity();
void searchItem();
void deleteItem();
void saveToFile();
void loadFromFile();

// Menu function
void menu()
{
    cout << "========================";
    cout << "\nInventory System\n";
    cout << "========================\n";

    cout << "1. Add Item\n";
    cout << "2. Display Inventory\n";
    cout << "3. Update Quantity\n";
    cout << "4. Search Item\n";
    cout << "5. Delete Item\n";
    cout << "6. Save Inventory\n";
    cout << "7. Exit\n";
}

// Main program
int main()
{
    int choice;

    // Load existing inventory when program starts
    loadFromFile();

    do
    {
        menu();

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1)
        {
            addItem();
        }
        else if (choice == 2)
        {
            displayInventory();
        }
        else if (choice == 3)
        {
            updateQuantity();
        }
        else if (choice == 4)
        {
            searchItem();
        }
        else if (choice == 5)
        {
            deleteItem();
        }
        else if (choice == 6)
        {
            saveToFile();
        }
        else if (choice == 7)
        {
            cout << "\n";
            saveToFile();

            cout << "Exiting program in ";

            for (int i = 6; i >= 0; i--)
            {
                cout << "\rExiting program in " << i << " ";
                cout.flush();
                this_thread::sleep_for(chrono::seconds(1));
            }

            cout << "\n";
            cout << "========================\n";
            cout << "Thank you, Goodbye!\n";
            cout << "========================\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}

// Function to add a new item
void addItem()
{
    string name;
    int quantity;
    double price;

    cout << "Enter item name: ";
    cin >> name;

    cout << "Enter quantity: ";
    cin >> quantity;

    if (cin.fail() || quantity < 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid quantity. Must be a non-negative number.\n";
        return;
    }

    cout << "Enter price: ";
    cin >> price;

    if (cin.fail() || price < 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid price. Must be a non-negative number.\n";
        return;
    }

    // Add item to vector
    inventory.push_back(Item(name, quantity, price));

    cout << "Item added successfully.\n";
}

// Function to display all items
void displayInventory()
{
    if (inventory.size() == 0)
    {
        cout << "\nInventory List\n";
        cout << "------------------------\n";
        cout << "No Items to display.\n";
        cout << "------------------------\n";
        cout << "\n";

        return;
    }

    cout << "\nInventory List\n";
    cout << "------------------------\n";

    for (int i = 0; i < inventory.size(); i++)
    {
        cout << "Item: " << inventory[i].name << endl;
        cout << "Quantity: " << inventory[i].quantity << endl;
        cout << "Price: $" << inventory[i].price << endl;
        cout << "------------------------\n";
        cout << "";
    }
}

// Function to update item quantity
void updateQuantity()
{
    string name;
    cout << "Enter item name to update: ";
    cin >> name;

    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i].name == name)
        {
            int newQuantity;

            cout << "Enter new quantity: ";
            cin >> newQuantity;

            if (cin.fail() || newQuantity < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid quantity.\n";
                return;
            }

            inventory[i].quantity = newQuantity;

            cout << "Quantity updated.\n";
            return;
        }
    }

    cout << "Item not found.\n";
}

// Function to delete an item
void deleteItem()
{
    string name;
    cout << "Enter item name to delete: ";
    cin >> name;

    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i].name == name)
        {
            inventory.erase(inventory.begin() + i);
            cout << "Item deleted successfully.\n";
            return;
        }
    }

    cout << "Item not found.\n";
}

// Function to search item by name
void searchItem()
{
    string name;
    cout << "Enter item name to search: ";
    cin >> name;

    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i].name == name)
        {
            cout << "Item found:\n";
            cout << "Name: " << inventory[i].name << endl;
            cout << "Quantity: " << inventory[i].quantity << endl;
            cout << "Price: $" << inventory[i].price << endl;
            return;
        }
    }

    cout << "Item not found.\n";
}

// Function to save inventory to file
void saveToFile()
{
    ofstream file("inventory.txt");
    if (!file)
    {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < inventory.size(); i++)
    {
        file << inventory[i].name << " "
             << inventory[i].quantity << " "
             << inventory[i].price << endl;
    }

    file.close();

    cout << "Inventory saved to file.\n";
}

// Function to load inventory from file
void loadFromFile()
{
    ifstream file("inventory.txt");
    if (!file)
        return;

    string name;
    int quantity;
    double price;

    while (file >> name >> quantity >> price)
    {
        inventory.push_back(Item(name, quantity, price));
    }

    file.close();
}
