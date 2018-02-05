#ifndef ABSTRACTVM_OPERAND_HPP
#define ABSTRACTVM_OPERAND_HPP

class Operand {

public:

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	Operand(Operand const &copy); // Canonical
	~Operand(); // Canonical
	Operand &operator=(Operand const &copy); // Canonical

private:

	Operand(); // Canonical

};

#endif //ABSTRACTVM_OPERAND_HPP