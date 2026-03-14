
#include <iostream>
#include <string>
#include <iomanip>

namespace using std;

class Product {
public:
    string name;

    Product()
        : name("Unnamed"),
          description("No description"),
          price(0.0),
          shelfLife(0),
          place("Unknown")
    {
        cout << "[Constructor] Default constructor called for Product: " << name << endl;
    }

    Product(const Product& other)
        : name(other.name),
          description(other.description),
          price(other.price),
          shelfLife(other.shelfLife),
          place(other.place)
    {
        cout << "[Constructor] Copy constructor called for Product: " << name << endl;
    }

    Product(const string& name_,
            const string& description_,
            double price_,           
            int shelfLifeDays_,      
            const string& place_)
        : name(name_.empty() ? "Unnamed" : name_),
          description(description_),
          price(0.0),
          shelfLife(0),
          place(place_.empty() ? "Unknown" : place_)
    {
        
        if (!setPrice(price_)) {
            cout << "[Warning] Invalid price provided; set to 0.0\n";
        }
        if (!setShelfLife(shelfLifeDays_)) {
            cout << "[Warning] Invalid shelf life provided; set to 0 days\n";
        }
        cout << "[Constructor] Full constructor called for Product: " << name << endl;
    }

    ~Product() 
        cout << "[Destructor] Destructor called for Product: " << getName() << endl;

    string getName() const 
        return name.empty() ? string("Unnamed") : name;

    string getDescription() const 
        return description.empty() ? string("No description") : description;

    double getPrice() const 
        return price;

    int getShelfLife() const 
        return shelfLife;

    string getPlace() const 
        return place.empty() ? string("Unknown") : place;

    void setDescription(const string& desc) 
        description = desc;

    bool setPrice(double newPrice) {
        if (newPrice < 0.0) 
            return false;
        price = newPrice;
        return true;
    }

    bool setShelfLife(int days) {
        if (days < 0) return false;
        shelfLife = days;
        return true;
    }

    void setPlace(const string& p) 
        if (!p.empty()) place = p;

    void printAllInfo() const {
        cout << "Product information:\n";
        cout << "  Name        : " << getName() << '\n';
        cout << "  Description : " << getDescription() << '\n';
        cout << "  Price       : " << fixed << setprecision(2) << getPrice() << " (currency)\n";
        cout << "  Shelf life  : " << getShelfLife() << " days\n";
        cout << "  Place       : " << getPlace() << '\n';
    }

    void printWhereToGet() const 
        cout << "Get the product \"" << getName() << "\" at: " << getPlace() << '\n';

    bool decreaseShelfLife(int days) {
        if (days < 0) return false;
        if (days >= shelfLife) 
            shelfLife = 0;
        else 
            shelfLife -= days;
        return true;
    }

private:
    double price;    
    int shelfLife;   
    string place; 

protected:
    string description; 
};

// Example
int main() {
    Product p1;
    p1.printAllInfo();
    cout << '\n';

    Product p2("Мёд Лесной", "Натуральный мёд, 500г", 399.99, 365, "Магазин \"У Пчеловода\"");
    p2.printAllInfo();
    cout << '\n';

    bool ok = p2.setPrice(-50.0);
    cout << (ok ? "успех" : "неудача") << '\n';
    p2.setPrice(359.90);
    cout << "Новая цена: " << p2.getPrice() << '\n';

    p2.decreaseShelfLife(30);
    cout <<  p2.getShelfLife() << " дней\n";

    p2.printWhereToGet();
    cout << '\n';

    Product p3 = p2;
    p3.printAllInfo();

    return 0;
}
