import customtkinter as ctk
from PIL import Image
from tkinter import filedialog
import os

root = ctk.CTk()
moon_engine_version = "0.1.0"

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
    global project_name_entry, project_location_entry
    new_project_window = ctk.CTkToplevel(root)
    new_project_window.title("Create New Project")
    new_project_window.geometry("400x300")

    project_name_entry = ctk.CTkEntry(
        master=new_project_window,
        width=300,
        height=10,
        placeholder_text="Project Name"
    )
    project_name_entry.pack(pady=10)

    project_location_entry = ctk.CTkEntry(
        master=new_project_window,
        width=300,
        height=10,
        placeholder_text="Project Location"
    )
    project_location_entry.pack(pady=10)

    create_buton = ctk.CTkButton(
        master=new_project_window, 
        corner_radius=0,
        bg_color="#00d11f",
        hover_color="#00d11f",
        fg_color="#00A00D",
        text="Create",
        command= lambda: make_project()
    )
    create_buton.place(x=250, y=260)


def make_project():
    project_name = project_name_entry.get()
    project_location = project_location_entry.get()
    
    if not project_name or not project_location:
        print("Please fill in all fields.")
        return
    
    project_path = os.path.join(project_location, project_name)
    project_file = os.path.join(project_path, f"{project_name}.moonproj")
    project_data = {
        "name": project_name,
        "location": project_location,
        "version": moon_engine_version
    }
    
    try:
        os.makedirs(project_path, exist_ok=True)
        with open(project_file, "w") as f:
            f.write(project_data.__str__())
        print(f"Project '{project_name}' created at '{project_location}'")
    except Exception as e:
        print(f"Error creating project: {e}")




main()

