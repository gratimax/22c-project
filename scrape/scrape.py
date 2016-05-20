import requests

NUM_FOODS = 8789

def mk_food_url(id):
  return 'https://ndb.nal.usda.gov/ndb/foods/show/' + str(id) + \
  '?fgcd=&man=&lfacet=&count=&max=35&sort=&qlookup=&offset=0&format=Full&new=&measureby='

for id in range(1, NUM_FOODS + 1):
  print 'Requesting {}'.format(id)  
  r = requests.get(mk_food_url(id))
  with open('usndb/' + str(id) + '.html', 'w') as f:
    f.write(r.content)

