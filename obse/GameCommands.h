#pragma once

typedef bool (* _Cmd_Execute)(COMMAND_ARGS);
extern const _Cmd_Execute Cmd_AddItem_Execute;
extern const _Cmd_Execute Cmd_RemoveItem_Execute;
extern const _Cmd_Execute Cmd_AddSpell_Execute;
extern const _Cmd_Execute Cmd_RemoveSpell_Execute;
extern const _Cmd_Execute Cmd_EquipItem_Execute;
extern const _Cmd_Execute Cmd_UnequipItem_Execute;
extern const _Cmd_Execute Cmd_SetStage_Execute;
