/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 23:09:34 by bryeap            #+#    #+#             */
/*   Updated: 2026/04/09 00:51:08 by bryeap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <exception>
#include <string>

class BitcoinExchange
{
private:
    std::map<std::string, double> _prices; // key: date, value: exchange rate
    void _readDB();
    bool _validateDate(std::string const &date);
    double _validatePrice(std::string const &price);
    void _multiplyWithPrice(std::string const &date, double price);

public:
    BitcoinExchange();
    BitcoinExchange(BitcoinExchange const &other);
    BitcoinExchange &operator=(BitcoinExchange const &other);
    ~BitcoinExchange();

    std::map<std::string, double> const &getPrices() const;
    void execute(char const *fileName);

    class CouldNotOpenFile : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return ("Could not open file");
        }
    };

    class InvalidColumnFormat : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return ("Invalid column format. Expected 'date,exchange_rate'");
        }
    };

    class InvalidDateFormat : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return ("Invalid date format. Expected 'YYYY-MM-DD'");
        }
    };

    class InvalidPriceFormat : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return ("Invalid price format. Expected a number between 0.0 and 1000.0");
        }
    };
};