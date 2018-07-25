/* Unique extension generation */

SELECT DISTINCT
	IO.BaseNum + IE.ExtensionID AS `Num`,
	IO.Name AS `strName`,
	IE.Header AS `strExtensionName`,
	IO.Description AS `strDescription`,
	IE.Description AS `strExtensionDescription`,
	IO.ExtensionID AS `Extension`,
	IO.`Unique` AS `isUnique`,
	CASE IE.IconID
		WHEN 0 THEN IO.IconID
		ELSE IE.IconID
	END AS `IconID`,
	IO.Kind AS `Kind`,
	IO.Slot AS `Slot`,
	IO.Race AS `Race`,
	IO.`Class` AS `Class`,
	(IO.Attack + IE.Damage) AS `Damage`,
	IE.AtkInterval AS `Delay`,
	IO.Range AS `Range`,
	IO.Weight AS `Weight`,
	(IO.Durability + IE.Durability) AS `Duration`,
	(IO.BuyPrice * IE.PriceMultiplier) AS `BuyPrice`,
	(IO.SellPrice * IE.PriceMultiplier) AS `SellPrice`,
	(IO.Defense + IE.Defense) AS `Ac`,
	IO.Countable AS `Countable`,
	CASE IE.EffectID1
		WHEN 0 THEN IO.EffectID1
		ELSE IE.EffectID1
	END AS `Effect1`,
	CASE IE.EffectID2
		WHEN 0 THEN IO.EffectID2
		ELSE IE.EffectID2
	END AS `Effect2`,
	(IE.ReqLevel + IO.ReqMinLevel) AS `ReqLevel`,
	IO.ReqMaxLevel AS `ReqLevelMax`,
	IE.ReqRank AS `ReqRank`,
	IE.ReqTitle AS `ReqTitle`,
	CASE IO.ReqStatStr
		WHEN 0 THEN IO.ReqStatStr
		ELSE IO.ReqStatStr + IE.ReqStatStr
	END AS 'ReqStr',
	CASE IO.ReqStatSta
		WHEN 0 THEN IO.ReqStatSta
		ELSE IO.ReqStatSta + IE.ReqStatSta
	END AS 'ReqSta',
	CASE IO.ReqStatDex
		WHEN 0 THEN IO.ReqStatDex
		ELSE IO.ReqStatDex + IE.ReqStatDex
	END AS 'ReqDex',
	CASE IO.ReqStatInt
		WHEN 0 THEN IO.ReqStatInt
		ELSE IO.ReqStatInt + IE.ReqStatInt
	END AS 'ReqIntel',
	CASE IO.ReqStatMp
		WHEN 0 THEN IO.ReqStatMp
		ELSE IO.ReqStatMp + IE.ReqStatMp
	END AS 'ReqCha',
	IO.SellingGroup AS `SellingGroup`,
	IE.ItemType AS `ItemType`,
	IE.HitRate AS `HitRate`,
	IE.EvasionRate AS `EvasionRate`,
	IE.DaggerDefense AS `DaggerAc`,
	IE.SwordDefense AS `SwordAc`,
	IE.ClubDefense AS `MaceAc`,
	IE.AxeDefense AS `AxeAc`,
	IE.SpearDefense AS `SpearAc`,
	IE.ArrowDefense AS `BowAc`,
	IE.JamadarDefense AS `JamadarAc`,
	IE.FireDamage AS `FireDamage`,
	IE.IceDamage AS `IceDamage`,
	IE.LightningDamage AS `LightningDamage`,
	IE.PoisonDamage AS `PoisonDamage`,
	IE.HpRecovery AS `HPDrain`,
	IE.MpDamage AS `MPDamage`,
	IE.MpRecovery AS `MPDrain`,
	IE.RepelPhysical AS `MirrorDamage`,
	IE.SoulBind AS `Droprate`,
	IE.StatStrBonus AS `StrB`,
	IE.StatStaBonus AS `StaB`,
	IE.StatDexBonus AS `DexB`,
	IE.StatIntBonus AS `IntelB`,
	IE.StatMpBonus AS `ChaB`,
	IE.HealthBonus AS `MaxHpB`,
	IE.ManaBonus AS `MaxMpB`,
	IE.ResistFire AS `FireR`,
	IE.ResistIce AS `ColdR`,
	IE.ResistLightning AS `LightningR`,
	IE.ResistMagic AS `MagicR`,
	IE.ResistPoison AS `PoisonR`,
	IE.ResistCurse AS `CurseR`,
	IE.SkillOption AS `SkillOption`,
	IE.UnboundCount AS `UnboundCount`
FROM
	{BASE_TABLE_NAME} AS IO   
INNER JOIN
	{EXTENSION_TABLE_NAME} AS IE  
ON 
	(IE.BaseItemID = IO.BaseNum)
WHERE 
	IE.BaseItemID <> 0 AND
	IO.ExtensionID = {EXTENSION_TABLE_IDX}  AND
	IO.BaseNum <= 999999999 AND
	IE.ExtensionID <= 999
ORDER BY `Num` ASC;

