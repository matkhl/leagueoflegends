#pragma once

//functions
#define oGetBaseDrawPosition 0x1F8920 //
#define oWorldToScreen 0xDF0B70 //
#define oTryRightClick 0x882B20 //
#define oIssueOrder 0x898680 //
#define oIssueMove 0x881F00 //
#define oCastSpellWrapper 0x88E990 //
#define oPrintChat 0x841820 //
#define oGetBoundingRadius 0x1F6110 //
#define oGetAttackDelay 0x3AFB90 //
#define oGetAttackWindup 0x3AFA90 //
#define oGetObjectFromNetId 0x38D860 //
#define oGetCollisionFlags 0xD67B50 //
#define oCharacterDataStackUpdate 0x183710 //

//variables
#define oGameTime 0x4213790 //
#define oLocalPlayer 0x421F8A8 //
#define oHeroManager 0x2171800 //
#define oMinionManager 0x31C4638 //
#define oViewport 0x31C45F8 //
#define oHudInstance 0x21716F0 //
#define oZoomInstance 0x4211B10 //
#define oChatClient 0x4220698 //
#define oChatInstance 0x31C4850 //
#define oGetObjectFromNetIdParam 0x21716E0 //

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
#define oObjMana 0x340
#define oObjTargetable 0xEB0
#define oObjRecallState 0xF40
#define oObjHealth 0x1058
#define oObjMaxHealth 0x1070
#define oObjActionState 0x13C0
#define oObjBonusAttackDamage 0x15D8
#define oObjAbilityPower 0x15E8
#define oObjBaseAttackDamage 0x1670
#define oObjScale 0x1684
#define oObjArmor 0x1694
#define oObjMagicResist 0x169C
#define oObjMovementSpeed 0x16AC
#define oObjAttackRange 0x16B4
#define oObjBuffManager 0x27C8
#define oObjSpellBook 0x29E8
#define oObjActiveSpellCast 0x2A20
#define oObjCharData 0x3528
#define oObjName 0x35D8
#define oObjCharacterDataStack 0x35C0
#define oObjAiManager 0x36F0

#define oObjBuffManagerEntriesEnd 0x10

#define oBuffEntryBuff 0x10

#define oBuffType 0x8
#define oBuffNamePtr 0x10
#define oBuffStartTime 0x18
#define oBuffEndTime 0x1C
#define oBuffStacksAlt 0x38
#define oBuffStacks 0x8C

#define oBuffNamePtrName 0x8

#define oObjSpellBookSpellSlot 0x6D0

#define oSpellSlotLevel 0x28
#define oSpellSlotCooldown 0x30
#define oSpellSlotStacks 0x5C
#define oSpellSlotTotalCooldown 0x74
#define oSpellSlotSpellInput 0x128
#define oSpellSlotSpellInfo 0x130

#define oSpellInputTargetNetId 0x14
#define oSpellInputStartPos 0x18
#define oSpellInputEndPos 0x24

#define oSpellInfoSpellData 0x60

#define oSpellDataSpellName 0x80
#define oSpellDataManaCost 0x5F4

#define oActiveSpellCastSpellInfo 0x8
#define oActiveSpellCastSpellType 0x10
#define oActiveSpellCastSpellId 0x124

#define oObjCharDataData 0x28

#define oObjCharDataDataSize 0xC4
#define oObjCharDataDataObjType 0x768

#define oObjCharDataDataObjTypeDetailed 0x20

#define oObjAiManagerManager 0x10

#define oObjAiManagerManagerTargetPosition 0x14
#define oObjAiManagerManagerIsMoving 0x2BC
#define oObjAiManagerManagerCurrentSegment 0x2C0
#define oObjAiManagerManagerPathStart 0x2D0
#define oObjAiManagerManagerPathEnd 0x2DC
#define oObjAiManagerManagerSegments 0x2E8
#define oObjAiManagerManagerSegmentsCount 0x2F0
#define oObjAiManagerManagerDashSpeed 0x300
#define oObjAiManagerManagerIsDashing 0x324
#define oObjAiManagerManagerPosition 0x414