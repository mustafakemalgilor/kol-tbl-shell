
SELECT
IO.MagicNum as 'iNum',
'empty' as 'Name',
'empty' as 'Description',
IO.HitType as 'HitType',
IO.HitRate as 'HitRate',
IO.AddDamage as 'AddDamage',
IO.AddRange as 'AddRange',
IO.NeedArrow as 'NeedArrow',
0 as 'AddDamagePlus'
from {BASE_TABLE_NAME} IO order by IO.MagicNum asc


