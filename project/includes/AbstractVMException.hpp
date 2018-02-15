/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVMException.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:40:24 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/12 13:40:24 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_ABSTRACTVMEXCEPTION_HPP
#define ABSTRACTVM_ABSTRACTVMEXCEPTION_HPP

#include <iostream>

class AbstractVMException : public std::exception {

public:
	class Overflow {
	public:
		Overflow(); // Canonical
		~Overflow(); // Canonical
		Overflow(Overflow const &copy); // Canonical
		virtual const char *what() const throw();
	private:
		Overflow &operator=(Overflow const &copy); // Canonical
	};

	class Underflow {
	public:
		Underflow(); // Canonical
		~Underflow(); // Canonical
		Underflow(Underflow const &copy); // Canonical
		virtual const char *what() const throw();
	private:
		Underflow &operator=(Underflow const &copy); // Canonical
	};

	AbstractVMException(); // Canonical
	AbstractVMException(std::string const msg);
	AbstractVMException(std::string const tag, std::string const msg);
	AbstractVMException(AbstractVMException const &copy); // Canonical
	~AbstractVMException(); // Canonical

	virtual const char *what() const throw();

	AbstractVMException &operator=(AbstractVMException const &copy); // Canonical

private:
	std::string _tag;
	std::string _msg;

};


#endif //ABSTRACTVM_ABSTRACTVMEXCEPTION_HPP