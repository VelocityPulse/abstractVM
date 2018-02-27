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

#include <fstream>
#include "../includes/AbstractVM.hpp"

bool globalDebugFlagNameFunction = false;
bool globalDebugFlagInfoMessage = false;
int globalDebugLineRead = 0;

void manageStandardEntry(AbstractVM &vm) {
	std::string line;

	while (std::getline(std::cin, line)) {
		globalDebugLineRead++;
		try {
			line = AbstractVM::stringTrim(line);
			if (line[0] == ';' &&
				line[1] == ';') {
				return;
			} else if (line[0] == ';' || line == "") { ;
			} else {
				vm.parseCommand(line);
			}
		} catch (AbstractVMException &e) {
			std::cout << e.what() << std::endl;
			break;
		}
	}
}

void manageWithArgument(AbstractVM &vm, char *string) {
	std::string line;
	std::ifstream file(string);
	if (file) {
		while (getline(file, line)) {
			globalDebugLineRead++;
			try {
				line = AbstractVM::stringTrim(line);
				if (line[0] == ';' &&
					line[1] == ';') {
					break;
				} else if (line[0] == ';' || line == "") { ;
				} else {
					vm.parseCommand(line);
				}
			} catch (AbstractVMException &e) {
				std::cout << e.what() << std::endl;
				break;
			}
		}
		file.close();
	}
}


int main(int argc, char **argv) {
	if (argc == 2) {
		manageWithArgument(*AbstractVM::getInstance(), argv[1]);
	} else if (argc == 1) {
		manageStandardEntry(*AbstractVM::getInstance());
	} else {
		std::cout << "bad entry" << std::endl;
	}
	return 1;
}

