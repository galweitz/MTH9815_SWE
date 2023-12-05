/**
 * test program for our ProductServices
 */

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace boost::interprocess;

void exercise1() 
{
    // Remove shared memory on construction and destruction
    struct shm_remove {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a shared memory object.
    shared_memory_object shm(create_only, "MySharedMemory", read_write);

    // Set size
    shm.truncate(sizeof(int));

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);

    // Write the integer to the memory
    int* i = static_cast<int*>(region.get_address());
    *i = 123;  // Example integer

    std::cout << "Publisher: Integer 123 written to shared memory." << std::endl;

    // Sleep for a moment to simulate separate processes
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Now, reading from the shared memory (Subscriber logic)
    // Open the shared memory object.
    shared_memory_object shm_read(open_only, "MySharedMemory", read_only);

    // Map the whole shared memory in this process
    mapped_region region_read(shm_read, read_only);

    // Access the shared memory
    int* i_read = static_cast<int*>(region_read.get_address());

    std::cout << "Subscriber: Integer from shared memory: " << *i_read << std::endl;

}

void exercise2()
{
    cout << "\n---------- Testing Futures ---------\n";

    string id1 = "f1";
    string ticker1 = "SPY";
    float strike1 = 100.0;
    date T1(2033, Dec, 5);
    Future f1{ id1,ticker1,strike1,T1 };

    cout << f1 << "\n";

    // Create a FutureProductService
    FutureProductService* futureProductService = new FutureProductService();

    // Add the 10Y note to the FutureProductService and retrieve it from the service
    futureProductService->Add(f1);
    Future future1_ = futureProductService->GetData(id1); // retreive 
    cout << "futureID: " << future1_.GetProductId() << " ==> " << future1_ << endl;
}

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



      exercise1();
      exercise2();
      return 0;
}
