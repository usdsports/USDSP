// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2020 The USD Sports developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	CMutableTransaction txNew;
	txNew.nVersion = 1;
	txNew.vin.resize(1);
	txNew.vout.resize(1);
	txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
	txNew.vout[0].nValue = genesisReward;
	txNew.vout[0].scriptPubKey = genesisOutputScript;

	CBlock genesis;
	genesis.vtx.push_back(txNew);
	genesis.hashPrevBlock.SetNull();
	genesis.nVersion = nVersion;
	genesis.nTime = nTime;
	genesis.nBits = nBits;
	genesis.nNonce = nNonce;
	genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
	return genesis;
}

/**
* Build the genesis block. Note that the output of the genesis coinbase cannot
* be spent as it did not originally exist in the database.
*
* CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
*   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
*     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
*     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
*   vMerkleTree: e0028e
*/
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	const char* pszTimestamp = "Large Bitcoin Options Positions May Boost Price Volatility This Week";
	const CScript genesisOutputScript = CScript() << ParseHex("04f5b8143f86ad8ac63791fbbdb8f0b91a6da88c8c693a95f6c2a16c063ea796a7960b8025a904767bc671d5cfe706a2dd2e13b86182e1064a0eea7bf863636363") << OP_CHECKSIG;
	return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
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
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
(0, uint256("0x00000fd1ef1036dc72bda4dcbf41f720be6634198c55447b0271d6c34f2de6c1"))
(198, uint256("0x00000007a012dbab764b7fa8ff04f4a46c4c6b9b8ceea30551df5a39cbc65166"))
(406, uint256("0x60ae9d07f62e2bb3f7d86374138469bc0fd20333618bba6dcc1e24621404a015"))
(999, uint256("0x99282d83978f908b78ab28c60fd5f3d7a4d4b99024dd5da9bad6bc69734e66de"))
(1340, uint256("0x69c5ea20c479f9186a70ee3e29dfe1043dc2c0706a1b63d6b0f40d3275d1fed9"))
(5048, uint256("0xfc2a08aeb4fe611d724b7d8c68de90b8254e22b343cc6aa01751abedb9e1e875"))
(11653, uint256("0xd99ef8289810c0fb6bf5552a9bbbf8a15b41b963362781a47f8867cbee61d3e9"))
(18577, uint256("0x16f53e9ef38146a0aa6d77daf08d732f831262d5d8f3e6f13a1692d9f4a355b4"))
;

static const Checkpoints::CCheckpointData data = {
	&mapCheckpoints,
	1614049185, // * UNIX timestamp of last checkpoint block
	37222,	    // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the UpdateTip debug.log lines)
	720         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
boost::assign::map_list_of
(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
	&mapCheckpointsTestnet,
	1591225230,
	3501914,
	3000 };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
	&mapCheckpointsRegtest,
	1454124731,
	0,
	100 };

class CMainParams : public CChainParams
{
public:
	CMainParams()
	{
		networkID = CBaseChainParams::MAIN;
		strNetworkID = "main";

		genesis = CreateGenesisBlock(1611651600, 8829, 0x1e0ffff0, 1, 0);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(consensus.hashGenesisBlock == uint256S("00000fd1ef1036dc72bda4dcbf41f720be6634198c55447b0271d6c34f2de6c1"));
		assert(genesis.hashMerkleRoot == uint256S("21266d2ee5bbd2161b9ef10a92eda73588c5fb5836900362055427b1c627818d"));

		consensus.fPowAllowMinDifficultyBlocks = false;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // USDSports starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 9999999;       // approx. 1 every 30 days
		consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
		consensus.nCoinbaseMaturity = 61;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 84000000 * COIN;
		consensus.nPoolMaxTransactions = 3;
		consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
		consensus.nStakeMinAge = 60 * 60;
		consensus.nStakeMinDepth = 60;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 2 * 60;
		consensus.nTimeSlotLength = 15;

		// spork keys
		consensus.strSporkPubKey = "0468a484e7908f0934f66ffcdf15f519d2f258e336c3f709ae408481ef248f755149bb9957ecedbabc95d7a8c13278fde45a4c7b5ec279fa312440123e17c53caa";
		consensus.strSporkPubKeyOld = "0468a484e7908f0934f66ffcdf15f519d2f258e336c3f709ae408481ef248f755149bb9957ecedbabc95d7a8c13278fde45a4c7b5ec279fa312440123e17c53caa";
		consensus.nTime_EnforceNewSporkKey = 1599195600;    //!> Friday, 4 September 2020 5:00:00 AM GMT
		consensus.nTime_RejectOldSporkKey = 1599285600;     //!> Saturday, 5 September 2020 6:00:00 AM GMT

		// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 1;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 500;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 300;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

		consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
			uint256S("0x");
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
			uint256S("0x");
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
			uint256S("0x");

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/
		pchMessageStart[0] = 0x71;
		pchMessageStart[1] = 0x2e;
		pchMessageStart[2] = 0xac;
		pchMessageStart[3] = 0xce;
		nDefaultPort = 2621;

		// Note that of those with the service bits flag, most only support a subset of possible options
		vSeeds.push_back(CDNSSeedData("dnsseed1.usdsports.io", "dnsseed1.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("dnsseed2.usdsports.io", "dnsseed2.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("explorer1.usdsports.io", "explorer1.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("explorer2.usdsports.io", "explorer2.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed1.usdsports.io", "seed1.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed2.usdsports.io", "seed2.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed3.usdsports.io", "seed3.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed4.usdsports.io", "seed4.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed5.usdsports.io", "seed5.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed6.usdsports.io", "seed6.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed7.usdsports.io", "seed7.usdsports.io", true));
		vSeeds.push_back(CDNSSeedData("seed8.usdsports.io", "seed8.usdsports.io", true));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 68);		// U
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);
		base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);	// S
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 46);
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
		// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

		// Sapling
		bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ps";
		bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviews";
		bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
		bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-main";
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return data;
	}

};
static CMainParams mainParams;

/**
* Testnet (v3)
*/
class CTestNetParams : public CMainParams
{
public:
	CTestNetParams()
	{
		networkID = CBaseChainParams::TESTNET;
		strNetworkID = "test";

		genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		//assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // USDSports starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
		consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
		consensus.nCoinbaseMaturity = 15;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 43199500 * COIN;
		consensus.nPoolMaxTransactions = 2;
		consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
		consensus.nStakeMinAge = 60 * 60;
		consensus.nStakeMinDepth = 100;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 1 * 60;
		consensus.nTimeSlotLength = 15;

		// spork keys
		consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
		consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
		consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
		consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

															// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 201;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 51197;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 851019;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 1214000;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 1347000;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

		consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
			uint256S("0xc54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30");
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
			uint256S("0x1822577176173752aea33d1f60607cefe9e0b1c54ebaa77eb40201a385506199");
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
			uint256S("0x30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882");

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/

		pchMessageStart[0] = 0x45;
		pchMessageStart[1] = 0x76;
		pchMessageStart[2] = 0x65;
		pchMessageStart[3] = 0xba;
		nDefaultPort = 51474;

		vFixedSeeds.clear();
		vSeeds.clear();
		// nodes with support for servicebits filtering should be at the top
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "usdsports-testnet.seed.fuzzbawls.pw", true));
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "usdsports-testnet.seed2.fuzzbawls.pw", true));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet usdsports addresses start with 'x' or 'y'
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet usdsports script addresses start with '8' or '9'
		base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
																			 // Testnet usdsports BIP32 pubkeys start with 'DRKV'
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
		// Testnet usdsports BIP32 prvkeys start with 'DRKP'
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
		// Testnet usdsports BIP44 coin type is '1' (All coin's testnet default)
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

		// Sapling
		bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ptestsapling";
		bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviewtestsapling";
		bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "bcktestsapling";
		bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-test";
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataTestnet;
	}
};
static CTestNetParams testNetParams;

/**
* Regression test
*/
class CRegTestParams : public CTestNetParams
{
public:
	CRegTestParams()
	{
		networkID = CBaseChainParams::REGTEST;
		strNetworkID = "regtest";

		genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		//assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // USDSports starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
		consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
		consensus.nCoinbaseMaturity = 100;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 43199500 * COIN;
		consensus.nPoolMaxTransactions = 2;
		consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
		consensus.nStakeMinAge = 0;
		consensus.nStakeMinDepth = 2;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 1 * 60;
		consensus.nTimeSlotLength = 15;

		/* Spork Key for RegTest:
		WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
		private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
		Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
		*/
		consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
		consensus.strSporkPubKeyOld = "";
		consensus.nTime_EnforceNewSporkKey = 0;
		consensus.nTime_RejectOldSporkKey = 0;

		// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight = 300;

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/

		pchMessageStart[0] = 0xa1;
		pchMessageStart[1] = 0xcf;
		pchMessageStart[2] = 0x7e;
		pchMessageStart[3] = 0xac;
		nDefaultPort = 51476;

		vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataRegtest;
	}

	void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
	{
		assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
		consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
	}
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
	assert(pCurrentParams);
	return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
	switch (network) {
	case CBaseChainParams::MAIN:
		return mainParams;
	case CBaseChainParams::TESTNET:
		return testNetParams;
	case CBaseChainParams::REGTEST:
		return regTestParams;
	default:
		assert(false && "Unimplemented network");
		return mainParams;
	}
}

void SelectParams(CBaseChainParams::Network network)
{
	SelectBaseParams(network);
	pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
	CBaseChainParams::Network network = NetworkIdFromCommandLine();
	if (network == CBaseChainParams::MAX_NETWORK_TYPES)
		return false;

	SelectParams(network);
	return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
	regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
