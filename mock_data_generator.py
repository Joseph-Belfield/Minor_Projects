import time
import random

startingUnixTime = int(time.time()) 
startingStockPrice = random.triangular(15, 150, 60) # random int between 15-150, modal value 60
dailySkew = random.triangular(0.9995, 1.0005, 1)

# Open/create file in write mode, closes when indentation ends
with open("mock_data.csv", "w") as file:
    
    file.write("Timestamp,Price,Volume\n") 

    second = 0;
    stockPrice = startingStockPrice

    while second < 3600: # models an hour of data
        
        # each loop you need: a unix time, a stock price, a number of shares
        currentTime = startingUnixTime + second
            
        relativeStockPriceChange = random.triangular(0.9995, 1.0005, dailySkew)
        stockPrice *= relativeStockPriceChange

        
        modalShares = # have the modal number of shares sold affected by change in stock price
        numberOfSharesTraded = round(random.triangular(10, 500, modalShares))

        # write data to file
        line = f"{currentTime},{stockPrice:.2f},{numberOfSharesTraded}\n"
        file.write(line)

        second += random.randint(1,3) # add small random passing of time
        



