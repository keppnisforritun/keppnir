from enum import Enum

input = input()

class Destination(Enum):
    REYKJAVIK = "Reykjavik"
    AKUREYRI = "Akureyri"

ans_map = {
    "Reykjavik": Destination.REYKJAVIK,
    "Kopavogur": Destination.REYKJAVIK,
    "Hafnarfjordur": Destination.REYKJAVIK,
    "Reykjanesbaer": Destination.REYKJAVIK,
    "Akureyri": Destination.AKUREYRI,
    "Gardabaer": Destination.REYKJAVIK,
    "Mosfellsbaer": Destination.REYKJAVIK,
    "Arborg": Destination.REYKJAVIK,
    "Akranes": Destination.REYKJAVIK,
    "Fjardabyggd": Destination.AKUREYRI,
    "Mulathing": Destination.AKUREYRI,
    "Seltjarnarnes": Destination.REYKJAVIK
}

print(ans_map[input].value)
