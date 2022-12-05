/**
 * test program for our ProductServices
 */

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"

using namespace std;

int main()
{
  // Create the 10Y treasury note
  date maturityDate(2025, Nov, 16);
  string cusip = "912828M56";
  Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDate);

  // Create the 2Y treasury note
  date maturityDate2(2017, Nov, 5);
  string cusip2 = "912828TW0";
  Bond treasuryBond2(cusip2, CUSIP, "T", 0.75, maturityDate2);

  // Create a BondProductService
  BondProductService *bondProductService = new BondProductService();

  // Add the 10Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond);
  Bond bond = bondProductService->GetData(cusip);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Add the 2Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond2);
  bond = bondProductService->GetData(cusip2);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Create the Spot 10Y Outright Swap
  date effectiveDate(2015, Nov, 16);
  date terminationDate(2025, Nov, 16);
  string outright10Y = "Spot-Outright-10Y";
  IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

  // Create the IMM 2Y Outright Swap
  date effectiveDate2(2015, Dec, 20);
  date terminationDate2(2017, Dec, 20);
  string imm2Y = "IMM-Outright-2Y";
  IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, IMM, OUTRIGHT);

  // Create a IRSwapProductService
  IRSwapProductService *swapProductService = new IRSwapProductService();

  // Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(outright10YSwap);
  IRSwap swap = swapProductService->GetData(outright10Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(imm2YSwap);
  swap = swapProductService->GetData(imm2Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  // ------------- Futures ---------------

  // Future 1
  cout << "---------- Future 1 testing ----------" << std::endl;
  date expirationDate1(2030, Jan, 1);
  string futureID1 = "future123";
  string ticker1 = "SPY";
  float strike1 = 101.01;
  Future future1 (futureID1, ticker1, strike1, expirationDate1);
  cout << future1 << std::endl;

  // Create a FutureProductService
  FutureProductService* futureProductService = new FutureProductService();

  // Add the 10Y note to the FutureProductService and retrieve it from the service
  futureProductService->Add(future1);
  Future future1_ = futureProductService->GetData(futureID1);
  cout << "futureID: " << future1_.GetProductId() << " ==> " << future1_ << endl;


  // Future 2
  cout << "---------- Future 2 testing ----------" << std::endl;
  date expirationDate2(2040, Feb, 2);
  string futureID2 = "future234";
  float strike2 = 202.02;
  EuroDollarFuture future2(futureID2, strike2, expirationDate2);
  cout << future2 << std::endl;

  // Add the 10Y note to the FutureProductService and retrieve it from the service
  futureProductService->Add(future2);
  Future future2_ = futureProductService->GetData(futureID2);
  cout << "futureID: " << future2_.GetProductId() << " ==> " << future2_ << endl;


  // Future 3
  cout << "---------- Future 3 testing ----------" << std::endl;
  date expirationDate3(2050, Mar, 3);
  string futureID3 = "future345";
  string ticker3 = "AAPL";
  float strike3 = 303.03;
  BondFuture future3(futureID3, ticker3, strike3, expirationDate3);
  cout << future3 << std::endl;

  // Add the 10Y note to the FutureProductService and retrieve it from the service
  futureProductService->Add(future3);
  Future future3_ = futureProductService->GetData(futureID3);
  cout << "futureID: " << future3_.GetProductId() << " ==> " << future3_ << endl;


  return 0;
}
