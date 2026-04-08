/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 23:08:47 by bryeap            #+#    #+#             */
/*   Updated: 2026/04/09 01:48:57 by bryeap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

// conxtructors
BitcoinExchange::BitcoinExchange()
{
	_readDB();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	if (this != &other)
		*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this != &other)
		_prices = other._prices;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

std::map<std::string, double> const &BitcoinExchange::getPrices() const
{
	return (_prices);
}

void BitcoinExchange::_readDB()
{
       std::ifstream file("data.csv"); // Open the file
        if (!file.is_open())
            throw CouldNotOpenFile();

        std::string line;
        std::getline(file, line);
        if (line != "date,exchange_rate")
            throw InvalidColumnFormat();

        while (std::getline(file, line))
		{
            std::string date, price;
            std::istringstream ss(line); // Create a string stream from the line
            std::getline(ss, date, ',');
            std::getline(ss, price, ',');

            double priceValue;
            std::istringstream priceStream(price);  // Create a string stream for the price
            if (!(priceStream >> priceValue))
				throw InvalidPriceFormat();
            _prices[date] = priceValue;
        }
        file.close();
}

bool BitcoinExchange::_validateDate(std::string const &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') // 10 is the len "YYYY-MM-DD"
		return (false);
	for (int i = 0; i < 10; i++) // check is is digit
	{
		if (i == 4 || i == 7)
			continue;
		if (isdigit(date[i]) == 0)
			return (false);
	}

	if (date[5] == '0' && date[6] == '0')  // reject "00" month
		return (false);
	if ((date[5] == '1' && date[6] > '2') || date[5] > '1') // month
 		return (false);

	if (date[8] == '0' && date[9] == '0')
		return (false);
	if ((date[8] == '3' && date[9] > '1') || date[8] > '3')
		return (false);
	
	return (true);
}

double BitcoinExchange::_validatePrice(std::string const &str)
{
	double priceValue;
	std::istringstream priceStream(str);

	if (!(priceStream >> priceValue))
	{
		std::cout << "Error: bad price input => " << priceValue << std::endl;
		return (-1);
	}

	if (priceValue < 0)
	{
		std::cout << "Error: not a positive number. " << std::endl;
		return (-1);
	}
	else if (priceValue > 1000)
	{
		std::cout << "Error: Too large a number. "  << std::endl;
		return (-1);
	}
	
	return (priceValue);
}

void BitcoinExchange::_multiplyWithPrice(std::string const &date, double amount)
{
	std::map<std::string, double>::iterator it = _prices.find(date);
	if (it != _prices.end()) // if found exact date
		std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
	else // if not found, find the closest date before the given date
	{
		std::map<std::string, double>::iterator it2 = _prices.lower_bound(date);  // first element that is bigger or equal to the given date
		if (it2 == _prices.begin()) // if the given date is before the earliest date , use the earliest date's price
			std::cout << date << " => " << amount << " = " << amount * it2->second << std::endl;
		else
		{
			it2--;
			std::cout << date << " => " << amount << " = " << amount * it2->second << std::endl;
		}
	}
}

void BitcoinExchange::execute(char const *fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		throw CouldNotOpenFile();

	std::string line;

	std::getline(file, line);
	if (line != "date | value")
		throw InvalidColumnFormat();

	while (std::getline(file, line))
	{
		std::string date;
		std::string amountStr;
		double amountValue;
		std::istringstream ss(line);
		std::getline(ss, date, '|');
		std::getline(ss, amountStr, '|');

		if (!date.empty() && date.back() == ' ')
			date = date.erase(date.length() -1); // remove trailing space
		if (_validateDate(date) == false)
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}

		if(!amountStr.empty())
			amountStr = amountStr.erase(0, 1); // remove leading space
		amountValue = _validatePrice(amountStr);
		if (amountValue != -1)
			_multiplyWithPrice(date, amountValue);
	}
	file.close();
}