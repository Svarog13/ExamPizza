#include "pizza.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm> 
#include <conio.h> 

Pizza::Pizza(const std::string& name, double basePizzaPrice) : pizzaName(name), basePizzaPrice(basePizzaPrice) {}

char getCharacter()
{
    char input;
    std::cin >> input;
    return input;
}
void Pizza::addIngredient(const Ingredient& ingredient)
{
    ingredients.push_back(ingredient);
}

double Pizza::calculateCost() const
{
    double totalCost = basePizzaPrice;
    for (const Ingredient& ingredient : ingredients)
    {
        totalCost += ingredient.getWeight() * ingredient.getPrice();
    }

    return totalCost;
}

void Pizza::displayPizzaInfo() const
{
    std::cout << "Pizza Name: " << pizzaName << std::endl;
    std::cout << "Base Price: " << basePizzaPrice << std::endl;
    std::cout << "Ingredients: " << std::endl;
    for (const Ingredient& ingredient : ingredients)
    {
        std::cout << ingredient.getName() << std::endl;
    }
}

void Menu::addPizza(const Pizza& pizza)
{
    pizzas.push_back(pizza);
}

void Menu::createPizza()
{
    std::string pizzaName;
    double pizzaPrice;
    int numIngredients;

    std::cin.ignore();
    std::cout << "Enter pizza name: ";
    std::getline(std::cin, pizzaName);
    std::cout << "Enter pizza price: ";
    std::cin >> pizzaPrice;

    std::cout << "Enter the number of ingredients: ";
    std::cin >> numIngredients;

    Pizza newPizza(pizzaName, pizzaPrice);

    for (int i = 0; i < numIngredients; ++i)
    {
        std::string ingredientName;
        float ingredientWeight;
        float ingredientPrice;

        std::cin.ignore();
        std::cout << "Enter ingredient name for ingredient " << (i + 1) << ": ";
        std::getline(std::cin, ingredientName);
        std::cout << "Enter ingredient weight (in grams) for ingredient " << (i + 1) << ": ";
        std::cin >> ingredientWeight;
        std::cout << "Enter ingredient price for ingredient " << (i + 1) << ": ";
        std::cin >> ingredientPrice;

        Ingredient newIngredient(ingredientName, ingredientWeight, ingredientPrice);

        newPizza.addIngredient(newIngredient);
    }
    addPizza(newPizza);
    std::cout << "Pizza created and added to the menu successfully!" << std::endl;
}

void Menu::removePizza(const std::string& pizzaName)
{
    pizzas.erase(
        std::remove_if(pizzas.begin(), pizzas.end(),
            [&pizzaName](const Pizza& pizza) { return pizza.getName() == pizzaName; }),
        pizzas.end());
}

void Menu::addIngredient(const Ingredient& ingredient)
{
    ingredients.push_back(ingredient);
}

bool Menu::ingredientExistsInMenu(const Ingredient& ingredientToCheck) const
{
    return std::any_of(ingredients.begin(), ingredients.end(),
        [&ingredientToCheck](const Ingredient& ingredient) { return ingredient.getName() == ingredientToCheck.getName(); });
}

void Menu::addIngredientToMenu(Ingredient& ingredient)
{
    std::string ingredientName;
    float ingredientWeight;
    float ingredientPrice;

    std::cin.ignore();
    std::cout << "Enter ingredient name: ";
    std::getline(std::cin, ingredientName);

    std::cout << "Enter ingredient weight (in grams): ";
    std::cin >> ingredientWeight;

    std::cout << "Enter ingredient price: ";
    std::cin >> ingredientPrice;

    Ingredient newIngredient(ingredientName, ingredientWeight, ingredientPrice);

    if (!ingredientExistsInMenu(newIngredient))
    {
        addIngredient(newIngredient);
        std::cout << "Ingredient added to the menu successfully!" << std::endl;
    }
    else
    {
        std::cout << "Ingredient already exists in the menu." << std::endl;
    }
}

void Menu::removeIngredient(const std::string& ingredientName)
{
    ingredients.erase(
        std::remove_if(ingredients.begin(), ingredients.end(),
            [&ingredientName](const Ingredient& ingredient) { return ingredient.getName() == ingredientName; }),
        ingredients.end());
}

void Menu::editPizza(const std::string& pizzaName, const Pizza& newPizza)
{
    auto pizzaToEdit = std::find_if(pizzas.begin(), pizzas.end(),
        [&pizzaName](const Pizza& pizza) { return pizza.getName() == pizzaName; });

    if (pizzaToEdit != pizzas.end())
    {
        *pizzaToEdit = newPizza;
    }
    else
    {
        throw std::invalid_argument("Pizza not found in the menu.");
    }
}

void Menu::editIngredient(const std::string& ingredientName, const Ingredient& newIngredient)
{
    auto ingredientToEdit = std::find_if(ingredients.begin(), ingredients.end(),
        [&ingredientName](const Ingredient& ingredient) { return ingredient.getName() == ingredientName; });

    if (ingredientToEdit != ingredients.end())
    {
        *ingredientToEdit = newIngredient;
    }
    else
    {
        throw std::invalid_argument("Ingredient not found in the menu.");
    }
}

void Menu::saveMenuToFile(const std::string& fileName) const
{
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("Error, file not open! " + fileName + " for write.");
    }

    file << "Ingredients: " << std::endl;
    for (const Ingredient& ingredient : ingredients)
    {
        file << ingredient.getName() << " " << ingredient.getWeight() << " " << ingredient.getPrice() << std::endl;
    }

    file << "Pizzas: " << std::endl;
    for (const Pizza& pizza : pizzas)
    {
        file << pizza.getName() << " " << pizza.calculateCost() << std::endl;
        file << "Ingredients: " << std::endl;
        for (const Ingredient& ingredient : pizza.getIngredients())
        {
            file << ingredient.getName() << " " << ingredient.getWeight() << " " << ingredient.getPrice() << std::endl;
        }
        file << "-----------------------" << std::endl;
    }

    file.close();
    std::cout << "Menu saved successfully to file. " << fileName << std::endl;
}

void Menu::loadMenuFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("Error, file not open! " + fileName + " for reading.");
    }

    pizzas.clear();
    ingredients.clear();

    std::string line;
    std::string category = "";

    while (std::getline(file, line))
    {
        if (line == "Ingredients:")
        {
            category = "Ingredients";
        }
        else if (line == "Pizzas:")
        {
            category = "Pizzas";
        }
        else if (!line.empty())
        {
            if (category == "Ingredients")
            {
                std::istringstream iss(line);
                std::string name;
                float weight, price;
                if (iss >> name >> weight >> price)
                {
                    Ingredient ingredient(name, weight, price);
                    ingredients.push_back(ingredient);
                }
                else
                {
                    throw std::invalid_argument("Error reading ingredient from file.");
                }
            }
            else if (category == "Pizzas")
            {
                std::string pizzaName = line;

                double pizzaCost;
                if (file >> pizzaCost)
                {
                    Pizza pizza(pizzaName, pizzaCost);

                    while (std::getline(file, line) && !line.empty() && line != "-----------------------")
                    {
                        std::istringstream iss(line);
                        std::string ingredientName;
                        float ingredientWeight, ingredientPrice;
                        if (iss >> ingredientName >> ingredientWeight >> ingredientPrice)
                        {
                            Ingredient ingredient(ingredientName, ingredientWeight, ingredientPrice);
                            pizza.addIngredient(ingredient);
                        }
                        else
                        {
                            throw std::invalid_argument("Error reading ingredient from file.");
                        }
                    }

                    pizzas.push_back(pizza);
                }
                else
                {
                    throw std::invalid_argument("Error reading pizza cost from file.");
                }
            }
        }
    }

    file.close();
    std::cout << "Menu loaded successfully from file: " << fileName << std::endl;
}

void Menu::viewPizzas() const
{
    if (pizzas.empty())
    {
        std::cout << "No pizzas in the menu. " << std::endl;
    }
    else
    {
        std::cout << "List of Pizzas: " << std::endl;
        for (const Pizza& pizza : pizzas)
        {
            pizza.displayPizzaInfo();
            std::cout << "----------------------" << std::endl;
        }
    }
}

void Menu::viewIngredients() const
{
    if (ingredients.empty())
    {
        std::cout << "No ingredients in the menu." << std::endl;
    }
    else
    {
        std::cout << "List of Ingredients: " << std::endl;
        for (const Ingredient& ingredient : ingredients)
        {
            std::cout << "Name: " << ingredient.getName() << std::endl;
            std::cout << "Weight: " << ingredient.getWeight() << std::endl;
            std::cout << "Price: " << ingredient.getPrice() << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }
    }
}

Order::Order(const Pizza& pizza, int quantity) : pizza(pizza), quantity(quantity) {}

void Menu::createOrder()
{
    std::string pizzaName;
    int quantity;

    std::cin.ignore();

    std::cout << "Enter pizza name for the order: ";
    std::getline(std::cin, pizzaName);

    std::cout << "Enter quantity for the order: ";
    std::cin >> quantity;

    Pizza orderedPizza;
    for (const Pizza& pizza : pizzas)
    {
        if (pizza.getName() == pizzaName)
        {
            orderedPizza = pizza;
            break;
        }
    }
    if (orderedPizza.getName() == "No Match")
    {
        std::cout << "Pizza with the specified name was not found in the menu." << std::endl;
    }
    else
    {
        Order order(orderedPizza, quantity);
        orders.push_back(order);
        std::cout << "Order created successfully!" << std::endl;
    }
}

void Menu::showMainMenu()
{
    char choice;
    while (true)
    {
        system("cls");
        std::cout << "Main Menu" << std::endl;
        std::cout << "1. View Pizzas" << std::endl;
        std::cout << "2. View Ingredients" << std::endl;
        std::cout << "3. Create Pizza" << std::endl;
        std::cout << "4. Add Ingredient to Menu" << std::endl;
        std::cout << "5. Create Order" << std::endl;
        std::cout << "6. View Orders" << std::endl;
        std::cout << "7. Save Menu to File" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        choice = _getch();
        switch (choice)
        {
        case '1':
            viewPizzas();
            break;
        case '2':
            viewIngredients();
            break;
        case '3':
            createPizza();
            break;
        case '4':
        {
            Ingredient newIngredient; 
            addIngredientToMenu(newIngredient); 
            break;
        }
        case '5':
            createOrder();
            break;
        case '6':
            viewOrders();
            break;
        case '7':
            saveMenuToFile("menu.txt");
            break;
        case '8':
            return; 
        default:
            std::cout << "Invalid choice. Press any key to continue...";
            _getch();
        }
    }
}

int main()
{
    Menu menu;

    try
    {
        menu.loadMenuFromFile("menu.txt");
        menu.showMainMenu();
        menu.saveMenuToFile("menu.txt");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
