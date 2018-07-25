
SELECT 
	cast(substr(CAST(IO.nID as TEXT),0,length(CAST(IO.nID as TEXT))-2) as integer) /10 as `Race`,
	substr(CAST(IO.nID as TEXT),length(CAST(IO.nID as TEXT))-2,3) as `Class`,
	cast(substr(CAST(IO.nID as TEXT),length(CAST(IO.nID as TEXT))-2,3) as integer) /100 as `Nation`,
	'empty' as 'strDescription',
	IO.bStr as `Strength`,
	IO.bSta as `Health`,
	IO.bDex as `Dexterity`,
	IO.bInt as `Intelligence`,
	IO.bCha as `MagicPower`,
	IO.bUnspent as `Unspent`
FROM
	NewChrValue AS IO   
ORDER BY `nID` ASC;

