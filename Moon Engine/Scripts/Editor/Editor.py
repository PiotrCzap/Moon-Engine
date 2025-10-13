import customtkinter as ctk
from PIL import Image
import tkinter as tk
import os

Editor = ctk.CTk()
Font = ("Arial", 20)

def Editor_Window():
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("dark-blue")

    Editor.title("Moon Engine - Editor")
    Editor.geometry("1920x1080+0+0")

    Editor_hierarchy_frame = ctk.CTkFrame(
        master=Editor,
        width=350,
        height=600,
        corner_radius=0,
        fg_color="#505050",
        border_color="#FFFFFF",
        border_width=2
    )
    Editor_hierarchy_frame.place(x=0, y=0)

    Editor_inspector_frame = ctk.CTkFrame(
        master=Editor,
        width=350,
        height=1080,
        corner_radius=0,
        fg_color="#505050",
        border_color="#FFFFFF",
        border_width=2
    )
    Editor_inspector_frame.place(x=1570, y=0)

    Editor_filesystem_frame = ctk.CTkFrame(
        master=Editor,
        width=1570,
        height=400,
        corner_radius=0,
        fg_color="#464646",
        border_color="#FFFFFF",
        border_width=2
    )
    Editor_filesystem_frame.place(x=0, y=600)

    Hierarchy_label = ctk.CTkLabel(
        master=Editor_hierarchy_frame,
        text="Hierarchy",
        text_color="white",
        font=(Font, 20)
    )
    Hierarchy_label.place(x=10, y=5)

    inspertor_label = ctk.CTkLabel(
        master=Editor_inspector_frame,
        text="Inspector",
        text_color="white",
        font=(Font, 20)
    )
    inspertor_label.place(x=10, y=5)

    filesystem_label = ctk.CTkLabel(
        master=Editor_filesystem_frame,
        text="Filesystem",
        text_color="White",
        font=(Font, 20)
    )
    filesystem_label.place(x=10, y=5)
    

    def Empty_component():
        Empty_component_frame = ctk.CTkFrame(
            master=Editor_hierarchy_frame,
            width=330,
            height=100,
            corner_radius=0,
            fg_color="#000000",
            border_color="#FFFFFF",
            border_width=2
        )
        Empty_component_frame.place(x=10, y=50)

        Empty_component_label = ctk.CTkLabel(
            master=Empty_component_frame,
            text="No Component Selected",
            text_color="white",
            font=(Editor.Font, 20)
        )
        Empty_component_label.place(x=50, y=30)



    Editor.mainloop()

    


Editor_Window()
