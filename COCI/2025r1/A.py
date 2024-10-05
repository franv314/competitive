L1 = input()
L2 = input()
L3 = input()

pin = L1[15:26]
year = L2[0:2]
month = L2[2:4]
day = L2[4:6]
name, surname = L3.split('<<')[:2]

if int(year) < 25:
    year = "20" + year
else:
    year = "19" + year

name = name[0] + name[1:].lower()
surname = surname[0] + surname[1:].lower()

print(f"Ime: {name}")
print(f"Prezime: {surname}")
print(f"Datum rodjenja: {day}-{month}-{year}")
print(f"OIB: {pin}")
