#pragma once
#include "IPaymentProcessor.h"
#include <iostream>

class CreditCardPaymentProcessor : public IPaymentProcessor {
public:
    bool processPayment(double amount, const std::string& paymentDetails) override {
        if (paymentDetails.empty()) {
            std::cerr << "[Card Payment Error] Missing payment token/card details.\n";
            return false;
        }

        std::cout << "[Card Payment] Successfully charged $" << amount
            << " using card/token: " << paymentDetails << "\n";

        return true;
    }
};
