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
	static AbstractVM *getInstance();

	static std::string stringTrim(std::string &string);

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

    void parseCommand(std::string prompt);
    void executeCommand(std::string cmd);
    void executeCommand(std::string cmd, std::string value);


private:
	AbstractVM &operator=(AbstractVM const &copy); // Canonical
	AbstractVM(); // Canonical
	AbstractVM(AbstractVM const &copy); // Canonical
	~AbstractVM() {} // Canonical

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

	typedef const IOperand *(AbstractVM::*TypeOperandFunction)(const std::string &) const;
	typedef void (AbstractVM::*TypeCommandFunction)();

	static AbstractVM *singleton;
    static bool debugFlag;
	std::vector<TypeOperandFunction> createPointerTab;
	std::map<std::string, TypeCommandFunction> commandMap;
	std::stack<IOperand> stack;

};


#endif //ABSTRACTVM_ABSTRACTVM_HPP