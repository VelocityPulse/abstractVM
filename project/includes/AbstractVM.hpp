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

#include <string>
#include <vector>
#include <map>
#include <list>
#include "IOperand.hpp"

class AbstractVM {

public:
	AbstractVM(); // Canonical
	AbstractVM(AbstractVM const &copy); // Canonical
	~AbstractVM(); // Canonical


	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	AbstractVM &operator=(AbstractVM const &copy); // Canonical

private:
	typedef const IOperand *(AbstractVM::*OperandFunc)(const std::string &) const;

	std::vector<OperandFunc> createPointerTab;

};


#endif //ABSTRACTVM_ABSTRACTVM_HPP