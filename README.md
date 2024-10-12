# OOP Parfumery - Final Version

## Overview

This project is a Parfumery Management System created as part of the Object-Oriented Programming (OOP) class. The system allows users to manage `Parfums`, `Employees`, `Sales`, and `Inventory` within a parfumery store, incorporating several OOP concepts such as inheritance, polymorphism, encapsulation, templates, and the Singleton design pattern.

## Features

### 1. **Parfums Management**
   - The system can store and manage multiple perfume products.
   - Each perfume (`Parfum`) can have multiple attributes like name, brand, price, rating, and a list of ingredients.
   - It supports functionality to update ingredients, check the similarity between perfumes, and display detailed information about each perfume.

### 2. **Employee Management**
   - Employees are represented by the `Angajat` class.
   - Each employee can have details like name, position, activity status, monthly salary, and a list of recommended perfumes.
   - It includes functionality to estimate future salary growth and manage free days for employees.

### 3. **Sales Management**
   - Sales can be processed either as:
     - `VanzareOnline`: Online sales with home delivery.
     - `VanzareInMagazin`: In-store sales.
     - `VanzareOnlineCuRidicare`: Online sales with in-store pickup.
   - Sales inherit common properties from a base class (`Vanzare`) and are specialized with additional features (such as loyalty programs for in-store sales).
   - The system allows users to check which products are included in a sale and handles discount calculations.

### 4. **Inventory Management**
   - The `InventarMagazin` class manages the stock of perfumes in the store.
   - It provides functionality to check stock levels for different products, handle promotions, and calculate the total profit for the store.

### 5. **Singleton Design Pattern**
   - The entire system is controlled by a `Singleton` class to ensure that only one instance of the parfumery management system exists.
   - The `Singleton` class provides CRUD operations for `Parfum`, `Angajat`, `Vanzare`, and `InventarMagazin`.

## Class Breakdown

### 1. **Class: Produs**
   - Abstract base class for representing a product with functions to get and set product details.

### 2. **Class: Parfum**
   - Inherits from `Produs`.
   - Represents a perfume product with attributes such as name, brand, rating, price, and a list of ingredients.
   - Supports similarity checking and ingredient combination between perfumes.

### 3. **Template Class: ParfumerieIngredient**
   - A template class for handling ingredients in a perfume.
   - It allows for storing the amount and chemical compounds of the ingredient.
   - Supports combining ingredients and checking similarity between them.

### 4. **Class: Angajat**
   - Represents an employee with attributes like name, position, activity status, and monthly salary.
   - Includes a list of recommended perfumes for customers and free days for the employee.

### 5. **Class: Vanzare (Base Class)**
   - Represents a sale with details such as customer name, employee ID, total amount, and purchased products.

### 6. **Derived Classes: VanzareOnline, VanzareInMagazin, VanzareOnlineCuRidicare**
   - Specialized classes inheriting from `Vanzare` and adding additional functionality specific to online or in-store sales.
   - Handle different payment methods, delivery times, loyalty programs, and discounts.

### 7. **Class: InventarMagazin**
   - Manages the inventory of perfumes in the store.
   - Tracks the number of perfumes in stock and calculates profits during promotional periods.

### 8. **Class: Singleton**
   - Manages the whole system, ensuring only one instance of the management system exists.
   - Provides CRUD operations and allows for interaction between perfumes, employees, sales, and inventory.

## Key OOP Concepts Used

1. **Encapsulation**: All attributes are private or protected, and access is provided through getters and setters.
   
2. **Inheritance**: 
   - `Parfum` inherits from `Produs`.
   - `VanzareOnline`, `VanzareInMagazin`, and `VanzareOnlineCuRidicare` inherit from `Vanzare`.
   
3. **Polymorphism**: 
   - Virtual functions are used to provide different implementations for online and in-store sales.
   
4. **Templates**: 
   - `ParfumerieIngredient` is a template class that works with different data types for ingredients.
   
5. **Singleton Pattern**: Ensures that there is only one instance of the parfumery management system throughout the program.

## How to Run

1. Compile the project using a C++ compiler:
   ```sh
   g++ -o parfumery parfumery.cpp
   ```

2. Run the executable:
   ```sh
   ./parfumery
   ```

3. Follow the on-screen menu to interact with the parfumery management system.

## Conclusion

This project demonstrates the practical application of OOP principles in managing a perfume store. By leveraging inheritance, templates, polymorphism, and design patterns, the system efficiently handles complex operations and interactions between different components.
