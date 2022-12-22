Compile using G++:
g++ [main.cpp File Path] -o test -I [boost_1_77_0 Folder Path]

When A registers a listener on B:
- Alistener is a subclass of ServiceListener<B's data member type>
- AListener has data member A*
- AListener is in B's listeners
- When B has an update, B tells Alistener in OnMessage()
- AListener then tells A in ProcessAdd()

BondAlgoExecutionService registers a listener on BondMarketDataService for OrderBook
BondExecutionService registers a listener on BondAlgoExecutionService for AlgoExecution
BondTradeBookingService registers a listener on BondExecutionService for ExecutionOrder
BondPositionService registers a listener on BondTradeBookingService for Trade
BondAlgoStreamingService registers a listener on BondPricingService for Price
BondStreamingService registers a listener on BondAlgoStreamingService for AlgoStream
GUIService registers a listener on BondPricingService for Price
BondInquiryServiceConnector has pointer to BondInquiryService
register a listener on BondInquiryService

InquiryService:
BondInquiryService calls SendQuote(id, 100) and in it calls the Connector.Publish(inquiry)


All HistoricalDataService/Listener/Connector classes are generic
RiskHistoricalDataService<T> has a AddBucketedSector() method that adds a BucketedSector<T> into its list of sectors (data member). The sectors' risk will be recorded as well as each individual product.
RiskHistoricalDataService<T> has GetBucketedRisk() to record sector risks. Same implementation as in BondRiskService.

Created AlgoExecutionService and AlgoStreamingService class.
Created GUIservice class which has derived class BondGUIService.
Defined <, >, <=, >=, == for Order class. The comparison is the based on price priority.
Defined BondAlgoExecutionService::GoodToSend() to check whether the Algo wants to send execution order. (Whether spread is tight enough in this case)
ExecutionOrder have ids incrementing by 6 each time because for every 6 orderbooks there is 1 execution order that is good to send (spread is tight enough)

BondRiskService::GetBucketedRisk():
- The quantity in this PV01<BucketedSector<Bond>> is the sum of quantities of all products
- The PV01 is the quantity-weighted average of PV01s of all products 
- In this way, the sum of risks remain the same

Added functionalities
- StringToPrice(): turn price string into double
- XXXToSting(): turn enum values into strings

Added str() member function to turn data into string in classes:
- Position
- PV01
- ExecutionOrder
- PriceStream
- Inquiry
so they can be easier to print/write

Added GetProductId() in BucketedSector<T> returning sector name so that PV01::str() can print sector and idividual products differently



BondInquiryService and BondInquiryServiceConnector are connected to each other (They have each other as data members). Therefore, they are defined in the same file.

classes that generate connectors themselves:
- all generic HistoricalDataServices
- BondStreamingService
- BondInquiryService
- BondExecutionService
- BondGUIService
- BondTradeBookingService

Deleted const keyword in PersistData() in HistoricalDataService classes because it will call Publish() which has not const keyword for the data argument.

In BonExecutionService::AddAlgoExecution(), execute all orders in market BROKERTEX for now. Further modification is allowed.
In BonExecutionService::ExecuteOrder(), nothing to do with market in current version. Implementable when there's an Exchange class



Because the printing in Publish() in classes BondExecutionServiceConnector and BondStreamingServiceConnector takes too long to print every message. We will print once only every 10000 mesage.
