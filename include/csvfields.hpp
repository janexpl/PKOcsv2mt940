//
// Created by Janusz Kwiatkowski on 19/10/2019.
//
#pragma once
#include <iostream>

using namespace std;
struct csvfields {
    string date = "";
    string accountDate = "";
    string contractorAccount = "";
    string operationTitle = "";
    string contractorNameAddress = "";
    string operationLoc = "";
    string operationDate = "";
    string cashBackamount = "";
    string referenceNo = "";
    double orgOperationAmount = 0;
    string cardNumber = "";
    string transactionIdent = "";
    string operationType = "";
    double amount = 0;
    string currency = "PLN";
    double balance = 0;
};
