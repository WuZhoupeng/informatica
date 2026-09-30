import requests

def loadData() -> list[dict]:
    response = requests.get("https://classe5id.altervista.org/api.restful-api.dev/objects/index.php")

    if not response.ok:
        raise Exception(f"ERRORE {response.status_code}: {response.text}")

    return response.json()

def mostValue(dati: list[dict]):
    value = 0.0

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

        value = price if price > value else value

    return value

dati = loadData()
print(mostValue(dati))
