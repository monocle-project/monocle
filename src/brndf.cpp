#include "brndf.h"

uint32_t BRNDF(const CBlockIndex* pindexLast, 
                          uint32_t TargetBlocksSpacingSeconds, 
                          uint32_t PastBlocksMin, 
                          uint32_t PastBlocksMax)
{
 
    const CBlockIndex *BlockLastSolved = pindexLast;
    const CBlockIndex *BlockReading    = pindexLast;

    typedef Fixed<32, 32> fixed;

    uint32_t     nPastBlocks               = 0;
    int32_t      nActualSeconds            = 0;
    int32_t      nTargetSeconds    	       = 0;
    fixed        nBlockTimeRatio	       = 1;
    CBigNum      bnPastTargetAverage;
    CBigNum      bnPastTargetAveragePrev;


    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || 
        (uint64)BlockLastSolved->nHeight < PastBlocksMin) 
    { 
        return pindexLast->nBits; 
    }
        

    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) 
	{
        if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
        nPastBlocks++;

        if (i == 1) 
        {
            bnPastTargetAverage.SetCompact(BlockReading->nBits); 
        }
        else
        {
            CBigNum lastDiff = CBigNum().SetCompact(BlockReading->nBits);
            bnPastTargetAverage = ((lastDiff - bnPastTargetAveragePrev) / i) + bnPastTargetAveragePrev;
        }
        bnPastTargetAveragePrev = bnPastTargetAverage;

        nActualSeconds = BlockLastSolved->GetBlockTime() - BlockReading->GetBlockTime();
        nTargetSeconds = TargetBlocksSpacingSeconds * nPastBlocks;
        nBlockTimeRatio = 1;
        
        if (nActualSeconds < 1)
            nActualSeconds = 1; 

        if (nActualSeconds != 0 && nTargetSeconds != 0)
        	nBlockTimeRatio= double(nTargetSeconds) / nActualSeconds;


        if (nPastBlocks >= PastBlocksMin)
        {
            if ((nBlockTimeRatio <= SlowBlocksLimit[nPastBlocks-1]) ||
                (nBlockTimeRatio >= FastBlocksLimit[nPastBlocks-1]))
            {
                assert(BlockReading);
                break;
            }
        }


        if (BlockReading->pprev == NULL)
        {
            assert(BlockReading); 
            break;
        }
        BlockReading = BlockReading->pprev;
   }

    // Limit range of bnPastTargetAverage to a halving or doubling from most recent block target
    CBigNum lastDiff = CBigNum().SetCompact(BlockLastSolved->nBits);
    if (bnPastTargetAverage < lastDiff / 2)
        bnPastTargetAverage = lastDiff / 2;
    if (bnPastTargetAverage > lastDiff * 2)
        bnPastTargetAverage = lastDiff * 2;

    CBigNum bnNew(bnPastTargetAverage);

    if (nActualSeconds != 0 && nTargetSeconds != 0)
    {
       	// Maximal difficulty decrease of /3 from constrained past average
    	if (nActualSeconds > 3 * nTargetSeconds)
            nActualSeconds = 3 * nTargetSeconds; 

        // Maximal difficulty increase of x3 from constrained past average   	
    	if (nActualSeconds < nTargetSeconds / 3)
            nActualSeconds = nTargetSeconds / 3;

    	bnNew *= nActualSeconds;
        bnNew /= nTargetSeconds;
    }


    if (bnNew > bnProofOfWorkLimit)
        bnNew = bnProofOfWorkLimit;

    // debug print
    if(fDebug)
    {
        printf("Difficulty Retarget - Boris's Ridiculously Named Difficulty Function\n");
        printf("nHeight = %i\n", pindexLast->nHeight);
        printf("nPastBlocks = %u\n", nPastBlocks);
        printf("nBlockTimeRatio Target/Actual = %.4f\n", nBlockTimeRatio.to_float());
        printf("Mean blocktime = %.1fs\n", TargetBlocksSpacingSeconds / nBlockTimeRatio.to_float());
        printf("SlowBlocksLimit = %.4f\n", SlowBlocksLimit[nPastBlocks-1]);
        printf("FastBlocksLimit = %.4f\n", FastBlocksLimit[nPastBlocks-1]);
        printf("Before: %08x %.8f\n", BlockLastSolved->nBits, GetDifficultyHelper(BlockLastSolved->nBits));
        printf("After: %08x %.8f\n", bnNew.GetCompact(), GetDifficultyHelper(bnNew.GetCompact()));
        printf("Ratio After/Before: %.8f\n", GetDifficultyHelper(bnNew.GetCompact()) / GetDifficultyHelper(BlockLastSolved->nBits));
    }
    return bnNew.GetCompact();
}