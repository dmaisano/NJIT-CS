/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 3
Due by 7/18/17
*/

/*
Steps
1. Input:
    a. amountAdult // amount of adult tickets sold
    b. amountChild // amount of child tickets sold

2. Processing:
    a. totalGross = (amountAdult * priceAdult) + (amountChild * priceChild); // total sales generated by the thearer for that specific movie
    b. totalNet = totalGross * percentProfit; // total that the theater keeps as profit

3. Output:
    a. movieName
    b. amountAdult
    c. amountChild
    d. totalGross
    e. totalNet
    f. Distributor profit // totalGross - totalNet
*/

#include <iostream>
#include <iomanip> // used for setprecision(2) to have a max of two decimal places
using namespace std;

int main()
{
	string movieName;
	double totalGross = 0, totalNet = 0, percentProfit = 0.2, amountAdult = 0, priceAdult = 6.00, amountChild = 0, priceChild = 3.00;

	cout << "Enter the name of the movie: ";
	cin >> movieName;

	cout << "Enter amount of adult seats sold: ";
	cin >> amountAdult;

	cout << "Enter amount of children seats sold: ";
	cin >> amountChild;

	totalGross = (amountAdult * priceAdult) + (amountChild * priceChild); // total sales generated by the thearer for that specific movie

	totalNet = totalGross * percentProfit; // total that the theater keeps as profit

	cout << "\n\nMovie Name: \t\t\t" << movieName;
	cout << "\nAdult Tickets Sold: \t\t" << fixed << setprecision(2) << amountAdult; // fixed is used to remove scientific notation from output format
	cout << "\nChild Tickets Sold: \t\t" << amountChild;
	cout << "\nGross Box Office Profit: \t$" << totalGross;
	cout << "\nNet Box Office Profit: \t\t$" << totalNet;
	cout << "\nAmount Paid to Distributor: \t$" << totalGross - totalNet; // Distributor profit = gross - net

	return 0;
}
