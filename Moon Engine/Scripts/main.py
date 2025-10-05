import customtkinter as ctk

root = ctk.CTk()

def main():
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("dark-blue")

    root.title("Moon Engine")
    root.geometry("800x600")

    ctk.CTkButton(
        root,
        text="New Project",
        bg_color="#009620",
        fg_color="#000000",
        width=200,
        height=50,
    )



    root.mainloop()


if __name__ == "__main__":
    main()