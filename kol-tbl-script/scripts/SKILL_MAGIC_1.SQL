
SELECT
IO.MagicNum as 'iNum',
'empty' as 'Name',
'empty' as 'Description',
IO.Type as 'Type',
IO.HitRate as 'HitRate',
IO.Hit as 'Hit',
IO.AddDamage as 'AddDamage',
IO.Delay as 'Delay',
IO.ComboType as 'ComboType',
IO.ComboCount as 'ComboCount',
IO.ComboDamage as 'ComboDamage',
IO.Range as 'Range'
from {BASE_TABLE_NAME} IO order by IO.MagicNum asc


