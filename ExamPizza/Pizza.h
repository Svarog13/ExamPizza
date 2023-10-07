#ifndef PIZZA_H
#define PIZZA_H

#include <string>
#include <vector>

class Ingredient
{
private:
    std::string name;
    float weight;
    float price;

public:
    Ingredient() : name("no name"), weight(0.0), price(0.0) {}
    Ingredient(const std::string& name, float weight, float price) : name(name), weight(weight), price(price) {}

    std::string getName() const;
    float getWeight() const;
    float getPrice() const;

    void setName(const std::string& _name);
    void setWeight(float _weight);
    void setPrice(float _price);
};

class Pizza
{
private:
    std::string pizzaName;
    double basePizzaPrice;
    std::vector<Ingredient> ingredients;

public:
    Pizza(const std::string& name = "", double basePizzaPrice = 0.0);

    std::string getName() const;
    const std::vector<Ingredient>& getIngredients() const;

    void addIngredient(const Ingredient& ingredient);
    double calculateCost() const;
    void displayPizzaInfo() const;
};

class StandartPizza : public Pizza
{
public:
    StandartPizza(const std::string name = "", double basePrice = 0.0) :
        Pizza(name, basePrice) {}
};

class CustomPizza : public Pizza
{
public:
    CustomPizza(const std::string name = "", double basePrice = 0.0) :
        Pizza(name, basePrice) {}
};

class Order;  // Forward declaration

class Menu
{
private:
    std::vector<Pizza> pizzas;
    std::vector<Ingredient> ingredients;
    std::vector<Order> orders;
public:
    void addPizza(const Pizza& pizza);
    void createPizza();
    void addIngredientToMenu(Ingredient& ingredient);
    bool ingredientExistsInMenu(const Ingredient& ingredientToCheck) const;
    void removePizza(const std::string& pizzaName);
    void addIngredient(const Ingredient& ingredient);
    void removeIngredient(const std::string& ingredientName);
    void editPizza(const std::string& pizzaName, const Pizza& newPizza);
    void editIngredient(const std::string& ingredientName, const Ingredient& newIngredient);
    void createOrder();
    void saveMenuToFile(const std::string& fileName) const;
    void loadMenuFromFile(const std::string& fileName);
    void viewPizzas() const;
    void viewIngredients() const;
    void viewOrders();
    void showMainMenu();
    Pizza findPizzaByIngredients(const std::vector<Ingredient>& ingredients) const;
};

class Order
{
private:
    std::vector<Pizza> pizzasOrdered;

public:
    void addPizzaToOrder(const Pizza& pizza);
    void removePizzaFromOrder(const std::string& pizzaName);
    double calculateTotalCost() const;
    void displayOrderInfo() const;
};

class Payment
{
public:
    void printReceipt(const Order& order) const;
    void acceptPayment(const Order& order, double amountReceived) const;
};

class PizzasDatabase
{
public:
    void savePizzasToFile(const std::string& fileName, const std::vector<Pizza>& pizzas) const;
    std::vector<Pizza> loadPizzasFromFile(const std::string& fileName) const;
};

class IngredientDatabase
{
public:
    void saveIngredientsToFile(const std::string& fileName, const std::vector<Ingredient>& ingredients) const;
    std::vector<Ingredient> loadIngredientsFromFile(const std::string& fileName) const;
};

class Client
{
private:
    std::string name;
    std::string address;
    std::vector<Order> orderHistory;

public:
    Client(const std::string& _name = "", const std::string& _address = "");
    void placeOrder(const Order& order);
    const std::vector<Order>& getOrderHistory() const;
};

class Order {
public:
    Order(const Pizza& _pizza, int _quantity) : pizza(_pizza), quantity(_quantity) {}

    const Pizza& getPizza() const { return pizza; }
    int getQuantity() const { return quantity; }
    double getTotalCost() const { return pizza.calculateCost() * quantity; }
    void displayOrderInfo() const {
        std::cout << "Pizza: " << pizza.getName() << std::endl;
        std::cout << "Quantity: " << quantity << std::endl;
        std::cout << "Total Cost: " << getTotalCost() << std::endl;
    }

private:
    const Pizza& pizza;
    int quantity;
};

class FileManager
{
public:
    void saveToFile(const std::string& fileName, const std::string& data) const;
    std::string loadFromFile(const std::string& fileName) const;
};

#endif
