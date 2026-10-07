import csv

def loadCSV():
    with open("./comuni.csv", mode="r", encoding="utf-8") as file:
        lettore = csv.DictReader(file, delimiter=",")

        return list(lettore)

def existProvincia(dati: list, input_user: str):
    for dato in dati:
        if dato["den_prov"].lower() == input_user.lower().strip():
            return True

    return False

def listComuniByProvincia(dati: list, input_user: str):
    if not existProvincia(dati, input_user):
        return []

    comuni = [dato for dato in dati if dato["den_prov"].lower() == input_user.lower().strip()]

    return comuni

def listProvinceByStart(dati: list, input_user: str):
    province = [dato for dato in dati if dato["den_prov"].lower().startswith(input_user.lower().strip())]

    return province

def listComuniByStart(dati: list, input_user: str):
    province = [dato for dato in dati if dato["comune"].lower().startswith(input_user.lower().strip())]

    return province

dati = loadCSV()
dato_input = input("Digita una provincia: ")
print(listComuniByStart(dati, dato_input))