![Kobocoin](http://kobocoin.com/KobocoinLogoNew.png "Kobocoin")
## A micropayment system and digitial currency similar to Bitcoin. 
## Kobocoin is PoS, optimised for mobile phone usage, and has an African heritage.


+ Ticker : KOBO
+ RPC Port : 3341
+ P2P Port : 9011
+ Algorithm : X15 PoW/PoS
+ PoS Started on block 43,200 (PoW end - 25th February, 2015)
+ Approx number of coins in circulation after PoW end : 23,500,000
+ Max Coins : 350,000,000
+ PoS currency growth per year : 10%
+ Max stake age : No max
+ Min stake age : 24 hrs
+ Timings of block (in seconds) : 60
+ Coins per Block : 1,000
+ 50 confirmations required for mined blocks
+ No premine

## Building Kobocoind (daemon/CLI) and kobocoin-qt (wallet/GUI)
[Ubuntu 16.04 recommended](http://releases.ubuntu.com/16.04/ "Ubuntu 16.04")
### 1. Install dependencies and download source code
```
sudo apt-get update
sudo apt-get install git
sudo apt-get install qt4-qmake libqt4-dev build-essential libssl-dev libdb++-dev libminiupnpc-dev libqrencode-dev
sudo apt-get install libboost-all-dev
git clone git://github.com/kobocoin/Kobocoin
sudo chmod -R 775 Kobocoin
```
### 2. Build Kobocoind (daemon)
```
goto <installDirectory>/Kobocoin/src/
cp makefile.unix Makefile
make
strip Kobocoind
```

### 3. Build kobocoin-qt (wallet/GUI)
```
goto <installDirectory>/Kobocoin/
qmake
make
strip kobocoin-qt
```
