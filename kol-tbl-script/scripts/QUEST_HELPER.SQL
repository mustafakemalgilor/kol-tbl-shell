SELECT
IO.HelperIndex as `nIndex`,
ifnull(IE.QuestName,'no name given') AS `strQuestName`,
IO.MessageType as `bMessageType`,
IO.Level as `bLevel`,
IO.Experience as `nExp`,
IO.Class as `bClass`,
IO.Nation as `bNation`,
IO.QuestType as `bQuestType`,
IO.ZoneIndex as `bZone`,
IO.NpcSsid as `sQuestNpcId`,
IO.EventDataIndex as `sEventDataIndex`,
IO.EventStatus as `bEventStatus`,
IO.EventTriggerIndex as `nEventTriggerIndex`,
IO.EventCompleteIndex as `nEventCompleteIndex`,
IO.ExchangeIndex as `nExchangeIndex`,
IO.TalkIndex as `nEventTalkIndex`,
IO.LuaFilename as `strLuaFilename`,
IO.GuideIndex as `nQuestGuideIndex`,
IO.NpcDescIndex as `nQuestNpcDescIndex`
 from {BASE_TABLE_NAME} IO 
 LEFT OUTER JOIN {AUX_TABLE_NAME} IE ON (IE.GuideIndex = IO.GuideIndex)
 order by IO.HelperIndex asc


