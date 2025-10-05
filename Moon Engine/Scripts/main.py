import customtkinter as ctk

root = ctk.CTk()

def main():
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("dark-blue")

    root.title("Moon Engine")
    root.geometry("800x600")

    new_project_button = ctk.CTkButton(
        master=root,
        text="New Project",
        width=150,
        height=50,
        bg_color="#007c11",
        fg_color="#00A00D",
        hover_color="#00d11f",
        text_color="white"
    )
    new_project_button.place(x=630, y=10)



    root.mainloop()


if __name__ == "__main__":
    main()