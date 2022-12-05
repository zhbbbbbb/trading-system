/**
 * test program for our ProductServices
 */

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"

template <typename T>
std::ostream& operator << (std::ostream& os, std::vector<T>& arr)
{
    for (unsigned int i = 0; i < arr.size(); ++i)
    {
        os << arr[i] << " ";
    }
    return os;
}

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

  // Create the 3Y treasury note
  date maturityDate3(2018, Nov, 5);
  string cusip3 = "822828TW0";
  Bond treasuryBond3(cusip3, CUSIP, "T1", 0.75, maturityDate3);

  // Create a BondProductService
  BondProductService *bondProductService = new BondProductService();

  // Add the 10Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond);
  Bond bond = bondProductService->GetData(cusip);
  //cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Add the 2Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond2);
  bond = bondProductService->GetData(cusip2);
  //cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Add the 3Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond3);
  bond = bondProductService->GetData(cusip3);
  //cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

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
  //cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(imm2YSwap);
  swap = swapProductService->GetData(imm2Y);
  //cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  //// testing part for HW
  // Bond
  string ticker1 = "T";
  std::vector<Bond> bonds = bondProductService->GetBonds(ticker1);
  cout << "Found bonds with ticker (" << ticker1 << "): " << bonds << endl << endl;

  // swap
  std::vector<IRSwap> swaps;
  // Get all Swaps with the specified fixed leg day count convention
  swaps = swapProductService->GetSwaps(THIRTY_THREE_SIXTY);
  cout << "Found swaps: " << swaps << endl << endl;

  // Get all Swaps with the specified fixed leg payment frequency
  swaps = swapProductService->GetSwaps(SEMI_ANNUAL);
  cout << "Found swaps: " << swaps << endl << endl;

  // Get all Swaps with the specified floating index
  swaps = swapProductService->GetSwaps(LIBOR);
  cout << "Found swaps: " << swaps << endl << endl;

  // Get all Swaps with a term in years greater than the specified value
  swaps = swapProductService->GetSwapsGreaterThan(5);
  cout << "Found swaps: " << swaps << endl << endl;

  // Get all Swaps with a term in years less than the specified value
  swaps = swapProductService->GetSwapsLessThan(5);
  cout << "Found swaps: " << swaps << endl << endl;

  // Get all Swaps with the specified swap type
  swaps = swapProductService->GetSwaps(IMM);
  cout << "Found swaps: " << swaps << endl << endl;

  // Get all Swaps with the specified swap leg type
  swaps = swapProductService->GetSwaps(OUTRIGHT);
  cout << "Found swaps: " << swaps << endl << endl;



  return 0;
}
