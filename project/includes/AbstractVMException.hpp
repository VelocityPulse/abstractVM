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
	AbstractVMException(); // Canonical
	AbstractVMException(std::string msg);
	AbstractVMException(AbstractVMException const &copy); // Canonical
	~AbstractVMException(); // Canonical

	virtual const char* what() const throw ();

	AbstractVMException &operator=(AbstractVMException const &copy); // Canonical

private:
	std::string _msg;

};


#endif //ABSTRACTVM_ABSTRACTVMEXCEPTION_HPP