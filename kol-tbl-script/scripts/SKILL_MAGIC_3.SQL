
SELECT
IO.MagicNum as 'iNum',
'empty' as 'Name',
'empty' as 'Description',
IO.Radius as 'Radius',
0 as 'Angle',
IO.DirectType as 'DirectType',
IO.FirstDamage as 'FirstDamage',
0 as 'EndDamage',
IO.TimeDamage as 'TimeDamage',
IO.Duration as 'Duration',
IO.Attribute as 'Attribute'
from {BASE_TABLE_NAME} IO order by IO.MagicNum asc


