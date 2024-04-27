from PIL import Image

# Funkcija za generisanje slika
def generate_images(num_images):
    # Generiše i čuva slike
    for i in range(1, num_images + 1):
        size = (i * 100, i * 100)
        image = Image.new("RGB", size, "red")
        image.save(f"input{i}.bmp")
        # image.save(f"C:\\Users\\Korisnik.DESKTOP-JVOQTMK\\source\\repos\\ARproject2\\x64\\Debug\\input{i}.bmp")


# Interaktivni unos korisnika za broj slika
def main():
    # Otvaranje datoteke za pisanje
    with open("num_images.txt", "w") as file:
    # with open("C:\\Users\\Korisnik.DESKTOP-JVOQTMK\\source\\repos\\ARproject2\\x64\\Debug\\num_images.txt", "w") as file:
        # Korisnik unosi broj test slika
        num_images = int(input("Unesite broj test slika: "))
        # Upisivanje broja test slika u datoteku
        file.write(str(num_images))

    # Generisanje slika
    generate_images(num_images)
    print(f"Generisano je {num_images} test slika.")

if __name__ == "__main__":
    main()

