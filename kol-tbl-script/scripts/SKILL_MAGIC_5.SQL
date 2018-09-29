
SELECT
IO.MagicNum as 'iNum',
'empty' as 'Name',
'empty' as 'Description',
IO.Type as 'Type',
IO.ExpRecover as 'ExpRecover',
IO.NeedStone as 'NeedStone'
from {BASE_TABLE_NAME} IO order by IO.MagicNum asc
