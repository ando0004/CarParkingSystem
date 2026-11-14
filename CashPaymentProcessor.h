#pragma once
#include "IPaymentProcessor.h"

class CashPaymentProcessor : public IPaymentProcessor {
public:
	bool processPayment(double amount, const std::string& paymentDetails) override {
		std::cout << "[Cash Payment] Processed payment of $" << amount << " in cash.\n";
		return true;
	}
}
