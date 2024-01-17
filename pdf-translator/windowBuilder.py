import os
import tkinter as tk
from tkinter import filedialog

def on_drop(event):
    filepath = event.data
    entry_path.delete(0, tk.END)
    entry_path.insert(0, filepath)

def browse_file():
    file_path = filedialog.askopenfilename(filetypes=[("Text files", "*.txt"), ("All files", "*.*")])
    entry_path.delete(0, tk.END)
    entry_path.insert(0, file_path)

def on_drag_enter(event):
    canvas.itemconfig(drop_target, fill="lightblue")

def on_drag_leave(event):
    canvas.itemconfig(drop_target, fill="lightgray")

def on_drag_drop(event):
    filepath = event.data
    entry_path.delete(0, tk.END)
    entry_path.insert(0, filepath)
    canvas.itemconfig(drop_target, fill="lightgray")

def main():
    global entry_path
    global canvas
    root = tk.Tk()
    root.title("Canvas and Dropbox Example")
    root.geometry("800x600")

    frame = tk.Frame(root, padx=10, pady=10)
    frame.pack(expand=True, fill="both")

    # Create a canvas widget
    canvas = tk.Canvas(frame, width=800, height=400, bg="white")
    canvas.grid(row=0, column=0, columnspan=2, pady=10)

    # Entry widget to display the selected file path
    entry_path = tk.Entry(frame, width=40)
    entry_path.grid(row=1, column=0, padx=5, pady=5)

    # Browse button to open file dialog
    button_browse = tk.Button(frame, text="Browse", command=browse_file)
    button_browse.grid(row=1, column=1, padx=5, pady=5)

    # Create a drop target using a rectangle on the canvas
    global drop_target
    drop_target = canvas.create_rectangle(100, 100, 700, 300, fill="lightgray", outline="black")
    
    # Bind events for drag and drop
    canvas.bind("<Enter>", on_drag_enter)
    canvas.bind("<Leave>", on_drag_leave)
    canvas.bind("<Drop>", on_drag_drop)

    root.mainloop()
main()