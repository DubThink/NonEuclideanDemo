#pragma once

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT(text), fstring))
