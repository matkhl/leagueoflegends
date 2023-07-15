#pragma once

//functions
#define oGetBaseDrawPosition 0x1F5AB0
#define oWorldToScreen 0xDF2D10
#define oTryRightClick 0x884700
#define oIssueOrder 0x899380
#define oIssueMove 0x883AE0
#define oCastSpellWrapper 0x890320
#define oPrintChat 0x844850
#define oGetBoundingRadius 0x1F32A0
#define oGetAttackDelay 0x3ABB70
#define oGetAttackWindup 0x3ABA70

//variables
#define oGameTime 0x521EE00
#define oLocalPlayer 0x522B768
#define oHeroManager 0x2173340
#define oMinionManager 0x39CDCE0
#define oViewport 0x39CDCA0
#define oHudInstance 0x2173230
#define oZoomInstance 0x521B180
#define oChatClient 0x522B928
#define oChatInstance 0x39CDF10

#define oManagerList 0x8
#define oManagerListSize 0x10

#define oViewportW2S 0x270

#define oHudInstanceCamera 0x18
#define oHudInstanceInput 0x28
#define oHudInstanceSpellInfo 0x68

#define oHudInstanceInputMouseWorldPos 0x20

#define oHudInstanceCameraZoom 0x2B8

#define oZoomInstanceMaxZoom 0x28

#define oChatClientChatOpen 0xCC1

//structs
#define oObjNetId 0x10
#define oObjTeam 0x3C
#define oObjIssueOrderFloatCheck1 0x84
#define oObjIssueOrderFloatCheck2 0x88
#define oObjIssueOrderCheck 0xD4
#define oObjPosition 0x220
#define oObjVisible 0x310
#define oObjAlive 0x328
#define oObjTargetable 0xEB0
#define oObjRecallState 0xF40
#define oObjHealth 0x1068
#define oObjScale 0x1694
#define oObjArmor 0x16A4
#define oObjMagicResist 0x16AC
#define oObjAttackRange 0x16C4
#define oObjSpellBook 0x29F8
#define oObjActiveSpellCast 0x2A30
#define oObjCharData 0x3538
#define oObjName 0x35E8

#define oObjSpellBookSpellSlot 0x6D0

#define oSpellSlotLevel 0x28
#define oSpellSlotCooldown 0x30
#define oSpellSlotTotalCooldown 0x74
#define oSpellSlotSpellInput 0x128
#define oSpellSlotSpellInfo 0x130

#define oSpellInputTargetNetId 0x14
#define oSpellInputStartPos 0x18
#define oSpellInputEndPos 0x24

#define oSpellInfoSpellData 0x60

#define oSpellDataSpellName 0x80

#define oActiveSpellCastSpellInfo 0x8
#define oActiveSpellCastSpellType 0x10
#define oActiveSpellCastStartTime 0x16C

#define oObjCharDataData 0x28
#define oObjCharDataDataSize 0xC4