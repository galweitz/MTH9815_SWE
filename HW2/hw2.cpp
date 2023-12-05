
#include <iostream>
#include "products.hpp"
#include "productservice.hpp"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <thread>
#include <chrono>

using namespace std;
using namespace boost::interprocess;

/*
 * Contributions of ChatGPT:
 * 1. ChatGPT assited in understanding the usage of boost::interprocess.
 * 2. ChatGPT suggested simple yet effective strategies for testing the program.

 * Notes:
 * - The implementation was further refined and tested beyond the initial guidance from ChatGPT.
 * - While ChatGPT was instrumental in providing a starting point and basic logic, additional development work was performed to ensure robustness and functionality of the code.
 * - This collaboration showcases the potential of AI-assisted coding, especially in conceptualizing data structures and writing initial code drafts.
 */

void exercise1() 
{
    cout << "---------- Publisher & Subscriber ---------\n\n";

    // Remove shared memory on construction and destruction
    struct shm_remove 
    {
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
    cout << "\n\n---------- Testing Futures ---------\n\n";

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

    // Create second Future instance
    string id2 = "f2";
    string ticker2 = "AAPL";
    float strike2 = 150.0;
    date T2(2035, Mar, 10);
    Future f2{ id2, ticker2, strike2, T2 };

    // Add the second Future to the FutureProductService and retrieve it
    futureProductService->Add(f2);
    Future future2_ = futureProductService->GetData(id2); // retrieve
    cout << "futureID: " << future2_.GetProductId() << " ==> " << future2_ << endl;

    // Create third Future instance
    string id3 = "f3";
    string ticker3 = "MSFT";
    float strike3 = 200.0;
    date T3(2037, Aug, 15);
    Future f3{ id3, ticker3, strike3, T3 };

    // Add the third Future to the FutureProductService and retrieve it
    futureProductService->Add(f3);
    Future future3_ = futureProductService->GetData(id3); // retrieve
    cout << "futureID: " << future3_.GetProductId() << " ==> " << future3_ << endl;

    delete futureProductService;
}


void exercise3() 
{
    cout << "\n\n---------- BondProductService ---------\n\n";

    // Create BondProductService and IRSwapProductService instances
    BondProductService bondService;

    // Create some Bond and IRSwap products and add them to the services
    Bond bond1("912797GQ4", CUSIP, "Ticker1", 5.0, date(2024, Mar, 7));
    Bond bond2("US912810RQ31", ISIN, "Ticker2", 2.5, date(2030, Jan, 1));
    Bond bond3("91282CJN2", CUSIP, "Ticker1", 6.0, date(2027, Jul, 15));

    bondService.Add(bond1);
    bondService.Add(bond2);
    bondService.Add(bond3);

    // Test GetBonds utility function
    string tickerToSearch = "Ticker1";
    vector<Bond> bonds = bondService.GetBonds(tickerToSearch);

    cout << "Bonds with ticker " << tickerToSearch << ":" << endl;
    for (auto& bond : bonds) 
    {
        cout << bond << endl;
    }


    cout << "\n\n---------- IRSwapProductService ---------\n\n";

    // Create IRSwapProductService instance
    IRSwapProductService swapService;

    // Create IRSwap products and add them to the service
    IRSwap swap1("SWAP1", THIRTY_THREE_SIXTY, ACT_THREE_SIXTY, ANNUAL, LIBOR, TENOR_3M, date(2021, Jan, 1), date(2026, Jan, 1), USD, 5, SPOT, OUTRIGHT);
    IRSwap swap2("SWAP2", ACT_THREE_SIXTY_FIVE, ACT_THREE_SIXTY, SEMI_ANNUAL, EURIBOR, TENOR_6M, date(2022, Mar, 15), date(2027, Mar, 15), EUR, 5, FORWARD, CURVE);
    IRSwap swap3("SWAP3", THIRTY_THREE_SIXTY, ACT_THREE_SIXTY, QUARTERLY, LIBOR, TENOR_1M, date(2023, Jun, 10), date(2028, Jun, 10), GBP, 7, IMM, FLY);
    IRSwap swap4("SWAP4", ACT_THREE_SIXTY, ACT_THREE_SIXTY_FIVE, ANNUAL, EURIBOR, TENOR_12M, date(2024, Sep, 20), date(2034, Sep, 20), USD, 10, BASIS, CURVE);

    swapService.Add(swap1);
    swapService.Add(swap2);
    swapService.Add(swap3);
    swapService.Add(swap4);

    // Test utility functions
    // 1. Fixed Leg Day Count Convention
    auto swapsByFixedLegDayCount = swapService.GetSwaps(THIRTY_THREE_SIXTY);
    cout << "IRSwaps with Fixed Leg Day Count Convention 30/360:" << endl;
    for (const auto& swap : swapsByFixedLegDayCount) 
    {
        cout << swap << endl;
    }

    // 2. Fixed Leg Payment Frequency
    auto swapsByPaymentFreq = swapService.GetSwaps(ANNUAL);
    cout << "\nIRSwaps with Fixed Leg Payment Frequency Annual:" << endl;
    for (const auto& swap : swapsByPaymentFreq) 
    {
        cout << swap << endl;
    }

    // 3. Floating Index
    auto swapsByFloatingIndex = swapService.GetSwaps(LIBOR);
    cout << "\nIRSwaps with Floating Index LIBOR:" << endl;
    for (const auto& swap : swapsByFloatingIndex) 
    {
        cout << swap << endl;
    }

    // 4. Term in Years Greater Than
    auto swapsGreaterThan = swapService.GetSwapsGreaterThan(6);
    cout << "\nIRSwaps with Term in Years Greater Than 6:" << endl;
    for (const auto& swap : swapsGreaterThan) 
    {
        cout << swap << endl;
    }

    // 5. Term in Years Less Than
    auto swapsLessThan = swapService.GetSwapsLessThan(6);
    cout << "\nIRSwaps with Term in Years Less Than 6:" << endl;
    for (const auto& swap : swapsLessThan) 
    {
        cout << swap << endl;
    }

    // 6. Swap Type
    auto swapsByType = swapService.GetSwaps(SPOT);
    cout << "\nIRSwaps with Swap Type SPOT:" << endl;
    for (const auto& swap : swapsByType) 
    {
        cout << swap << endl;
    }

    // 7. Swap Leg Type
    auto swapsByLegType = swapService.GetSwaps(OUTRIGHT);
    cout << "\nIRSwaps with Swap Leg Type Outright:" << endl;
    for (const auto& swap : swapsByLegType) 
    {
        cout << swap << endl;
    }


}

int main()
{
      exercise1();
      exercise2();
      exercise3();
      return 0;
}
