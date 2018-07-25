SELECT DISTINCT
IO.QuestIndex as `sEventDataIndex`,
'no name given' AS `strQuestName`,
IO.Group1A as `sGroup1A`,
IO.Group1B as `sGroup1B`,
IO.Group1C as `sGroup1C`,
IO.Group1D as `sGroup1D`,
IO.Group1Qty as `sGroup1Count`,
IO.Group2A as `sGroup2A`,
IO.Group2B as `sGroup2B`,
IO.Group2C as `sGroup2C`,
IO.Group2D as `sGroup2D`,
IO.Group2Qty as `sGroup2Count`,
IO.Group3A as `sGroup3A`,
IO.Group3B as `sGroup3B`,
IO.Group3C as `sGroup3C`,
IO.Group3D as `sGroup3D`,
IO.Group3Qty as `sGroup3Count`,
IO.Group4A as `sGroup4A`,
IO.Group4B as `sGroup4B`,
IO.Group4C as `sGroup4C`,
IO.Group4D as `sGroup4D`,
IO.Group4Qty as `sGroup4Count`
from {BASE_TABLE_NAME} IO 
GROUP BY IO.QuestIndex
order by IO.QuestIndex asc



