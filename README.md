# Kobocoin [KOBO]
## A micropayment system and digitial currency similar to Bitcoin. The Kobocoin blockchain is optimised for mobile phone usage, and has an African heritage.


RPC Port: 3341

P2P Port: 9011

Algorithm: X15 PoW/PoS

Ticker: KOBO

PoS Started on block 43,200 (PoW end - 25th February, 2015)

Approx number of coins in circulation after PoW end: 23,500,000

Max Coins: 350,000,000

PoS currency growth per year: 10%

Max stake age: No max

Min stake age: 24 hrs

Timings of block (in seconds): 60

Coins per Block : 1,000

50 confirmations required for mined blocks

6 confirmations required for transactions

No premine


# Installation Instructions
## Building Kobocoind (daemon) and kobocoin-qt (wallet/GUI)

### 1. Install dependencies and download source code
`sudo apt-get update`

`sudo apt-get install git`

`sudo apt-get install qt4-qmake libqt4-dev build-essential libssl-dev libdb++-dev libminiupnpc-dev libqrencode-dev`


`sudo apt-get install libboost-all-dev`

`cd /<install_directory>/`

`git clone git://github.com/kobocoin/Kobocoin`

`sudo chmod -R 775 Kobocoin`

### 2. Build Kobocoind (daemon)
`cd /<install_directory>/Kobocoin/src/`

`cp makefile.unix Makefile`

`make`

### 3. Build kobocoin-qt (wallet/GUI)
`cd /<install_directory>/Kobocoin/`

`qmake`

`make`
