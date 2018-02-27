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
bool globalDebugContinueWithErrors = false;

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
			if (!globalDebugContinueWithErrors) {
				break;
			}
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
				if (!globalDebugContinueWithErrors) {
					break;
				}
			}
		}
		file.close();
	}
}


int main(int argc, char **argv) {
	if (argc > 1) {
		//argv[1] == "-bonus1"
		if (argc == 3 && strcmp(argv[1], "-bonus1") == 0) {
			globalDebugContinueWithErrors = true;
			manageWithArgument(*AbstractVM::getInstance(), argv[2]);
		} else if (argc == 2) {
			manageWithArgument(*AbstractVM::getInstance(), argv[1]);
		} else {
			std::cout << "Too many arguments. [-bonus1] for continue even errors are meet" << std::endl;
		}
	} else {
		manageStandardEntry(*AbstractVM::getInstance());
	}
	return 1;
}

