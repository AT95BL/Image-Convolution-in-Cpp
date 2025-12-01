from PIL import Image

# Function for generating images
def generate_images(num_images):
    # Generiše i čuva slike
    for i in range(1, num_images + 1):
        size = (i * 100, i * 100)
        image = Image.new("RGB", size, "red")
        image.save(f"input{i}.bmp")
        # image.save(f"C:\\Users\\Korisnik.DESKTOP-JVOQTMK\\source\\repos\\ARproject2\\x64\\Debug\\input{i}.bmp")


# Interactive user input for the number of images
def main():
    # Opening the file for writing
    with open("num_images.txt", "w") as file:
    # with open("C:\\Users\\Korisnik.DESKTOP-JVOQTMK\\source\\repos\\ARproject2\\x64\\Debug\\num_images.txt", "w") as file:
        # The user enters the number of test images
        num_images = int(input("Unesite broj test slika: "))
        # Writing the number of test images to the file
        file.write(str(num_images))

    # Generating images
    generate_images(num_images)
    print(f"Generisano je {num_images} test slika.")

if __name__ == "__main__":
    main()

