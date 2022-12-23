Tony (Haobo) Zhang

Compile using G++ (Mac):
g++ [main.cpp File Path] -o ./test -I [boost Folder Path]
g++ ./test

Takes 16 seconds to finish on my MacBook. (Reduced data size)



1. Class design

Created AlgoExecutionService and AlgoStreamingService class as base classes for BondAlgoExecutioin and BondAlgoStreamingSercice, respectively.
Created GUIservice class which has derived class BondGUIService.

--- HistoricalDataService classes:
All HistoricalDataService/Listener/Connector classes are generic.

RiskHistoricalDataService<T> has an AddBucketedSector() method that adds a BucketedSector<T> into its list of sectors (data member). The sectors' risk will be recorded as well as each individual product.

RiskHistoricalDataService<T> has GetBucketedRisk() to record sector risks. Same implementation as in BondRiskService.



2. Listeners:

When A registers a listener on B:
- Alistener is a subclass of ServiceListener<B's data member type>
- AListener has data member A*
- AListener is in B's listeners
- When B has an update, B tells Alistener in OnMessage()
- AListener then tells A in ProcessAdd()

Listeners have to use their corresponding service (A) pointer as a parameter for constructor

BondAlgoExecutionService registers a listener on BondMarketDataService for OrderBook
BondExecutionService registers a listener on BondAlgoExecutionService for AlgoExecution
BondTradeBookingService registers a listener on BondExecutionService for ExecutionOrder
BondPositionService registers a listener on BondTradeBookingService for Trade
BondRiskService registers a listener on BondPositionService for Position
BondAlgoStreamingService registers a listener on BondPricingService for Price
BondStreamingService registers a listener on BondAlgoStreamingService for AlgoStream
BondGUIService registers a listener on BondPricingService for Price
HistoricalDataService classes register listeners to their corresponding services of the corresponding data



3. Connectors:

classes that generate connectors themselves:
- all generic HistoricalDataServices
- BondStreamingService
- BondInquiryService
- BondExecutionService
- BondGUIService
- BondTradeBookingService

BondInquiryService and BondInquiryServiceConnector are connected to each other (They have each other as data members). Therefore, they are defined in the same file.



4. Functionalities

Defined <, >, <=, >=, == operators for Order class. The comparison is the based on price priority.

Defined BondAlgoExecutionService::GoodToSend() to check whether the Algo wants to send execution order. (Whether spread is tight enough in this case)

BondRiskService::GetBucketedRisk():
- The quantity in this PV01<BucketedSector<Bond>> is the sum of quantities of all products
- The PV01 is the quantity-weighted average of PV01s of all products 
- In this way, the sum of risks remain the same

Added functionalities
- StringToPrice(): turn price string into double
- XXXToSting(): turn enum values into strings

Added str() member function to turn data into string in classes so they can be easier to print/write:
- Position
- PV01
- ExecutionOrder
- PriceStream
- Inquiry

Added GetProductId() in BucketedSector<T> returning sector name so that PV01::str() can print sector and idividual products differently: print sector name for sectors and print product id for individual procucts

Changed some const keywords in the given files in order to allow interaction functions (wrappers) and derived function to work together.
- e.g. Deleted const keyword in PersistData() in HistoricalDataService classes because it will call Publish() which has not const keyword for the data argument.

When calculating BucketSector risks, all risks (multiplied by quantity) are added together as the bucketed risk, while the bucketed quantity will be unit (1).

Some function declaration/definitions are in utiliity.hpp while others can be found in their corresponding service file

In BonExecutionService::AddAlgoExecution(), execute all orders in market BROKERTEX for now. In BonExecutionService::ExecuteOrder(), nothing to do with market in current version. Implementable when there's an Exchange class. Further modification is allowed when an Exchange-related class is introduced.

Added AlgoExecution<T>::UpdateExecutionOrder(const OrderBook<T>& orderBook) function. When a new order book is received, the BondAlgoExecutionService updates its execution order. Each time the execution order is updated, the static order id number increments by 1. When updating, the order type of the execution order rotates over {FOK, IOC, MARKET, LIMIT, STOP}. The pricing side rotates over {BID, OFFER}. The order is always a child order by default. Further modification is allowed.



5. Data

Input files: prices.txt, trades.txt, marketdata.txt, inquiries.txt
Output files: allinquiries.txt, executions.txt, gui.txt, positions.txt, risk.txt, streaming.txt

Reduced the number of data records generated for each product from 1000000 to 10000 to reduce the program's runtime.

The connectors that publish data by printing to console will only print every 1000 data record so that printing doesn't slow down the program.

ExecutionOrder have ids incrementing by 6 each time because for every 6 order books there is 1 execution order that is good to send (spread is tight enough)

Output data will be appended to the output text files if the files exists already. Otherwise, the output files will be automatically created.
