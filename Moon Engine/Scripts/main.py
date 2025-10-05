import customtkinter as ctk

root = ctk.CTk()

def main():
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("dark-blue")

    root.title("Moon Engine")
    root.geometry("800x600+550+200")

    new_project_button = ctk.CTkButton(
        master=root,
        text="New Project",
        width=150,
        height=50,
        bg_color="#007c11",
        fg_color="#00A00D",
        hover_color="#00d11f",
        text_color="white",
        command=create_new_project
    )
    new_project_button.place(x=630, y=10)

    root.mainloop()

def create_new_project():
    new_project_window = ctk.CTkToplevel(root)
    new_project_window.title("Create New Project")
    new_project_window.geometry("400x300")

    ctk.CTkEntry(master=new_project_window, width=300, height=10, placeholder_text="Project Name").pack(pady=10)
    ctk.CTkEntry(master=new_project_window, width=300, height=10, placeholder_text="Project Location").pack(pady=10)
    ctk.CTkButton(master=new_project_window, corner_radius=0, bg_color="#00d11f", hover_color="#00d11f", fg_color="#00A00D", text="Create", command=lambda: print("Project Created")).place(x=250, y=260)
    

main()

