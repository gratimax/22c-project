from pyquery import PyQuery as pq
import json
import string
NUM_FOODS = 8789

foods = {}
old_used = None
with open('used.json', 'r') as f:
    old_used = json.load(f)
used = set()

def mostly_uppercase(s):
    u = len([c for c in s if c in string.ascii_uppercase])
    return u/len(s) > 0.5

for i in old_used:
  d = pq(filename="../usndb/{}.html".format(i))
  vn = d("#view-name").text()
  vn = vn.replace("Full Report (All Nutrients):", "").strip()[7:]
  name = vn.split(', ')[0]
  food = {
    'name': name,
    'group': d(".value").eq(0).text()
  }
  if name not in foods and not mostly_uppercase(name) and 'KRAFT' not in name and 'KELLOG' not in name:
      foods[name] = food
      used.add(i)
  if i % 100 == 0:
      print("foods in table = {}, total foods = {} ({:0.1%} used)".format(len(foods), i, len(foods)/i))

with open('foods.json', 'w') as f:
    json.dump(foods, f)

with open('used.json', 'w') as f:
    json.dump(list(used), f)
