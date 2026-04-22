/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:06:19 by bryeap            #+#    #+#             */
/*   Updated: 2026/04/17 19:13:50 by bryeap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <climits>
#include <iomanip>

class PmergeMe
{

private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    bool isValidNumber(const char *str);
    std::vector<int> getJacob(size_t size);         // Get the Jacob sequence for the given size
    std::vector<int> getInsertPos(size_t size);     // Get the insertion positions for the given size

    void sortVector();
    void sortDeque();

    template<typename T>
    void printSeq(const T &container, const std::string &label)
    {
        std::cout << label << ": ";
        for (size_t i = 0; i < container.size(); i++)
        {
            if (i > 0)
                std::cout << " ";
            std::cout << container[i];
        }
        std::cout << std::endl;
    }

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    bool parseArgs(int argc, char **argv);
    void sort();
};