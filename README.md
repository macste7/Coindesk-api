# Coindesk-api
*_Simple library for retrieving and parsing data from api.coindesk.com_*

With library you can get currect prize of Bitcoin in FIAT like:
- [EUR] - Euro :euro:
- [BGP] - British Pound Sterling :pound:
- [USD] - United States Dollar :money_with_wings:

The deafult timeout is 60s because coindesk refresh api after 60s. If you want
change delay of sending GET request, specify in class constructor, but you can
skip this argument if you want.

# Get value from struct :construction:
  For getting the values you have to use: 
```name_of_object.definition_name_of_struct.variable```

For example:
```crypto1.usd.rate_float```
return value depends on the variable. Look below..

## Struct Data data  :memo:
|variable       |example   | example returned value|
|---------------|----------| -----|
|char *time_updated   |crypto1.data.time.updated|Mar 25, 2021 14:08:00 UTC|
|char *time_updatedISO|crypto1.data.time_updatedISO|2021-03-25T14:08:00+00:00|
|char *time_updateduk |crypto1.data.time_updateduk|Mar 25, 2021 at 14:08 GMT|
|char *disclaimer     |crypto1.data.disclaimer|This data was produced from the CoinDesk Bitcoin Price Index (USD). Non-USD currency data converted using hourly conversion rate from openexchangerates.org|
|char *chartname      |crypto1.data.chartname| Bitcoin|
## Struct USD usd  :money_with_wings:
|variable       |example   | example returned value|
|---------------|----------|-----------------------|
|char *code   |crypto1.usd.time.code|USD|
|char *symbol|crypto1.usd.symbol|&#36;|
|char *rate_char|crypto1.usd.rate_char|51,858.9553|
|char *description|crypto1.usd.description|United States Dollar|
|float rate_float|crypto1.usd.rate_float|51858.95|

## Struct GBP gbp :pound:
|variable       |example   | example returned value|
|---------------|----------|-----------------------|
|char *code   |crypto1.gbp.time.code|GBP|
|char *symbol|crypto1.gbp.symbol|&pound;|
|char *rate_char|crypto1.gbp.rate_char|37,805.2303|
|char *description|crypto1.gbp.description|British Pound Sterling|
|float rate_float|crypto1.gbp.rate_float|37805.23|

## Struct EUR eur :euro:
|variable       |example   | example returned value|
|---------------|----------|-----------------------|
|char *code   |crypto1.eur.time.code|EUR|
|char *symbol|crypto1.eur.symbol|&euro;|
|char *rate_char|crypto1.eur.rate_char|43,919.0381|
|char *description|crypto1.eur.description|Euro|
|float rate_float|crypto1.eur.rate_float|43919.03|

Check yourself if api is working with: [api.coindesk.com](https://api.coindesk.com/v1/bpi/currentprice.json) or by using CURL: ```curl --location --request GET https://api.coindesk.com/v1/bpi/currentprice.json```
