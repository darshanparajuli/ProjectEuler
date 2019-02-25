#ifndef PE_PROB22_H
#define PE_PROB22_H

/*
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/

struct ParsedNames
{
    String *names;
    u32 count;
};

internal ParsedNames parseNames(MemoryArena *arena, String *fileContents)
{
    u32 arrayCount = 1;  // Start at 1 to accomodate for the last string that doesn't end with a comma.
    for (u32 i = 0; i < fileContents->length; ++i)
    {
        if (fileContents->buffer[i] == ',')
        {
            arrayCount += 1;
        }
    }

    String *names = PushArray(arena, String, arrayCount);
    u32 nextIndex = 0;

    s32 start = -1;
    u32 length = 0;

    for (u32 i = 0; i < fileContents->length && nextIndex < arrayCount; ++i)
    {
        char c = fileContents->buffer[i];
        switch (c)
        {
            case '"':
            {
                if (start == -1)
                {
                    start = i + 1;
                }
                else
                {
                    String *s = names + nextIndex++;
                    *s = createString(arena, length);

                    stringCopy(fileContents, start, s, 0, length);

                    length = 0;
                    start = -1;
                }
            }
            break;
            default:
            {
                if (start >= 0)
                {
                    ++length;
                }
            }
            break;
        }
    }

    return ParsedNames{names, arrayCount};
}

void merge(MemoryArena *memoryArena, ParsedNames parsedNames, s32 low, s32 mid, s32 high)
{
    TemporaryMemory temporaryMemory = BeginTemporaryMemory(memoryArena);

    u32 count = high - low + 1;
    String *sortedArray = PushArray(temporaryMemory, String, count);
    u32 nextIndex = 0;

    u32 firstHalfFrom = low;
    u32 firstHalfTo = mid;

    u32 secondHalfFrom = mid + 1;
    u32 secondHalfTo = high;

    while (firstHalfFrom <= firstHalfTo && secondHalfFrom <= secondHalfTo)
    {
        String *a = &parsedNames.names[firstHalfFrom];
        String *b = &parsedNames.names[secondHalfFrom];

        if (stringCompare(a, b) <= 0)
        {
            sortedArray[nextIndex++] = *a;
            ++firstHalfFrom;
        }
        else
        {
            sortedArray[nextIndex++] = *b;
            ++secondHalfFrom;
        }
    }

    while (firstHalfFrom <= firstHalfTo)
    {
        sortedArray[nextIndex++] = parsedNames.names[firstHalfFrom];
        ++firstHalfFrom;
    }

    while (secondHalfFrom <= secondHalfTo)
    {
        sortedArray[nextIndex++] = parsedNames.names[secondHalfFrom];
        ++secondHalfFrom;
    }

    for (u32 i = 0; i < count; ++i)
    {
        parsedNames.names[low + i] = sortedArray[i];
    }

    EndTemporaryMemory(temporaryMemory);
}

void mergeSort(MemoryArena *memoryArena, ParsedNames parsedNames, s32 low, s32 high)
{
    if (high - low <= 0)
    {
        return;
    }

    s32 mid = (low + high) / 2;
    mergeSort(memoryArena, parsedNames, low, mid);
    mergeSort(memoryArena, parsedNames, mid + 1, high);

    merge(memoryArena, parsedNames, low, mid, high);
}

SolveProblemFunc(22)
{
    String fileContents = readEntireFile(memoryArena, "data/prob22/names.txt");
    ParsedNames parsedNamesResult = parseNames(memoryArena, &fileContents);

    mergeSort(memoryArena, parsedNamesResult, 0, parsedNamesResult.count - 1);

    u32 result = 0;
    for (u32 i = 0; i < parsedNamesResult.count; ++i)
    {
        String *name = parsedNamesResult.names + i;

        u32 charSum = 0;
        for (u32 i = 0; i < name->length; ++i)
        {
            charSum += (u32)(name->buffer[i] - 'A') + 1;
        }

        result += charSum * (i + 1);
    }

    WriteSolution("%llu", result);
}

#endif
