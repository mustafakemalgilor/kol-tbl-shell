
SELECT
IO.WarpIndex % 100 /10 as 'sListID',
IO.WarpIndex % 10 as 'sListItemID',
IO.WarpIndex / 100 as 'sZoneID',
IO.Name as 'strTitle',
IO.Description as 'strDescription',
CASE IO.WarpIndex / 100
	WHEN 1 THEN 1
	WHEN 2 THEN 2
	WHEN 11 THEN 1
	WHEN 12 THEN 2
	
	ELSE 3
END AS `byNation`,
0 as 'iPrice',
0 as 'fPosX',
0 as 'fPosZ',
0 as 'fPosY',
0 as 'fRadius'


 from {BASE_TABLE_NAME} IO order by IO.WarpIndex asc


