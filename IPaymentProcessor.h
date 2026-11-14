#pragma once
#include <string>

class IPaymentProcessor {
public:
	virtual ~IPaymentProcessor() = default;
	virtual bool processPayment(double amount, const std::string& paymentDetails) = 0;
};
