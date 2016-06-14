import json

foods = []

def make_food_line(food):
 #  * for ingredients, <rest...> = "<foodGroup>" <calories> <fat> <protein> <fiber> <sugar> <carbs>
    s = "1 {id} \"{name}\" \"{foodGroup}\" {calories} {fat} {protein} {fiber} {sugar} {carbs}".format(
            id=food["id"],
            name=food["name"].replace('"', ''),
            foodGroup=food['group'],
            calories=food.get('calories','0kcal')[:-4],
            fat=food.get('fat', '0.0g')[:-1],
            protein=food.get('protein', '0.0g')[:-1],
            fiber=food.get('fiber', '0.0g')[:-1],
            sugar=food.get('sugar', '0.0g')[:-1],
            carbs=food.get('carbs', '0.0g')[:-1],
            )
    return s

with open('foods.json', 'r') as f:
    foods = json.load(f)

with open('foods.txt', 'w') as f:
    for food in foods:
        f.write(make_food_line(food))
        f.write('\n')

print(foods)
