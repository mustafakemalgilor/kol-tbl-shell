
SELECT
IO.MagicNum as 'iNum',
IO.Name as 'Name',
IO.Description as 'Description',
IO.ValidGroup as 'ValidGroup',
IO.NationChange as 'NationChange',
IO.MonsterNum as 'MonsterNum',
IO.TargetChange as 'TargetChange',
IO.StateChange as 'StateChange',
IO.Radius as 'Radius',
IO.HitRate as 'Hitrate',
IO.Duration as 'Duration',
IO.AddDamage as 'AddDamage',
IO.Vision as 'Vision',
IO.NeedItem as 'NeedItem'
from {BASE_TABLE_NAME} IO order by IO.MagicNum asc


