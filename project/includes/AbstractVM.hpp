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
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "IOperand.hpp"
#include "Operand.tpp"
#include "AbstractVMException.hpp"

extern bool globalDebugFlag;

class AbstractVM {

public:
	static AbstractVM *getInstance();

	static std::string stringTrim(const std::string &string);
	static std::vector<std::string> stringSplit(const std::string &string, const char *c);
	static bool isDouble(const std::string &string);
	static bool isInteger(const std::string &string);
	static bool isFloat(std::string const &string);

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

    void parseCommand(std::string prompt);
    void executeCommand(std::string cmd);
    void executeCommand(std::string cmd, std::string parameter);
	std::string getIntegerParameter(std::string string);
	std::string getFloatParameter(std::string string);
	std::string getDoubleParameter(std::string string);

private:
	AbstractVM &operator=(AbstractVM const &copy); // Canonical
	AbstractVM(); // Canonical
	AbstractVM(AbstractVM const &copy); // Canonical
	~AbstractVM() {} // Canonical

	void push(IOperand *iOperand);
    void pop(IOperand *iOperand);
    void dump(IOperand *iOperand);
    void assert(IOperand *iOperand);
    void add(IOperand *iOperand);
    void sub(IOperand *iOperand);
    void mul(IOperand *iOperand);
    void div(IOperand *iOperand);
    void mod(IOperand *iOperand);
    void print(IOperand *iOperand);
    void exit(IOperand *iOperand);

	typedef std::vector<const IOperand *(AbstractVM::*)(const std::string &) const> VectorOperand;
	typedef std::map<std::string, void (AbstractVM::*)(IOperand *)> MapCommand;
	typedef MapCommand::iterator MapCommandIterator;

	static AbstractVM *_singleton;
	VectorOperand _createPointerTab;
	MapCommand _commandMap;
	std::vector<IOperand*> _stack;

};

#endif //ABSTRACTVM_ABSTRACTVM_HPP