import customtkinter as ctk
import os
from PIL import Image
import tkinter as tk
import Editor


def Empty_component():
    Empty_component_frame = ctk.CTkFrame(
        master=Editor.Editor,
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