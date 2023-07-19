#pragma once

//functions
#define oGetBaseDrawPosition 0x1F8920
#define oWorldToScreen 0xDF0950
#define oTryRightClick 0x882A20
#define oIssueOrder 0x898580
#define oIssueMove 0x881E00
#define oCastSpellWrapper 0x88E890
#define oPrintChat 0x841720
#define oGetBoundingRadius 0x1F6110
#define oGetAttackDelay 0x3AFB90
#define oGetAttackWindup 0x3AFA90
#define oGetObjectFromNetId 0x38D860
#define oGetCollisionFlags 0xD67930

//variables
#define oGameTime 0x4213710
#define oLocalPlayer 0x421F828
#define oHeroManager 0x2171780
#define oMinionManager 0x31C45B8
#define oViewport 0x31C4578
#define oHudInstance 0x2171670
#define oZoomInstance 0x4211A90
#define oChatClient 0x4220618
#define oChatInstance 0x31C47D0
#define oGetObjectFromNetIdParam 0x2171660

#define oManagerList 0x8
#define oManagerListSize 0x10

#define oViewportW2S 0x270

#define oHudInstanceCamera 0x18
#define oHudInstanceInput 0x28
#define oHudInstanceUserData 0x60
#define oHudInstanceSpellInfo 0x68

#define oHudInstanceCameraZoom 0x2B8

#define oHudInstanceInputMouseWorldPos 0x20

#define oHudInstanceUserDataSelectedObjectNetId 0x28

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
#define oObjHealth 0x1070
#define oObjScale 0x1684
#define oObjArmor 0x1694
#define oObjMagicResist 0x169C
#define oObjAttackRange 0x16B4
#define oObjSpellBook 0x29E8
#define oObjActiveSpellCast 0x2A20
#define oObjCharData 0x3528
#define oObjName 0x35D8

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
#define oActiveSpellCastSpellId 0x124

#define oObjCharDataData 0x28
#define oObjCharDataDataSize 0xC4