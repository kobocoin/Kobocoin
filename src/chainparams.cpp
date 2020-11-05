// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"
#include "consensus/consensus.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "base58.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << CScriptNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = 0;
    txNew.vout[0].scriptPubKey.clear();

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.vtx[0].nTime = nTime;
    genesis.vtx[0].UpdateHash();
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion)
{
    const char* pszTimestamp = "World Leaders Head Paris March Honoring Terror Victims ABC NEWS 12012015";
    return CreateGenesisBlock(pszTimestamp, nTime, nNonce, nBits, nVersion);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes
        consensus.nPowTargetSpacing = 60;
        consensus.nPowTargetSpacing2 = 2 * 60; // Prep for future hard fork
		consensus.nPowTargetSpacing2_start = 10000000; // Prep for future hard fork
        consensus.nLastPOWBlock = 43200;
        consensus.nRejectPoSbelow = 4000; //m2:
        consensus.nStakeMinAge = 24 * 60 * 60;
		consensus.nBlockVersionCheckStart = 5000; //m2: blocks after this will be version checked.
        consensus.nModifierInterval = 10 * 60;
        consensus.nStakeSplitAge = 24 * 60 * 60;
        consensus.timeLimitChange = 1421090888;
        consensus.nStakeCombineThreshold = 1000 * COIN;
        consensus.checkpointPubKey = "04011f5be18b59843bcb0bc09965ebf1d188b401d90c17dcfdfb07d8a97e56e6dd1c2ce164c542f73598eafe2bc39452813a5398c29a3abb13ebf1f8ef41ce13d9";
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 15120; // 95% of 20160
        consensus.nMinerConfirmationWindow = 20160; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1733081600; //m2
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1764617600; //m2

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1733081600; //m2
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1764617600; //m2

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000118c1523e594");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0xa2;
        pchMessageStart[3] = 0xa3;
        nDefaultPort = 9011;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1421090888, 219702, 0x1e0fffff, 1);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c98be708f9ff86319738d4ce8778f1db7ce140d2d665cca9281eef433bd"));
        assert(genesis.hashMerkleRoot == uint256S("0x3519d54cd3dddf456888921b8e97c43ef6f6204b95683a45f28437d4c44153d3"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("ns1.Kobocoin.com", "seed1.Kobocoin.com", false));
        vSeeds.push_back(CDNSSeedData("ns1.Kobocoin.com", "seed2.Kobocoin.com", false));
        vSeeds.push_back(CDNSSeedData("ns2.Kobocoin.com", "seed3.Kobocoin.com", false));
        vSeeds.push_back(CDNSSeedData("ns2.Kobocoin.com", "seed4.Kobocoin.com", false));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x00000c98be708f9ff86319738d4ce8778f1db7ce140d2d665cca9281eef433bd")),
            1423293722, // * UNIX timestamp of last checkpoint block
            1,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            60000.0     // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nMajorityEnforceBlockUpgrade = 50;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes
        consensus.nPowTargetSpacing = 60;
        consensus.nPowTargetSpacing2 = 2 * 60;	
		consensus.nPowTargetSpacing2_start = 100;
        consensus.nLastPOWBlock = 2000;
        consensus.nRejectPoSbelow = 100;
        consensus.nStakeMinAge = 20 * 60; // testnet min age is 20 mins
        consensus.nModifierInterval = 60;
        consensus.nStakeSplitAge = 24 * 60 * 60;
        consensus.timeLimitChange = 1455825600;
        consensus.nBlockVersionCheckStart = 5; //m2: blocks after this will be version checked.
        consensus.nStakeCombineThreshold = 1000 * COIN;
        consensus.checkpointPubKey = "043824867726f0c11fa2c4d62c1be60cf2bbaced609e17f099ca318b56addb3b7e47f38c983580b82e3b89fee9fab7c9dada97bc66bc4bc249f18a7a7fd139005a";
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1733081600; //m2
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1733081600; //m2

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1733081600; //m2
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1733081600; //m2

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        pchMessageStart[0] = 0x71;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0x0f;		
        nDefaultPort = 19011;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1421090888, 219702, 0x1e0fffff, 1);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c98be708f9ff86319738d4ce8778f1db7ce140d2d665cca9281eef433bd"));
        assert(genesis.hashMerkleRoot == uint256S("0x3519d54cd3dddf456888921b8e97c43ef6f6204b95683a45f28437d4c44153d3"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("ns1.Kobocoin.com", "testnet-seed1.Kobocoin.com", false));
        vSeeds.push_back(CDNSSeedData("ns1.Kobocoin.com", "testnet-seed2.Kobocoin.com", false));
        vSeeds.push_back(CDNSSeedData("ns2.Kobocoin.com", "testnet-seed3.Kobocoin.com", false));
        vSeeds.push_back(CDNSSeedData("ns2.Kobocoin.com", "testnet-seed4.Kobocoin.com", false));				

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x0000d20b7549d1457039ebc7d0c8ea5f6d6c8c2c811f898d5530bfeb70fcb06f")),
            1421090888,
            1,
            720
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes
        consensus.nPowTargetSpacing = 60;
        consensus.nLastPOWBlock = 4000000;
        consensus.nPowTargetSpacing2 = 2 * 60;
		consensus.nPowTargetSpacing2_start = 30;
        consensus.nStakeMinAge = 12 * 60 * 60;
        consensus.nModifierInterval = 10 * 60;
        consensus.nStakeSplitAge = 24 * 60 * 60;
        consensus.timeLimitChange = 0;
        consensus.nStakeCombineThreshold = 1000 * COIN;
        consensus.checkpointPubKey = "043824867726f0c11fa2c4d62c1be60cf2bbaced609e17f099ca318b56addb3b7e47f38c983580b82e3b89fee9fab7c9dada97bc66bc4bc249f18a7a7fd139005a";
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1421090888, 219702, 0x1e0fffff, 1);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c98be708f9ff86319738d4ce8778f1db7ce140d2d665cca9281eef433bd"));
        assert(genesis.hashMerkleRoot == uint256S("0x3519d54cd3dddf456888921b8e97c43ef6f6204b95683a45f28437d4c44153d3"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("48c347e8ffa4e3b7f313f2301b055f3c35fe7ed6d0f5397e069f5afb2fb764da")),
            0,
            0,
            0
        };
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 
