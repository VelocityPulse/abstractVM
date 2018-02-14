/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:42:28 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/05 10:42:30 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/AbstractVM.hpp"
#include "../includes/AbstractVMException.hpp"

void manageStandardEntry(AbstractVM *vm) { //TODO 12 Feb 2018 11:37 make the parameter a reference
	std::string line;

	while (std::getline(std::cin, line)) {
		try {
			line = AbstractVM::stringTrim(line);
			if (line[0] == ';' && line[1] == ';') {
				return;
			} else if (line[0] != ';') {
				vm->parseCommand(line);
			}
		} catch (AbstractVMException &e) {
			std::cout << e.what() << std::endl;
		}
	}
}

int main(int argc, char **argv) {

	AbstractVM *avm = AbstractVM::getInstance();
	manageStandardEntry(avm);

//	IOperand const *operand = avm.createOperand(Int16, "2440");
//	std::cout << "[" + operand->toString() + "]" << std::endl;

//	if (argc == 2) {
//		std::cout << "arguments" << std::endl;
//	} else if (argc == 1) {
//		manageStandardEntry();
//		std::cout << "standard entry" << std::endl;
//	} else {
//		std::cout << "bad entry" << std::endl;
//	}
	std::cout << "SUCCESS end of program" << std::endl;
//	return 1;
}
