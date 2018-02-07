/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:51:47 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/05 15:51:47 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_ABSTRACTVM_HPP
#define ABSTRACTVM_ABSTRACTVM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "IOperand.hpp"
#include "Operand.tpp"

class AbstractVM {

public:
	AbstractVM(); // Canonical
	AbstractVM(AbstractVM const &copy); // Canonical
	~AbstractVM() {} // Canonical

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

    void parseCommand(std::string prompt);

    void executeCommand(std::string cmd);
    void executeCommand(std::string cmd, std::string value);

	AbstractVM &operator=(AbstractVM const &copy); // Canonical

private:
    void push();
    void pop();
    void dump();
    void assert();
    void add();
    void sub();
    void mul();
    void div();
    void mod();
    void print();
    void exit();

	typedef const IOperand *(AbstractVM::*OperandFunc)(const std::string &) const;
    static bool debugFlag;
	std::vector<OperandFunc> createPointerTab;
	std::map<std::string, void (AbstractVM::*)()> commandMap;
	std::stack<IOperand> stack;

};


#endif //ABSTRACTVM_ABSTRACTVM_HPP