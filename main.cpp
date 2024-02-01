#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
void login();
void registration();
void main_menu();
void saveDataToFile();
void admin_login_menu();
int main();
class Customer
{
private:
    char home_address[200];
    char phone_number[8];
    string email_address;

public:
    char full_name[30];
    void enter_details();
    void display_details();
};
void Customer::enter_details()
{
    int i = 0, temp = 0, check = 0;
    cout << "\nEnter Detail: \n";
    cout << "\nCustomer name: ";
    cin >> full_name;
    cout << "\nContact number: ";
    cin >> phone_number;
    cout << "\nCustomer address: ";
    cin >> home_address;
    cout << "\nEmail: ";
    cin >> email_address;
}

void Customer::display_details()
{
    cout << "\n\t\tName:              " << full_name;
    cout << "\n\t\tContact Number:    " << phone_number;
    cout << "\n\t\tEmail address:     " << email_address;
}

class Admin
{
private:
    string category;
    string productCode;
    string productName;
    int quantity;
    double price;

public:
    void enterProductData()
    {
        cout << "Enter product category of beauty, home, accessories: ";
        cin >> category;
        if (category != "beauty" && category != "home" && category != "accessories")
        {
            cout << "Error: Invalid category.\n";
            return;
        }

        cout << "Enter  code: ";
        cin >> productCode;
        cout << "Enter product name: ";
        cin >> productName;
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter price: ";
        cin >> price;
        saveDataToFile();
    }

    void saveDataToFile()
    {
        ofstream outFile(category + "_products.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << productCode << "   " << productName << "   " << quantity << "   " << price << endl;
            cout << "Product data saved successfully.\n";
        }
        else
        {
            cout << "Error opening file for writing.\n";
        }
    }

    void printLowQuantityItems()
    {
        cout << "Items with quantity less than 10:\n";

        checkAndPrintLowQuantity("beauty");
        checkAndPrintLowQuantity("home");
        checkAndPrintLowQuantity("accessories");
    }

private:
    void checkAndPrintLowQuantity(const string &cat)
    {
        ifstream inFile(cat + "_products.txt");

        if (inFile.is_open())
        {
            while (inFile >> productCode >> productName >> quantity >> price)
            {
                if (quantity < 10)
                {
                    cout << productCode << "   " << productName << "   " << quantity << "   " << price << endl;
                }
            }

            inFile.close();
        }
        else
        {
            cout << "Error  " << cat + "_products.txt" << endl;
        }
    }  
};

class Inventory
{
public:
    char product_code[6];
    string product_name;
    double item_price;
    int quantity;

public:
    char show_more();
    void order_item();
};
char Inventory ::show_more()
{
    char type;
    cout << "\n\t B>>> beauty";
    cout << "\n\t H>>> home";
    cout << "\n\t A>>> accessories";
    cout << "\n\n\tEnter type: ";
    cin >> type;
    return type;
}
class beauty : public virtual Inventory
{
public:
    void show();
};

class home : public virtual Inventory
{
public:
    void show();
};
class accessories : public virtual Inventory
{
public:
    void show();
};
class Inventorycart : public beauty, public home, public accessories
{
public:
    void show_cart();
    void select_item(const char filename[]);
};
void Inventory::order_item()
{
    Inventorycart cart;
    char type;

    type = show_more();
    if (type == 'B' || type == 'b')
    {
        beauty b;
        b.show();
        cart.select_item("beauty_products.txt");
    }
    else if (type == 'H' || type == 'h')
    {
        home h;
        h.show();
        cart.select_item("home_products.txt");
    }
    else if (type == 'A' || type == 'a')
    {
        accessories a;
        a.show();
        cart.select_item("accessories_products.txt");
    }
    else 
    cout << "Invalid choice .... Please enter again: ";
    
};



void beauty::show()
{

    ifstream infile("beauty_products.txt");
    cout << "\n************************************************************************************\n";
    cout << "\n                                  ";
    cout << "\nCode   Names\t\tQuantity\t\tPrice\n";
    cout << "\n************************************************************************************\n";
    while (infile >> product_code >> product_name >> quantity >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << quantity << "  " << item_price << endl;
    }
    cout << "\n************************************************************************************\n";
    infile.close();
}

void home::show()
{

    ifstream infile("home_products.txt");
    cout << "\n************************************************************************************\n";
    cout << "\n                                  ";
    cout << "\nCode   Names\t\tQuantity\t\t\tPrice\n\n";
    cout << "\n************************************************************************************\n";
    while (infile >> product_code >> product_name >> quantity >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << quantity << "  " << item_price << endl;
    }
    cout << "\n************************************************************************************\n";
    infile.close();
}

void accessories::show()
{

    ifstream infile("accessories_products.txt");
    cout << "\n************************************************************************************\n";
    cout << "\n                                  ";
    cout << "\nCode   Names\t\tQuantity\t\t\tPrice\n\n";
    cout << "\n************************************************************************************\n";
    while (infile >> product_code >> product_name >> quantity >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << quantity << "  " << item_price << endl;
    }
    cout << "\n************************************************************************************\n";
    infile.close();
}

void Inventorycart::select_item(const char filename[])
{
    char option[6],  answer;
    int temp = 0, quan = 0;
    ifstream infile;
    ofstream updated_file, cart_file;
    updated_file.open("temp.txt");
    cart_file.open("cart.txt", ios::out | ios::app);

    do
    {
        cout << "\nEnter code to select: ";
        cin >> option;
        infile.open(filename);

        while (infile >> product_code >> product_name >> quantity >> item_price)
        {
            if (strcmp(option, product_code) == 0)
            {
                temp = 0;
                break;
            }
            else
                temp = 1;
        }

        if (temp == 1)
        {
            cout << "\nInvalid code entered! Please enter correct code";
            infile.close();
        }

        infile.close();
    } while (temp == 1);

    infile.open(filename);

    cout << "\n\nEnter Quantity: ";
    cin >> quan;

    while (infile >> product_code >> product_name >> quantity >> item_price)
    {
        if (strcmp(option, product_code) == 0)
        {
            quantity = quantity - quan;

            cart_file << product_code << "   " << product_name << "   " << quan << "   " << item_price << endl;
            cout << endl
                 << product_code << "\t\t" << product_name << "\t\t" << quan << "\t" << item_price << "\t\t" << endl;
        }
        updated_file << product_code << "   " << product_name << "   " << quantity << "   " << item_price << endl;
    }
    infile.close();
    cart_file.close();
    updated_file.close();
    remove(filename);
    rename("temp.txt", filename);

    cout << "\nDo you want to buy anything else?(y/n)";
    cin >> answer;
    if (answer == 'y')
    {
        order_item();
    }
    else
    {
        show_cart();
    }
}
class Recordtransaction : public Customer
{
private:
    double total_amount = 0;
    int quantity = 0;
    double price = 0;

public:
    void set_amount(int qty, double p);
    Recordtransaction operator*(const Recordtransaction &temp);
    void makebill();
};

void Recordtransaction::set_amount(int qty, double p)
{
    quantity = qty;
    price = p;
    total_amount += qty * p;
}

Recordtransaction Recordtransaction::operator*(const Recordtransaction &temp)
{
    Recordtransaction result;
    result.total_amount = this->quantity * this->price;
    return result;
}

void Recordtransaction::makebill()
{
    char item_code[6];
    string item_name;
    double item_price;
    int item_qty;
    Recordtransaction Customer_transaction;
    Customer_transaction.enter_details();
    cout << "\n\t\t************************************************************************************\n";
    cout << "\t\t\t\t\t\tBILL";
    cout << "\n\t\t************************************************************************************\n";
    Customer_transaction.display_details();
    cout << "\n\t\t************************************************************************************\n";

    cout << "\t\tItem name\tPrice\t\tQuantity" << endl;

    ifstream c;
    c.open("cart.txt");

    double total_amount;

    while (c >> item_code >> item_name >> item_qty >> item_price)
    {
        cout << "\t\t" << item_name << "\t\t" << item_qty << "\t\t" << item_price << endl;
        set_amount(item_qty, item_price);
        total_amount += item_qty * item_price;
    }

    cout << "\n\t\tTotal balance due : " << total_amount;

    cout << "\n\t\t************************************************************************************\n";

    c.close();
    ofstream transactionRecord("TransactionRecord.txt", ios::out | ios::app);
    c.open("cart.txt");

    while (c >> item_code >> item_name >> item_price >> item_qty)
    {
        transactionRecord << item_code << "   " << item_name << "   " << item_price << "   " << item_qty << endl;
    }

    c.close();
    transactionRecord.close();
    remove("cart.txt");
}

void Inventorycart::show_cart()
{
   
    ifstream cart_file("cart.txt");
    cout << "\n\t\t\t\t\t\tYour Cart";
    cout << "\n\t\t************************************************************************************\n";
    cout << "\n\t\t\tCode   Names\t\tQuantity\tPrice\n";
    cout << "\n\t\t************************************************************************************\n";
    while (cart_file >> product_code >> product_name >> quantity >> item_price)
    {
        cout << "\t\t\t" << product_code << "   " << product_name << "\t\t\t" << quantity << "  " << item_price << "\t\t" << endl;
    }
    cout << "\n\t\t************************************************************************************\n";
    cart_file.close();
    // Display the bill
    Recordtransaction transaction_obj;
    transaction_obj.makebill();
    char q;
    cout << "Press 1 to go to main menu: " << endl;
    cout << "Press 2 to exit :" << endl;
    cin >> q;
    switch (q)
    {
    case '1':
    {
        main();
        break;
    }
    case '2':
    {
        exit(0);
    }
    default:
        cout << "Enter Correct option " << endl;
    }
}
/*
void main_menu()
{
    int choice;

    cout << "\t\t\t _________________________________________________________________\n";
        cout << "\t\t\t|                    WELCOME TO LOGIN PAGE                        |\n";
        cout << "\t\t\t|                                                                 |\n";
        cout << "\t\t\t|______________________      MENU        _________________________|\n\n\n";
        cout << "\t| Press 1 to login                  |" << endl;
        cout << "\t| Press 2 to registration           |" << endl;
        cout << "\t| Press 3 if you forget password    |" << endl;
        cout << "\t| Press 4 to exit                   |" << endl;
        cout << "\n\t\tPlease enter your choice:";

    switch (choice)
    {
    case 1:
        login();
        break;
    case 2:
        registration();
        break;
    case 3:
        forget();
        break;
    case 4:
        cout << "\t\t\t Thank you!\n\n";
        break;
    default:
        system("cls");
        cout << "Please select from the options given above\n";
        main_menu();
    }
}

void registration()
{
    string username, password;
    system("cls");
    cout << "\t\t\tEnter username:" << endl;
    cin >> username;
    cout << "\t\t\tEnter password:" << endl;
    cin >> password;

    ofstream out("data.txt", ios::app);
    out << username << " " << password << endl;
    system("cls");
    cout << "Registration is successful" << endl;
    main_menu();
}

void login()
{
    int count = 0;
    string username, password, stored_username, stored_password;
    system("cls");
    cout << "\t\tPlease enter username and password:" << endl;
    cout << "\t\t  USERNAME:  " << endl;
    cin >> username;
    cout << "\t\t   PASSWORD:  " << endl;
    cin >> password;

    ifstream in("data.txt");

    while (in >> stored_username >> stored_password)
    {
        if (stored_username == username && stored_password == password)
        {
            count = 1;
            system("cls");
            break;
        }
    }

    in.close();

    if (count == 1)
    {
        cout << username << "\n Your login is successful \n Thanks for logging in! \n"
             << endl;
        Inventory store;
        store.order_item();
    }
    else
    {
        cout << "Login error! \n Please check your username and password\n";
        main_menu();
    }
}

void forget()
{
    int option;
    cout << "\t\t Forgot your password? No worries" << endl;
    cout << " Press 1 to search your Id by name" << endl;
    cout << " Press 2 to go to the main menu" << endl;
    cout << "\t\t Enter your choice " << endl;
    cin >> option;

    switch (option)
    {
    case 1:
        search();
        break;
    case 2:
        main_menu();
        break;
    default:
        cout << "Invalid option. Please enter 1 or 2." << endl;
        forget();
    }
}

void search()
{
    int option;
    string search_name, stored_username, stored_password, name;

    cout << "Enter your name: ";
    cin >> search_name;

    ifstream in("data.txt");

    while (in >> stored_username >> stored_password)
    {
        if (stored_username == search_name)
        {
            name = stored_username;
            break;
        }
    }

    in.close();

    if (name == search_name)
    {
        cout << "Your Id is: " << name << "\n Enter 3 to go to main menu: ";
        cin >> option;
        if (option == 3)
        {
            main_menu();
        }
        else
        {
            cout << "Invalid option. Please enter 3." << endl;
            search();
        }
    }
    else
    {
        cout << "Name not found. Please try again." << endl;
        search();
    }
}
*/
bool administrator_login()
{
    string admin_email = "sarkar@gmail.com";
    string admin_password = "idk";

    string entered_email, entered_password;

    cout << "Enter Administration Email: ";
    cin >> entered_email;

    cout << "Enter Administration Password: ";
    cin >> entered_password;

    return (entered_email == admin_email && entered_password == admin_password);
}

void admin_login_menu()
{
    Admin a;
    char admin_choice;
    do
    {    cout << "\t\t|___________________________________________________________________|\n\n";
         cout << "\n\t\t| _________________________________________________________________|\n";
         cout << "\t\t|___________________________________________________________________|\n\n";
        cout << "\t\t|                     Administration Menu                            |\n";
        cout << "\t\t|___________________________________________________________________|\n\n";
        cout << "\t\t|___________________________________________________________________|\n\n";
        cout << "\t\t|___________________________________________________________________|\n\n";
        cout << "\t\t| Press 1  add products                                           |\n";
        cout << "\t\t| Press 2  threshold products                                    |\n";
        cout << "\n\t\tEnter given choice :";
        cin >> admin_choice;

        switch (admin_choice)
        {
        case '1':
            a.enterProductData();
            break;

        case '2':
            a.printLowQuantityItems();
            break;

        default:
            cout << "Incorrect code! please enter right code.\n";
        }

    } while (admin_choice > 2 || admin_choice < 0);
}
int main()
{
    char c;
    //  system("cls");
    cout << "\t\t\t _________________________________________________________________\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|                    GREETINGS ON THE INVENTORY STORE             |\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|                      Feel free to come & Enjoy                  |\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|______________________    MENU MENU         _____________________|\n\n\n";
    cout << "\t| Enter 1 for User(Individual)  |" << endl;
    cout << "\t| Enter 2 for administration    |" << endl;
    cin >> c;
    if (c == '1')
    {
    
       Inventory store;
        store.order_item();
    }
    else if (c == '2')
    {
        administrator_login();
        admin_login_menu();
    }
    else
    {
        cout << "Invalid input. Please enter 1 or 2.\n";
        main();
    }

    return 0;
}