import customtkinter as ctk

def pokaz():
    wartosc = entry.get()
    print("Zawartość:", wartosc)

root = ctk.CTk()
entry = ctk.CTkEntry(root, placeholder_text="Wpisz coś...")
entry.pack(padx=20, pady=10)

btn = ctk.CTkButton(root, text="Pobierz", command=pokaz)
btn.pack(padx=20, pady=10)

root.mainloop()
