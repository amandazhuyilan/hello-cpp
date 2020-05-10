#include <string>

class Account {
	std::string name_;
	int account_no;
	static int account_no_generator; 

protected:
	float balance_;

public:
	Account(std::string &name,  float balance) :
	name_(name), balance_(balance) {
		account_no = ++account_no_generator;
	}
	~Account();

	const std::string GetName() const {
		return name_;
	}
	float GetBalance() const {
		return balance_;
	}
	int GetAccountNo() const {
		return account_no_;
	}

}

class Savings : public Account {
	float interest_rate_;
public:
	Savings(const std::string &name, float balance, float interest_rate) : Account(name, balance), interest_rate_(interest_rate);

	~Savings();
	float GetInterestRate() {
		return interest_rate_;
	}
};


class Checking : public Account {
public:
	using Account::Account; // use base class constructor instead having to implement the constrictor in the base class just to invoke the base class constructor. This can only be accomplished if the child class doesn't have its own attribute(s).
	~Checking();
};
