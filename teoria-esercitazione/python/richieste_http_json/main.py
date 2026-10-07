import requests

def loadData() -> list[dict]:
    response = requests.get("https://classe5id.altervista.org/api.restful-api.dev/objects/index.php")

    if not response.ok:
        raise Exception(f"ERRORE {response.status_code}: {response.text}")

    return response.json()

def mostValue(dati: list[dict]):
    value = 0.0
    obj = None

    for dato in dati:
        if not isinstance(dato.get("data"), dict):
            continue

        price = dato["data"].get("Price") or dato["data"].get("price")

        if not price:
            continue

        if isinstance(price, float):
            price = float(price)

        if isinstance(price, int):
            price = float(price)

        if isinstance(price, str):
            price = float(price)

        if price > value:
            value = price
            obj = dato

    return obj

def containsPC(dati: list[dict]):
    return [dato for dato in dati if "PC" in dato["name"]]

def worstCapacity(dati: list[dict]):
    print("Errore: dati inconsistenti")

def addData(name):
    headers = {
        "Accept": "application/json"
    }

    for i in range(150):
        data = {
            "id": f"forza_{0 + i}",
            "name": name,
            "data": {
                "price": 0.0000001,
                "capacity": "19092008 PB",
                "description": "QWERTYUIOPLKJHGFDSAZXCVBNM"
            }
        }

        r = requests.post("https://classe5id.altervista.org/api.restful-api.dev/objects/index2.php", json=data, headers=headers)

        if not r.ok:
            raise Exception(f"ERRORE {r.status_code}: {r.text}")

dati = loadData()
print(addData("angelica"))
