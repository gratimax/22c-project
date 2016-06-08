from pyquery import PyQuery as pq
import json
import string
NUM_FOODS = 8789

foods = []
old_used = None
with open('used.json', 'r') as f:
    old_used = json.load(f)

for i in old_used:
  d = pq(filename="../../usndb/{}.html".format(i))
  vn = d("#view-name").text()
  vn = vn.replace("Full Report (All Nutrients):", "").strip()[7:]
  name = vn.split(', ')[0]
  food = {
    'name': name,
    'group': d(".value").eq(0).text()
  }
  tab = d(".nutlist table, .nutlist-hscroll table")
  rows = tab.find("tr.odd")
  data = []
  print(i, name, "({})".format(food["group"]))
  for row in list(rows.items()):
      txt = []
      for td in list(row.find("td").items())[:3]:
        txt.append(td.text())
    #   print(' ', txt)
      data.append(txt)
  name_map = {
    'Energy': 'calories',
    'Protein': 'protein',
    'Total lipid (fat)': 'fat',
    'Carbohydrate, by difference': 'carbs',
    'Fiber, total dietary': 'fiber',
    'Sugars, total': 'sugar'
  }
  for d in data:
      if d[0] in name_map.keys():
          food[name_map[d[0]]] = d[2] + '' + d[1]
  foods.append(food)

with open('foods.json', 'w') as f:
    json.dump(foods, f)
