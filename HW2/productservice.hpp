/**
 * productservice.hpp defines Bond and IRSwap ProductServices
 */

#include <iostream>
#include <map>
#include "products.hpp"
#include "soa.hpp"

/**
 * Bond Product Service to own reference data over a set of bond securities.
 * Key is the productId string, value is a Bond.
 */
class BondProductService : public Service<string,Bond>
{

public:
  // BondProductService ctor
  BondProductService();

  // Return the bond data for a particular bond product identifier
  Bond& GetData(string productId);

  // Add a bond to the service (convenience method)
  void Add(Bond &bond);


  vector<Bond> GetBonds(string& _ticker) 
  {
      vector<Bond> bonds;
      for (auto& item : bondMap) {
          if (item.second.GetTicker() == _ticker) {
              bonds.push_back(item.second);
          }
      }
      return bonds;
  }

private:
  map<string,Bond> bondMap; // cache of bond products

};

/**
 * Interest Rate Swap Product Service to own reference data over a set of IR Swap products
 * Key is the productId string, value is a IRSwap.
 */
class IRSwapProductService : public Service<string,IRSwap>
{
public:
  // IRSwapProductService ctor
  IRSwapProductService();

  // Return the IR Swap data for a particular bond product identifier
  IRSwap& GetData(string productId);

  // Add a bond to the service (convenience method)
  void Add(IRSwap &swap);


  //Get Swaps by Fixed Leg Day Count Convention
  vector<IRSwap> GetSwaps(DayCountConvention _fixedLegDayCountConvention) 
  {
      vector<IRSwap> swaps;
      for (auto& item : swapMap) {
          if (item.second.GetFixedLegDayCountConvention() == _fixedLegDayCountConvention) 
          {
              swaps.push_back(item.second);
          }
      }
      return swaps;
  }

  //Get Swaps by Fixed Leg Payment Frequency
  vector<IRSwap> GetSwaps(PaymentFrequency _fixedLegPaymentFrequency) 
  {
      vector<IRSwap> swaps;
      for (auto& item : swapMap) {
          if (item.second.GetFixedLegPaymentFrequency() == _fixedLegPaymentFrequency) 
          {
              swaps.push_back(item.second);
          }
      }
      return swaps;
  }

  //Get Swaps by Floating Index
  vector<IRSwap> GetSwaps(FloatingIndex _floatingIndex) 
  {
      vector<IRSwap> swaps;
      for (auto& item : swapMap) {
          if (item.second.GetFloatingIndex() == _floatingIndex) {
              swaps.push_back(item.second);
          }
      }
      return swaps;
  }

  //Get Swaps with a Term in Years Greater Than a Value
  vector<IRSwap> GetSwapsGreaterThan(int _termYears) 
  {
      vector<IRSwap> swaps;
      for (auto& item : swapMap) {
          if (item.second.GetTermYears() > _termYears) 
          {
              swaps.push_back(item.second);
          }
      }
      return swaps;
  }

  //Get Swaps with a Term in Years Less Than a Value
  vector<IRSwap> GetSwapsLessThan(int _termYears) 
  {
      vector<IRSwap> swaps;
      for (auto& item : swapMap) {
          if (item.second.GetTermYears() < _termYears) 
          {
              swaps.push_back(item.second);
          }
      }
      return swaps;
  }

  //Get Swaps by Swap Type
  vector<IRSwap> GetSwaps(SwapType _swapType) 
  {
      vector<IRSwap> swaps;
      for (auto& item : swapMap) {
          if (item.second.GetSwapType() == _swapType) 
          {
              swaps.push_back(item.second);
          }
      }
      return swaps;
  }

  //Get Swaps by Swap Leg Type
  vector<IRSwap> GetSwaps(SwapLegType _swapLegType) 
  {
      vector<IRSwap> swaps;
      for (auto& item : swapMap) 
      {
          if (item.second.GetSwapLegType() == _swapLegType) {
              swaps.push_back(item.second);
          }
      }
      return swaps;
  }


private:
  map<string,IRSwap> swapMap; // cache of IR Swap products

};

BondProductService::BondProductService()
{
  bondMap = map<string,Bond>();
}

Bond& BondProductService::GetData(string productId)
{
  return bondMap[productId];
}

void BondProductService::Add(Bond &bond)
{
  bondMap.insert(pair<string,Bond>(bond.GetProductId(), bond));
}

IRSwapProductService::IRSwapProductService()
{
  swapMap = map<string,IRSwap>();
}

IRSwap& IRSwapProductService::GetData(string productId)
{
  return swapMap[productId];
}

void IRSwapProductService::Add(IRSwap &swap)
{
  swapMap.insert(pair<string,IRSwap>(swap.GetProductId(), swap));
}

class FutureProductService : public Service<string,Future>
{
  private:
    map<string,Future> futureMap;

  public:
    FutureProductService();
    Future& GetData(string productId);
    void Add(Future &future);
};

FutureProductService::FutureProductService() {futureMap = map<string, Future>();}
Future& FutureProductService::GetData(string productId) {return futureMap[productId];}
void FutureProductService::Add(Future &future) {futureMap.insert(pair<string, Future>(future.GetProductId(), future));}