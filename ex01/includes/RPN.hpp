/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:33:03 by bryeap            #+#    #+#             */
/*   Updated: 2026/04/09 03:04:17 by bryeap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <exception>

class RPN
{
private:
    std::stack<double> _stack;
    void _executeStack(double (RPN::*f)(double, double));  // RPN::*f pointer to member func
    double _plus(double a, double b);
    double _minus(double a, double b);
    double _multiply(double a, double b);
    double _divide(double a, double b);

public:
    RPN();
    RPN(const std::string &inputStr);
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();

    double getResult() const;

    class invalidArgument : public std::runtime_error
    {
    public:
        explicit invalidArgument(const std::string &msg);
    };

    class emptyStack : public std::runtime_error
    {
    public:
        explicit emptyStack(const std::string &msg);
    };

    class divisionByZero : public std::runtime_error
    {
    public:
        explicit divisionByZero(const std::string &msg);
    };
};