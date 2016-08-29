#include "obse/CommandTable.h"
#include "obse/GameCommands.h"

#if OBLIVION_VERSION == OBLIVION_VERSION_1_1

//TODO

#elif OBLIVION_VERSION == OBLIVION_VERSION_1_2

//TODO

#elif OBLIVION_VERSION == OBLIVION_VERSION_1_2_416

const _Cmd_Execute Cmd_AddItem_Execute = (_Cmd_Execute)0x00507320;
const _Cmd_Execute Cmd_RemoveItem_Execute = (_Cmd_Execute)0x00513810;
const _Cmd_Execute Cmd_AddSpell_Execute = (_Cmd_Execute)0x00514950;
const _Cmd_Execute Cmd_RemoveSpell_Execute = (_Cmd_Execute)0x00510B90;
const _Cmd_Execute Cmd_EquipItem_Execute = (_Cmd_Execute)0x005162B0;
const _Cmd_Execute Cmd_UnequipItem_Execute = (_Cmd_Execute)0x005164C0;
const _Cmd_Execute Cmd_SetStage_Execute = (_Cmd_Execute)0x00502CB0;

#else

#error unsupported version of oblivion

#endif