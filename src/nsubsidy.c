#include <stdint.h>
#include <stdlib.h>
typedef int64_t CAmount;
static const CAmount COIN = 100000000;

// barrystyle 13062019
CAmount GetBlockSubsidy(int nHeight)
{
	CAmount nSubsidy = 25000 * COIN;

	if (nHeight < 2000)   { nSubsidy = 1000 * COIN; return nSubsidy; }
	if (nHeight < 15000)  { nSubsidy /= 30000; nSubsidy *= nHeight; return nSubsidy; }
	if (nHeight < 30000)  { nSubsidy /= 30000; nSubsidy *= (nHeight+1); return nSubsidy; }
	if (nHeight < 50000)  { nSubsidy *= 30000; nSubsidy /= nHeight;	return nSubsidy; }
	if (nHeight < 100000) { nSubsidy *= 50000; nSubsidy /= (nHeight*1.5); return nSubsidy; }

        CAmount nRapidDecay = 5000 - (nHeight - 100000);
	return nRapidDecay < 1000 ? 1000 * COIN : nRapidDecay * COIN;
}

int main()
{
        CAmount MarketCap = 0;
	for (int nHeight=0; nHeight<650000; nHeight++) {
            MarketCap += GetBlockSubsidy(nHeight);
            printf("nHeight %06d - nSubsidy %llu - MarketCap %llu\n", nHeight, GetBlockSubsidy(nHeight) / COIN, MarketCap / COIN);
        }
	return(0);
}
