from pyquery import PyQuery as pq
import json
import string
NUM_FOODS = 8789

foods = {}
old_used = None
with open('used.json', 'r') as f:
    old_used = json.load(f)

for i in old_used:
  d = pq(filename="../usndb/{}.html".format(i))
  vn = d("#view-name").text()
  vn = vn.replace("Full Report (All Nutrients):", "").strip()[7:]
  name = vn.split(', ')[0]
  food = {
    'name': name,
    'group': d(".value").eq(0).text()
  }
  tab = d(".nutlist table")
  print(tab)

with open('foods.json', 'w') as f:
    json.dump(foods, f)
