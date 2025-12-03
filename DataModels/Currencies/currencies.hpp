#pragma once
#include <string>
#include <variant>
#include <unordered_map>

/// Currencies that use bars according to the standard -> ISO_4217 Pblshd="2025-05-12"
enum class ÑountriesCurrencies : uint8_t {
	AED, AFN, ALL, AMD, AOA, ARS, AUD, AWG, AZN, BAM, BBD, BDT, BGN,
	BHD, BIF, BMD, BND, BOB, BOV, BRL, BSD, BTN, BWP, BYN, BZD, CAD,
	CDF, CHE, CHF, CHW, CLF, CLP, CNY, COP, COU, CRC, CUP, CVE, CZK,
	DJF, DKK, DOP, DZD, EGP, ERN, ETB, EUR, FJD, FKP, GBP, GEL, GHS,
	GIP, GMD, GNF, GTQ, GYD, HKD, HNL, HTG, HUF, IDR, ILS, INR, IQD,
	IRR, ISK, JMD, JOD, JPY, KES, KGS, KHR, KMF, KPW, KRW, KWD, KYD,
	KZT, LAK, LBP, LKR, LRD, LSL, LYD, MAD, MDL, MGA, MKD, MMK, MNT,
	MOP, MRU, MUR, MVR, MWK, MXN, MXV, MYR, MZN, NAD, NGN, NIO, NOK,
	NPR, NZD, OMR, PAB, PEN, PGK, PHP, PKR, PLN, PYG, QAR, RON, RSD,
	RUB, RWF, SAR, SBD, SCR, SDG, SEK, SGD, SHP, SLE, SOS, SRD, SSP,
	STN, SVC, SYP, SZL, THB, TJS, TMT, TND, TOP, TRY, TTD, TWD, TZS,
	UAH, UGX, USD, USN, UYI, UYU, UYW, UZS, VED, VES, VND, VUV, WST,
	XAD, XAF, XAG, XAU, XBA, XBB, XBC, XBD, XCD, XCG, XDR, XOF, XPD,
	XPF, XPT, XSU, XTS, XUA, XXX, YER, ZAR, ZMW, ZWG
};

/// The main cryptocurrencies used for payments and transfers
enum class CryptoCurrency : uint8_t {
	BTC,    ///< Bitcoin - The first and most valuable cryptocurrency
	ETH,    ///< Ethereum - Smart contract platform
	USDT,   ///< Tether - USD-backed stablecoin (most popular for transfers)
	USDC,   ///< USD Coin - Regulated USD stablecoin
	BNB,    ///< Binance Coin - Binance ecosystem
	XRP,    ///< Ripple - Fast cross-border payments
	SOL,    ///< Solana - High-speed transactions
	ADA,    ///< Cardano - Proof-of-stake platform
	DOGE,   ///< Dogecoin - Popular for tips and small payments
	DOT,    ///< Polkadot - Multi-chain network
	LTC,    ///< Litecoin - Faster Bitcoin alternative
	BCH,    ///< Bitcoin Cash - Bitcoin fork for payments
	XLM,    ///< Stellar - Low-cost cross-border payments
	XMR,    ///< Monero - Privacy-focused cryptocurrency
	DAI,    ///< DAI - Decentralized USD stablecoin
	TRX,    ///< Tron - Low-cost transactions
	MATIC,  ///< Polygon - Ethereum scaling solution
	AVAX,   ///< Avalanche - Fast smart contracts
	LINK,   ///< Chainlink - Oracle network
	UNI,    ///< Uniswap - Decentralized exchange token
	ATOM,   ///< Cosmos - Inter-blockchain communication
	ETC,    ///< Ethereum Classic - Original Ethereum chain
	XTZ,    ///< Tezos - Self-amending blockchain
	EOS,    ///< EOS - Blockchain for dApps
	NEO,    ///< NEO - Smart economy platform
	VET,    ///< VeChain - Supply chain solutions
	ALGO,   ///< Algorand - Pure proof-of-stake
	ZEC,    ///< Zcash - Privacy cryptocurrency
	DASH,   ///< Dash - Digital cash
	BSV,    ///< Bitcoin SV - Bitcoin fork
	MIOTA,  ///< IOTA - IoT payments (feeless)
	HBAR,   ///< Hedera - Enterprise-grade blockchain
	CRO,    ///< Crypto.com Coin - Payments and rewards
	FTT,    ///< FTX Token - Exchange token
	KLAY,   ///< Klaytn - Korean blockchain platform
	THETA,  ///< Theta - Video delivery network
	FLOW,   ///< Flow - NFT and gaming
	GRT,    ///< The Graph - Data indexing
	SAND,   ///< The Sandbox - Gaming metaverse
	MANA,   ///< Decentraland - Virtual reality
	AXS,    ///< Axie Infinity - Play-to-earn gaming
	GALA,   ///< Gala - Gaming platform
	ENJ,    ///< Enjin - Gaming cryptocurrency
	CHZ,    ///< Chiliz - Sports fan tokens
	BAT,    ///< Basic Attention Token - Digital advertising
	COMP,   ///< Compound - DeFi lending
	AAVE,   ///< Aave - DeFi lending
	MKR,    ///< Maker - DAI stablecoin governance
	SNX,    ///< Synthetix - Synthetic assets
	YFI,    ///< Yearn.finance - Yield optimization
	SUSHI,  ///< SushiSwap - DeFi exchange
	CRV,    ///< Curve - Stablecoin trading
	UST,    ///< TerraUSD - Algorithmic stablecoin
	LUNA,   ///< Terra - Terra ecosystem
	FTM,    ///< Fantom - Fast smart contracts
	ONE,    ///< Harmony - Cross-chain finance
	CELO,   ///< Celo - Mobile-first payments
	RVN,    ///< Ravencoin - Asset transfer
	SC,     ///< Siacoin - Decentralized storage
	AR,     ///< Arweave - Permanent storage
	FIL,    ///< Filecoin - Decentralized storage
	ICP,    ///< Internet Computer - Web3 platform
	QNT,    ///< Quant - Blockchain interoperability
	NEXO,   ///< Nexo - Lending platform
	CAKE,   ///< PancakeSwap - BSC DEX
	KSM,    ///< Kusama - Polkadot canary network
	WAVES,  ///< Waves - Custom tokens
	ZIL,    ///< Zilliqa - High-throughput blockchain
	IOST,   ///< IOST - High-performance blockchain
	ONT,    ///< Ontology - Identity and data
	HOT,    ///< Holo - Distributed computing
	OMG,    ///< OMG Network - Ethereum scaling
	ZRX,    ///< 0x - Decentralized exchange protocol
	REP,    ///< Augur - Prediction markets
	KNC,    ///< Kyber Network - Liquidity protocol
	NMR,    ///< Numeraire - Hedge fund protocol
	OXT,    ///< Orchid - VPN and privacy
	REN,    ///< Ren - Cross-chain interoperability
	LRC,    ///< Loopring - ZK-rollup exchange
	CVC,    ///< Civic - Identity verification
	STORJ,  ///< Storj - Decentralized storage
	SNT,    ///< Status - Mobile Ethereum
	FUN,    ///< FunFair - Casino platform
	POWR,   ///< Power Ledger - Energy trading
	GNT,    ///< Golem - Distributed computing
	DNT,    ///< District0x - Decentralized communities
	MLN,    ///< Enzyme Finance - Asset management
	ANT,    ///< Aragon - DAO governance
	BAL,    ///< Balancer - Automated portfolio manager
	UMA,    ///< UMA - Financial contracts
	BAND,   ///< Band Protocol - Oracle network
	OCEAN,  ///< Ocean Protocol - Data exchange
	RSV,    ///< Reserve - Stablecoin protocol
	AMP,    ///< Amp - Collateral token
	RAI,    ///< RAI - Reflex index (stable asset)
	FEI,    ///< Fei Protocol - Algorithmic stablecoin
	TRIBE,  ///< Tribe - Fei Protocol governance
	FORTH,  ///< Ampleforth governance
	RAD,    ///< Radicle - Code collaboration
	API3,   ///< API3 - Decentralized APIs
	BADGER, ///< Badger DAO - Bitcoin on Ethereum
	RARI,   ///< Rarible - NFT marketplace
	NFTX,   ///< NFTX - NFT liquidity
	SOS,    ///< OpenDAO - NFT community
	GTC,    ///< Gitcoin - Open source funding
	ILV,    ///< Illuvium - Gaming and NFTs
	IMX,    ///< Immutable X - NFT scaling
	GODS,   ///< Gods Unchained - Gaming tokens
	RLY,    ///< Rally - Creator tokens
	AUDIO,  ///< Audius - Music streaming
	WOO,    ///< WOO Network - Liquidity
	PERP,   ///< Perpetual Protocol - Derivatives
	DYDX,   ///< dYdX - Derivatives trading
	RBN,    ///< Ribbon Finance - Structured products
	ORCA,   ///< Orca - Solana DEX
	RAY,    ///< Raydium - Solana AMM
	SRM,    ///< Serum - Solana DEX
	FIDA,   ///< Bonfida - Serum ecosystem
	MAPS,   ///< Maps.me - DeFi maps
	OXY,    ///< Oxygen - Brokerage protocol
	MSOL,   ///< Marinade Staked SOL - Staked Solana
	ATLAS,  ///< Star Atlas - Gaming token
	POLIS,  ///< Star Atlas DAO - Governance
	SBR,    ///< Saber - Stablecoin swaps on Solana
	PORT,   ///< Port Finance - Lending on Solana
	SLRS,   ///< Solrise Finance - Fund management
	SUNNY,  ///< Sunny Aggregator - Yield optimization
	STEP,   ///< Step Finance - Solana analytics
	COPE,   ///< Copium - Trading signals
	LIKE,   ///< Only1 - Social NFT platform
	MNGO,   ///< Mango Markets - Derivatives
	FTT2,   ///< FTX Token 2.0 - Exchange token recovery
	LUNA2,  ///< Terra Luna 2.0 - Terra reboot
	LUNC,   ///< Terra Classic - Community revival
	USDN,   ///< Neutrino USD - Waves stablecoin
	USDP,   ///< Pax Dollar - Regulated stablecoin
	BUSD,   ///< Binance USD - Binance stablecoin
	TUSD,   ///< TrueUSD - Attested stablecoin
	HUSD,   ///< HUSD - Stablecoin
	USDK,   ///< USDK - OKX stablecoin
	GUSD,   ///< Gemini Dollar - Gemini stablecoin
	SUSD,   ///< sUSD - Synthetic USD
	LUSD,   ///< Liquity USD - Decentralized stablecoin
	FRAX,   ///< Frax - Fractional-algorithmic stablecoin
	MIM,    ///< Magic Internet Money - Stablecoin
	VAI,    ///< VAI - Venus stablecoin
	CUSD,   ///< Celo Dollar - Celo stablecoin
	CEUR,   ///< Celo Euro - Celo stablecoin
	EURS,   ///< STASIS Euro - Euro stablecoin
	EURT,   ///< Tether Euro - Euro stablecoin
	XAUT,   ///< Tether Gold - Gold-backed
	PAXG,   ///< Paxos Gold - Gold-backed
	WBTC,   ///< Wrapped Bitcoin - Bitcoin on Ethereum
	RENBTC, ///< RenBTC - Bitcoin on Ethereum
	SBTC,   ///< Synthetic Bitcoin
	TBTC,   ///< tBTC - Trustless Bitcoin on Ethereum
	STETH,  ///< Lido Staked ETH - Staked Ethereum
	RETH,   ///< Rocket Pool ETH - Staked Ethereum
	AETH,   ///< Ankr Staked ETH - Staked Ethereum
	SETH,   ///< Synthetic ETH
	WETH,   ///< Wrapped ETH - Ethereum on Ethereum
	CETH,   ///< Compound ETH
	YVETH,  ///< Yearn Vault ETH
	ALETH,  ///< Alchemix ETH
	DETH,   ///< Index token
	UNIETH, ///< Unified ETH
	PETH,   ///< Pooled ETH
	GETH,   ///< Guarded ETH
	XETH,   ///< Wrapped Ethereum
	HETH,   ///< Hedera Ethereum
	POLYETH,///< Polygon ETH
	ARETH,  ///< Arbitrum ETH
	OPETH,  ///< Optimism ETH
	AVAXETH,///< Avalanche ETH
	FTMETH, ///< Fantom ETH
	ONEETH, ///< Harmony ETH
	SOLETH, ///< Solana ETH
	ADAETH, ///< Cardano ETH
	DOTETH, ///< Polkadot ETH
	XRPETH, ///< Ripple ETH
	LTCETH, ///< Litecoin ETH
	BCHETH, ///< Bitcoin Cash ETH
	XLMETH, ///< Stellar ETH
	EOSETH, ///< EOS ETH
	TRXETH, ///< Tron ETH
	XTZETH, ///< Tezos ETH
	ATOMETH,///< Cosmos ETH
	NEOETH, ///< NEO ETH
	VETETH, ///< VeChain ETH
	ICXETH, ///< ICON ETH
	ONTETH, ///< Ontology ETH
	ZILETH, ///< Zilliqa ETH
	QTUMETH,///< Qtum ETH
	BTGETH, ///< Bitcoin Gold ETH
	DASHETH,///< Dash ETH
	ZECETH, ///< Zcash ETH
	XMRETH, ///< Monero ETH
	DCRETH, ///< Decred ETH
	SCETH,  ///< Siacoin ETH
	WAVESETH,///< Waves ETH
	STRATETH,///< Stratis ETH
	ARKETH, ///< Ark ETH
	PIVXETH,///< PIVX ETH
	GRSETH, ///< Groestlcoin ETH
	NAVETH, ///< Navcoin ETH
	VTCETH, ///< Vertcoin ETH
	RVNETH, ///< Ravencoin ETH
	MNXETH, ///< Minexcoin ETH
	EMC2ETH,///< Einsteinium ETH
	GNOETH, ///< Gnosis ETH
	REPETH, ///< Augur ETH
	BATETH, ///< Basic Attention ETH
	ZRXETH, ///< 0x ETH
	KNCETH, ///< Kyber Network ETH
	SNTETH, ///< Status ETH
	FUNETH, ///< FunFair ETH
	LINKETH,///< Chainlink ETH
	MANAETH,///< Decentraland ETH
	LOOMETH,///< Loom Network ETH
	CVCETH, ///< Civic ETH
	DNTETH, ///< District0x ETH
	STORJETH,///< Storj ETH
	OMGETH, ///< OMG Network ETH
	TUSDETH,///< TrueUSD ETH
	USDCETH,///< USD Coin ETH
	USDTETH ///< Tether ETH
};

using Currencies = std::variant<ÑountriesCurrencies, CryptoCurrency>;

inline std::string countriesCurrencyToString(ÑountriesCurrencies currency) {
	static const std::unordered_map<ÑountriesCurrencies, std::string> currencyMap = {
		{ÑountriesCurrencies::AED, "AED"}, {ÑountriesCurrencies::AFN, "AFN"}, {ÑountriesCurrencies::ALL, "ALL"},
		{ÑountriesCurrencies::AMD, "AMD"}, {ÑountriesCurrencies::AOA, "AOA"}, {ÑountriesCurrencies::ARS, "ARS"},
		{ÑountriesCurrencies::AUD, "AUD"}, {ÑountriesCurrencies::AWG, "AWG"}, {ÑountriesCurrencies::AZN, "AZN"},
		{ÑountriesCurrencies::BAM, "BAM"}, {ÑountriesCurrencies::BBD, "BBD"}, {ÑountriesCurrencies::BDT, "BDT"},
		{ÑountriesCurrencies::BGN, "BGN"}, {ÑountriesCurrencies::BHD, "BHD"}, {ÑountriesCurrencies::BIF, "BIF"},
		{ÑountriesCurrencies::BMD, "BMD"}, {ÑountriesCurrencies::BND, "BND"}, {ÑountriesCurrencies::BOB, "BOB"},
		{ÑountriesCurrencies::BOV, "BOV"}, {ÑountriesCurrencies::BRL, "BRL"}, {ÑountriesCurrencies::BSD, "BSD"},
		{ÑountriesCurrencies::BTN, "BTN"}, {ÑountriesCurrencies::BWP, "BWP"}, {ÑountriesCurrencies::BYN, "BYN"},
		{ÑountriesCurrencies::BZD, "BZD"}, {ÑountriesCurrencies::CAD, "CAD"}, {ÑountriesCurrencies::CDF, "CDF"},
		{ÑountriesCurrencies::CHE, "CHE"}, {ÑountriesCurrencies::CHF, "CHF"}, {ÑountriesCurrencies::CHW, "CHW"},
		{ÑountriesCurrencies::CLF, "CLF"}, {ÑountriesCurrencies::CLP, "CLP"}, {ÑountriesCurrencies::CNY, "CNY"},
		{ÑountriesCurrencies::COP, "COP"}, {ÑountriesCurrencies::COU, "COU"}, {ÑountriesCurrencies::CRC, "CRC"},
		{ÑountriesCurrencies::CUP, "CUP"}, {ÑountriesCurrencies::CVE, "CVE"}, {ÑountriesCurrencies::CZK, "CZK"},
		{ÑountriesCurrencies::DJF, "DJF"}, {ÑountriesCurrencies::DKK, "DKK"}, {ÑountriesCurrencies::DOP, "DOP"},
		{ÑountriesCurrencies::DZD, "DZD"}, {ÑountriesCurrencies::EGP, "EGP"}, {ÑountriesCurrencies::ERN, "ERN"},
		{ÑountriesCurrencies::ETB, "ETB"}, {ÑountriesCurrencies::EUR, "EUR"}, {ÑountriesCurrencies::FJD, "FJD"},
		{ÑountriesCurrencies::FKP, "FKP"}, {ÑountriesCurrencies::GBP, "GBP"}, {ÑountriesCurrencies::GEL, "GEL"},
		{ÑountriesCurrencies::GHS, "GHS"}, {ÑountriesCurrencies::GIP, "GIP"}, {ÑountriesCurrencies::GMD, "GMD"},
		{ÑountriesCurrencies::GNF, "GNF"}, {ÑountriesCurrencies::GTQ, "GTQ"}, {ÑountriesCurrencies::GYD, "GYD"},
		{ÑountriesCurrencies::HKD, "HKD"}, {ÑountriesCurrencies::HNL, "HNL"}, {ÑountriesCurrencies::HTG, "HTG"},
		{ÑountriesCurrencies::HUF, "HUF"}, {ÑountriesCurrencies::IDR, "IDR"}, {ÑountriesCurrencies::ILS, "ILS"},
		{ÑountriesCurrencies::INR, "INR"}, {ÑountriesCurrencies::IQD, "IQD"}, {ÑountriesCurrencies::IRR, "IRR"},
		{ÑountriesCurrencies::ISK, "ISK"}, {ÑountriesCurrencies::JMD, "JMD"}, {ÑountriesCurrencies::JOD, "JOD"},
		{ÑountriesCurrencies::JPY, "JPY"}, {ÑountriesCurrencies::KES, "KES"}, {ÑountriesCurrencies::KGS, "KGS"},
		{ÑountriesCurrencies::KHR, "KHR"}, {ÑountriesCurrencies::KMF, "KMF"}, {ÑountriesCurrencies::KPW, "KPW"},
		{ÑountriesCurrencies::KRW, "KRW"}, {ÑountriesCurrencies::KWD, "KWD"}, {ÑountriesCurrencies::KYD, "KYD"},
		{ÑountriesCurrencies::KZT, "KZT"}, {ÑountriesCurrencies::LAK, "LAK"}, {ÑountriesCurrencies::LBP, "LBP"},
		{ÑountriesCurrencies::LKR, "LKR"}, {ÑountriesCurrencies::LRD, "LRD"}, {ÑountriesCurrencies::LSL, "LSL"},
		{ÑountriesCurrencies::LYD, "LYD"}, {ÑountriesCurrencies::MAD, "MAD"}, {ÑountriesCurrencies::MDL, "MDL"},
		{ÑountriesCurrencies::MGA, "MGA"}, {ÑountriesCurrencies::MKD, "MKD"}, {ÑountriesCurrencies::MMK, "MMK"},
		{ÑountriesCurrencies::MNT, "MNT"}, {ÑountriesCurrencies::MOP, "MOP"}, {ÑountriesCurrencies::MRU, "MRU"},
		{ÑountriesCurrencies::MUR, "MUR"}, {ÑountriesCurrencies::MVR, "MVR"}, {ÑountriesCurrencies::MWK, "MWK"},
		{ÑountriesCurrencies::MXN, "MXN"}, {ÑountriesCurrencies::MXV, "MXV"}, {ÑountriesCurrencies::MYR, "MYR"},
		{ÑountriesCurrencies::MZN, "MZN"}, {ÑountriesCurrencies::NAD, "NAD"}, {ÑountriesCurrencies::NGN, "NGN"},
		{ÑountriesCurrencies::NIO, "NIO"}, {ÑountriesCurrencies::NOK, "NOK"}, {ÑountriesCurrencies::NPR, "NPR"},
		{ÑountriesCurrencies::NZD, "NZD"}, {ÑountriesCurrencies::OMR, "OMR"}, {ÑountriesCurrencies::PAB, "PAB"},
		{ÑountriesCurrencies::PEN, "PEN"}, {ÑountriesCurrencies::PGK, "PGK"}, {ÑountriesCurrencies::PHP, "PHP"},
		{ÑountriesCurrencies::PKR, "PKR"}, {ÑountriesCurrencies::PLN, "PLN"}, {ÑountriesCurrencies::PYG, "PYG"},
		{ÑountriesCurrencies::QAR, "QAR"}, {ÑountriesCurrencies::RON, "RON"}, {ÑountriesCurrencies::RSD, "RSD"},
		{ÑountriesCurrencies::RUB, "RUB"}, {ÑountriesCurrencies::RWF, "RWF"}, {ÑountriesCurrencies::SAR, "SAR"},
		{ÑountriesCurrencies::SBD, "SBD"}, {ÑountriesCurrencies::SCR, "SCR"}, {ÑountriesCurrencies::SDG, "SDG"},
		{ÑountriesCurrencies::SEK, "SEK"}, {ÑountriesCurrencies::SGD, "SGD"}, {ÑountriesCurrencies::SHP, "SHP"},
		{ÑountriesCurrencies::SLE, "SLE"}, {ÑountriesCurrencies::SOS, "SOS"}, {ÑountriesCurrencies::SRD, "SRD"},
		{ÑountriesCurrencies::SSP, "SSP"}, {ÑountriesCurrencies::STN, "STN"}, {ÑountriesCurrencies::SVC, "SVC"},
		{ÑountriesCurrencies::SYP, "SYP"}, {ÑountriesCurrencies::SZL, "SZL"}, {ÑountriesCurrencies::THB, "THB"},
		{ÑountriesCurrencies::TJS, "TJS"}, {ÑountriesCurrencies::TMT, "TMT"}, {ÑountriesCurrencies::TND, "TND"},
		{ÑountriesCurrencies::TOP, "TOP"}, {ÑountriesCurrencies::TRY, "TRY"}, {ÑountriesCurrencies::TTD, "TTD"},
		{ÑountriesCurrencies::TWD, "TWD"}, {ÑountriesCurrencies::TZS, "TZS"}, {ÑountriesCurrencies::UAH, "UAH"},
		{ÑountriesCurrencies::UGX, "UGX"}, {ÑountriesCurrencies::USD, "USD"}, {ÑountriesCurrencies::USN, "USN"},
		{ÑountriesCurrencies::UYI, "UYI"}, {ÑountriesCurrencies::UYU, "UYU"}, {ÑountriesCurrencies::UYW, "UYW"},
		{ÑountriesCurrencies::UZS, "UZS"}, {ÑountriesCurrencies::VED, "VED"}, {ÑountriesCurrencies::VES, "VES"},
		{ÑountriesCurrencies::VND, "VND"}, {ÑountriesCurrencies::VUV, "VUV"}, {ÑountriesCurrencies::WST, "WST"},
		{ÑountriesCurrencies::XAD, "XAD"}, {ÑountriesCurrencies::XAF, "XAF"}, {ÑountriesCurrencies::XAG, "XAG"},
		{ÑountriesCurrencies::XAU, "XAU"}, {ÑountriesCurrencies::XBA, "XBA"}, {ÑountriesCurrencies::XBB, "XBB"},
		{ÑountriesCurrencies::XBC, "XBC"}, {ÑountriesCurrencies::XBD, "XBD"}, {ÑountriesCurrencies::XCD, "XCD"},
		{ÑountriesCurrencies::XCG, "XCG"}, {ÑountriesCurrencies::XDR, "XDR"}, {ÑountriesCurrencies::XOF, "XOF"},
		{ÑountriesCurrencies::XPD, "XPD"}, {ÑountriesCurrencies::XPF, "XPF"}, {ÑountriesCurrencies::XPT, "XPT"},
		{ÑountriesCurrencies::XSU, "XSU"}, {ÑountriesCurrencies::XTS, "XTS"}, {ÑountriesCurrencies::XUA, "XUA"},
		{ÑountriesCurrencies::XXX, "XXX"}, {ÑountriesCurrencies::YER, "YER"}, {ÑountriesCurrencies::ZAR, "ZAR"},
		{ÑountriesCurrencies::ZMW, "ZMW"}, {ÑountriesCurrencies::ZWG, "ZWG"}
	};

	auto it = currencyMap.find(currency);
	return it != currencyMap.end() ? it->second : "unknow";
}

inline std::string cryptoCurrencyToString(CryptoCurrency crypto) {
	static const std::unordered_map<CryptoCurrency, std::string> cryptoMap = {
		{CryptoCurrency::BTC, "BTC"}, {CryptoCurrency::ETH, "ETH"}, {CryptoCurrency::USDT, "USDT"},
		{CryptoCurrency::USDC, "USDC"}, {CryptoCurrency::BNB, "BNB"}, {CryptoCurrency::XRP, "XRP"},
		{CryptoCurrency::SOL, "SOL"}, {CryptoCurrency::ADA, "ADA"}, {CryptoCurrency::DOGE, "DOGE"},
		{CryptoCurrency::DOT, "DOT"}, {CryptoCurrency::LTC, "LTC"}, {CryptoCurrency::BCH, "BCH"},
		{CryptoCurrency::XLM, "XLM"}, {CryptoCurrency::XMR, "XMR"}, {CryptoCurrency::DAI, "DAI"},
		{CryptoCurrency::TRX, "TRX"}, {CryptoCurrency::MATIC, "MATIC"}, {CryptoCurrency::AVAX, "AVAX"},
		{CryptoCurrency::LINK, "LINK"}, {CryptoCurrency::UNI, "UNI"}, {CryptoCurrency::ATOM, "ATOM"},
		{CryptoCurrency::ETC, "ETC"}, {CryptoCurrency::XTZ, "XTZ"}, {CryptoCurrency::EOS, "EOS"},
		{CryptoCurrency::NEO, "NEO"}, {CryptoCurrency::VET, "VET"}, {CryptoCurrency::ALGO, "ALGO"},
		{CryptoCurrency::ZEC, "ZEC"}, {CryptoCurrency::DASH, "DASH"}, {CryptoCurrency::BSV, "BSV"},
		{CryptoCurrency::MIOTA, "MIOTA"}, {CryptoCurrency::HBAR, "HBAR"}, {CryptoCurrency::CRO, "CRO"},
		{CryptoCurrency::FTT, "FTT"}, {CryptoCurrency::KLAY, "KLAY"}, {CryptoCurrency::THETA, "THETA"},
		{CryptoCurrency::FLOW, "FLOW"}, {CryptoCurrency::GRT, "GRT"},
		{CryptoCurrency::SAND, "SAND"}, {CryptoCurrency::MANA, "MANA"}, {CryptoCurrency::AXS, "AXS"},
		{CryptoCurrency::GALA, "GALA"}, {CryptoCurrency::ENJ, "ENJ"}, {CryptoCurrency::CHZ, "CHZ"},
		{CryptoCurrency::BAT, "BAT"}, {CryptoCurrency::COMP, "COMP"}, {CryptoCurrency::AAVE, "AAVE"},
		{CryptoCurrency::MKR, "MKR"}, {CryptoCurrency::SNX, "SNX"}, {CryptoCurrency::YFI, "YFI"},
		{CryptoCurrency::SUSHI, "SUSHI"}, {CryptoCurrency::CRV, "CRV"}, {CryptoCurrency::UST, "UST"},
		{CryptoCurrency::LUNA, "LUNA"}, {CryptoCurrency::FTM, "FTM"}, {CryptoCurrency::ONE, "ONE"},
		{CryptoCurrency::CELO, "CELO"}, {CryptoCurrency::RVN, "RVN"}, {CryptoCurrency::SC, "SC"},
		{CryptoCurrency::AR, "AR"}, {CryptoCurrency::FIL, "FIL"}, {CryptoCurrency::ICP, "ICP"},
		{CryptoCurrency::QNT, "QNT"}, {CryptoCurrency::NEXO, "NEXO"}, {CryptoCurrency::CAKE, "CAKE"},
		{CryptoCurrency::KSM, "KSM"}, {CryptoCurrency::WAVES, "WAVES"}, {CryptoCurrency::ZIL, "ZIL"},
		{CryptoCurrency::IOST, "IOST"}, {CryptoCurrency::ONT, "ONT"}, {CryptoCurrency::HOT, "HOT"},
		{CryptoCurrency::OMG, "OMG"}, {CryptoCurrency::ZRX, "ZRX"}, {CryptoCurrency::REP, "REP"},
		{CryptoCurrency::KNC, "KNC"}, {CryptoCurrency::NMR, "NMR"}, {CryptoCurrency::OXT, "OXT"},
		{CryptoCurrency::REN, "REN"}, {CryptoCurrency::LRC, "LRC"}, {CryptoCurrency::CVC, "CVC"},
		{CryptoCurrency::STORJ, "STORJ"}, {CryptoCurrency::SNT, "SNT"}, {CryptoCurrency::FUN, "FUN"},
		{CryptoCurrency::POWR, "POWR"}, {CryptoCurrency::GNT, "GNT"}, {CryptoCurrency::DNT, "DNT"},
		{CryptoCurrency::MLN, "MLN"}, {CryptoCurrency::ANT, "ANT"}, {CryptoCurrency::BAL, "BAL"},
		{CryptoCurrency::UMA, "UMA"}, {CryptoCurrency::BAND, "BAND"}, {CryptoCurrency::OCEAN, "OCEAN"},
		{CryptoCurrency::RSV, "RSV"}, {CryptoCurrency::AMP, "AMP"}, {CryptoCurrency::RAI, "RAI"},
		{CryptoCurrency::FEI, "FEI"}, {CryptoCurrency::TRIBE, "TRIBE"}, {CryptoCurrency::FORTH, "FORTH"},
		{CryptoCurrency::RAD, "RAD"}, {CryptoCurrency::API3, "API3"}, {CryptoCurrency::BADGER, "BADGER"},
		{CryptoCurrency::RARI, "RARI"}, {CryptoCurrency::NFTX, "NFTX"}, {CryptoCurrency::SOS, "SOS"},
		{CryptoCurrency::GTC, "GTC"}, {CryptoCurrency::ILV, "ILV"}, {CryptoCurrency::IMX, "IMX"},
		{CryptoCurrency::GODS, "GODS"}, {CryptoCurrency::RLY, "RLY"}, {CryptoCurrency::AUDIO, "AUDIO"},
		{CryptoCurrency::WOO, "WOO"}, {CryptoCurrency::PERP, "PERP"}, {CryptoCurrency::DYDX, "DYDX"},
		{CryptoCurrency::RBN, "RBN"}, {CryptoCurrency::ORCA, "ORCA"}, {CryptoCurrency::RAY, "RAY"},
		{CryptoCurrency::SRM, "SRM"}, {CryptoCurrency::FIDA, "FIDA"}, {CryptoCurrency::MAPS, "MAPS"},
		{CryptoCurrency::OXY, "OXY"}, {CryptoCurrency::MSOL, "MSOL"}, {CryptoCurrency::ATLAS, "ATLAS"},
		{CryptoCurrency::POLIS, "POLIS"}, {CryptoCurrency::SBR, "SBR"}, {CryptoCurrency::PORT, "PORT"},
		{CryptoCurrency::SLRS, "SLRS"}, {CryptoCurrency::SUNNY, "SUNNY"}, {CryptoCurrency::STEP, "STEP"},
		{CryptoCurrency::COPE, "COPE"}, {CryptoCurrency::LIKE, "LIKE"}, {CryptoCurrency::MNGO, "MNGO"},
		{CryptoCurrency::FTT2, "FTT2"}, {CryptoCurrency::LUNA2, "LUNA2"}, {CryptoCurrency::LUNC, "LUNC"},
		{CryptoCurrency::USDN, "USDN"}, {CryptoCurrency::USDP, "USDP"}, {CryptoCurrency::BUSD, "BUSD"},
		{CryptoCurrency::TUSD, "TUSD"}, {CryptoCurrency::HUSD, "HUSD"}, {CryptoCurrency::USDK, "USDK"},
		{CryptoCurrency::GUSD, "GUSD"}, {CryptoCurrency::SUSD, "SUSD"}, {CryptoCurrency::LUSD, "LUSD"},
		{CryptoCurrency::FRAX, "FRAX"}, {CryptoCurrency::MIM, "MIM"}, {CryptoCurrency::VAI, "VAI"},
		{CryptoCurrency::CUSD, "CUSD"}, {CryptoCurrency::CEUR, "CEUR"}, {CryptoCurrency::EURS, "EURS"},
		{CryptoCurrency::EURT, "EURT"}, {CryptoCurrency::XAUT, "XAUT"}, {CryptoCurrency::PAXG, "PAXG"},
		{CryptoCurrency::WBTC, "WBTC"}, {CryptoCurrency::RENBTC, "RENBTC"}, {CryptoCurrency::SBTC, "SBTC"},
		{CryptoCurrency::TBTC, "TBTC"}, {CryptoCurrency::STETH, "STETH"}, {CryptoCurrency::RETH, "RETH"},
		{CryptoCurrency::AETH, "AETH"}, {CryptoCurrency::SETH, "SETH"}, {CryptoCurrency::WETH, "WETH"},
		{CryptoCurrency::CETH, "CETH"}, {CryptoCurrency::YVETH, "YVETH"}, {CryptoCurrency::ALETH, "ALETH"},
		{CryptoCurrency::DETH, "DETH"}, {CryptoCurrency::UNIETH, "UNIETH"}, {CryptoCurrency::PETH, "PETH"},
		{CryptoCurrency::GETH, "GETH"}, {CryptoCurrency::XETH, "XETH"}, {CryptoCurrency::HETH, "HETH"},
		{CryptoCurrency::POLYETH, "POLYETH"}, {CryptoCurrency::ARETH, "ARETH"}, {CryptoCurrency::OPETH, "OPETH"},
		{CryptoCurrency::AVAXETH, "AVAXETH"}, {CryptoCurrency::FTMETH, "FTMETH"}, {CryptoCurrency::ONEETH, "ONEETH"},
		{CryptoCurrency::SOLETH, "SOLETH"}, {CryptoCurrency::ADAETH, "ADAETH"}, {CryptoCurrency::DOTETH, "DOTETH"},
		{CryptoCurrency::XRPETH, "XRPETH"}, {CryptoCurrency::LTCETH, "LTCETH"}, {CryptoCurrency::BCHETH, "BCHETH"},
		{CryptoCurrency::XLMETH, "XLMETH"}, {CryptoCurrency::EOSETH, "EOSETH"}, {CryptoCurrency::TRXETH, "TRXETH"},
		{CryptoCurrency::XTZETH, "XTZETH"}, {CryptoCurrency::ATOMETH, "ATOMETH"}, {CryptoCurrency::NEOETH, "NEOETH"},
		{CryptoCurrency::VETETH, "VETETH"}, {CryptoCurrency::ICXETH, "ICXETH"}, {CryptoCurrency::ONTETH, "ONTETH"},
		{CryptoCurrency::ZILETH, "ZILETH"}, {CryptoCurrency::QTUMETH, "QTUMETH"}, {CryptoCurrency::BTGETH, "BTGETH"},
		{CryptoCurrency::DASHETH, "DASHETH"}, {CryptoCurrency::ZECETH, "ZECETH"}, {CryptoCurrency::XMRETH, "XMRETH"},
		{CryptoCurrency::DCRETH, "DCRETH"}, {CryptoCurrency::SCETH, "SCETH"}, {CryptoCurrency::WAVESETH, "WAVESETH"},
		{CryptoCurrency::STRATETH, "STRATETH"}, {CryptoCurrency::ARKETH, "ARKETH"}, {CryptoCurrency::PIVXETH, "PIVXETH"},
		{CryptoCurrency::GRSETH, "GRSETH"}, {CryptoCurrency::NAVETH, "NAVETH"}, {CryptoCurrency::VTCETH, "VTCETH"},
		{CryptoCurrency::RVNETH, "RVNETH"}, {CryptoCurrency::MNXETH, "MNXETH"}, {CryptoCurrency::EMC2ETH, "EMC2ETH"},
		{CryptoCurrency::GNOETH, "GNOETH"}, {CryptoCurrency::REPETH, "REPETH"}, {CryptoCurrency::BATETH, "BATETH"},
		{CryptoCurrency::ZRXETH, "ZRXETH"}, {CryptoCurrency::KNCETH, "KNCETH"}, {CryptoCurrency::SNTETH, "SNTETH"},
		{CryptoCurrency::FUNETH, "FUNETH"}, {CryptoCurrency::LINKETH, "LINKETH"}, {CryptoCurrency::MANAETH, "MANAETH"},
		{CryptoCurrency::LOOMETH, "LOOMETH"}, {CryptoCurrency::CVCETH, "CVCETH"}, {CryptoCurrency::DNTETH, "DNTETH"},
		{CryptoCurrency::STORJETH, "STORJETH"}, {CryptoCurrency::OMGETH, "OMGETH"}, {CryptoCurrency::TUSDETH, "TUSDETH"},
		{CryptoCurrency::USDCETH, "USDCETH"}, {CryptoCurrency::USDTETH, "USDTETH"}
	};

	auto it = cryptoMap.find(crypto);
	return it != cryptoMap.end() ? it->second : "unknow";
}

inline std::string currencyToString(const Currencies& currencies) {
	if (std::holds_alternative<ÑountriesCurrencies>(currencies)) {
		return countriesCurrencyToString(std::get<ÑountriesCurrencies>(currencies));
	}
	else if (std::holds_alternative<CryptoCurrency>(currencies)) {
		return cryptoCurrencyToString(std::get<CryptoCurrency>(currencies));
	}
	return std::string();
}