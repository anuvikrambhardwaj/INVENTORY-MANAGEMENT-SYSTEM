// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Product {
protected:
    int id;
    string name;
    int quantity;
    double price;

public:
    Product() : id(0), name(""), quantity(0), price(0.0) {}
    Product(int id, string name, int quantity, double price)
        : id(id), name(name), quantity(quantity), price(price) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setPrice(double price) { this->price = price; }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << quantity
             << setw(10) << fixed << setprecision(2) << price << endl;
    }

    string toFileString() const {
        return to_string(id) + "," + name + "," + to_string(quantity) + "," + to_string(price);
    }

    static Product fromFileString(const string& line) {
        Product p;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        p.id = stoi(line.substr(0, pos1));
        p.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        p.quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        p.price = stod(line.substr(pos3 + 1));

        return p;
    }
};

class Inventory {
private:
    vector<Product> products;
    string filename = "inventory.txt";

public:
    Inventory() { loadFromFile(); }

    void addProduct() {
        int id, quantity;
        double price;
        string name;

        cout << "\nEnter Product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: ";
        cin >> price;

        products.emplace_back(id, name, quantity, price);
        saveToFile();

        cout << "\nProduct added successfully!\n";
    }

    void viewProducts() const {
        if (products.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }

        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price" << endl;
        cout << string(50, '-') << endl;

        for (const auto &p : products)
            p.display();
    }

    void searchProduct() const {
        int id;
        cout << "\nEnter Product ID to search: ";
        cin >> id;

        for (const auto &p : products) {
            if (p.getId() == id) {
                cout << "\nProduct found:\n";
                cout << left << setw(10) << "ID"
                     << setw(20) << "Name"
                     << setw(10) << "Quantity"
                     << setw(10) << "Price" << endl;
                cout << string(50, '-') << endl;
                p.display();
                return;
            }
        }
        cout << "\nProduct not found!\n";
    }

    void updateProduct() {
        int id;
        cout << "\nEnter Product ID to update: ";
        cin >> id;

        for (auto &p : products) {
            if (p.getId() == id) {
                int newQty;
                double newPrice;
                cout << "Enter new Quantity: ";
                cin >> newQty;
                cout << "Enter new Price: ";
                cin >> newPrice;
                p.setQuantity(newQty);
                p.setPrice(newPrice);
                saveToFile();
                cout << "\nProduct updated successfully!\n";
                return;
            }
        }
        cout << "\nProduct not found!\n";
    }

    void deleteProduct() {
        int id;
        cout << "\nEnter Product ID to delete: ";
        cin >> id;

        for (size_t i = 0; i < products.size(); ++i) {
            if (products[i].getId() == id) {
                products.erase(products.begin() + i);
                saveToFile();
                cout << "\nProduct deleted successfully!\n";
                return;
            }
        }
        cout << "\nProduct not found!\n";
    }

    void saveToFile() const {
        ofstream fout(filename, ios::trunc);
        for (const auto &p : products)
            fout << p.toFileString() << endl;
        fout.close();
    }

    void loadFromFile() {
        products.clear();
        ifstream fin(filename);
        if (!fin.is_open())
            return;

        string line;
        while (getline(fin, line)) {
            if (!line.empty())
                products.push_back(Product::fromFileString(line));
        }
        fin.close();
    }
};

class Menu {
private:
    Inventory inventory;

public:
    void displayMenu() {
        int choice;
        do {
            cout << "\n========= INVENTORY MANAGEMENT SYSTEM =========\n";
            cout << "1. Add Product\n";
            cout << "2. View All Products\n";
            cout << "3. Search Product\n";
            cout << "4. Update Product\n";
            cout << "5. Delete Product\n";
            cout << "0. Exit\n";
            cout << "==============================================\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: inventory.addProduct(); break;
                case 2: inventory.viewProducts(); break;
                case 3: inventory.searchProduct(); break;
                case 4: inventory.updateProduct(); break;
                case 5: inventory.deleteProduct(); break;
                case 0: cout << "\nExiting... Goodbye!\n"; break;
                default: cout << "\nInvalid choice! Try again.\n";
            }

        } while (choice != 0);
    }
}; // ✅ closes Menu class properly

int main() {
    Menu menu;
    menu.displayMenu();
    return 0;
} // ✅ closes main()

// g++ "C:\Users\Vikram\OOpsFile\vsCode\main.cpp" -o "C:\Users\Vikram\OOpsFile\vsCode\main.exe"

