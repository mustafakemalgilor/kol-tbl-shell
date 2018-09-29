
SELECT
IO.MagicNum as 'MagicNum',
IO.KrName as 'KrName',
IO.EnName as 'EnName',
IO.Description as 'Description',
IO.BeforeAction as 'BeforeAction',
IO.TargetAction as 'TargetAction',
IO.SelfEffect1 as 'SelfEffect',
IO.FlyingEffect as 'FlyingEffect',
IO.TargetEffect as 'TargetEffect',
IO.Moral as 'Moral',
IO.SkillLevel as 'SkillLevel',
IO.Skill as 'Skill',
IO.MSP as 'Msp',
IO.HP as 'HP',
IO.ItemGroup as 'ItemGroup',
IO.UseItem as 'UseItem',
IO.CastTime as 'CastTime',
IO.RecastTime as 'RecastTime',
IO.SuccessRate as 'SuccessRate',
IO.Type1 as 'Type1',
IO.Type2 as 'Type2',
IO.Range as 'Range',
IO.Etc as 'Etc',
IO.Event as 'Event'
from {BASE_TABLE_NAME} IO order by IO.MagicNum asc


