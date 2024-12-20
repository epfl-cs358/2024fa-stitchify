import sys
import tkinter as tk
from tkinter import messagebox

def get_c(action, direction):
    if(action == "skip"):
        return "ors" if direction == "right" else "ols"
    elif(action == "take"):
        return "ort" if direction == "right" else "olt"
    else:
        return "fr" if direction == "right" else "fl"

def read_input_file(file_path):
    grid = []
    with open(file_path, 'r') as file:
        for line in file:
            row = line.strip()
            grid.append([(1 if bit == "#" else 0) for bit in row])
    return grid

def interpret_grid(grid):
    commands = []
    direction = "left"
    for row_index, row in enumerate(grid):
        commands.append(get_c("init", direction))
        prev_command = "take" if row[0] == 1 else "skip"
        count = 0
        for bit in row:
            command = "take" if bit == 1 else "skip"
            if command == prev_command:
                count += 1
            else:
                commands.append(get_c(prev_command, direction) + " " + str(count))
                count = 1
                prev_command = command
        commands.append(get_c(prev_command, direction) + " " + str(count))
        max_n = 2500 if direction == "right" else -2500
        commands.append("n " + str(max_n))
        direction = ("left" if direction == "right" else "right")
    return commands

def write_output_file(commands, file_path):
    """Writes each command on its own line in the output file."""
    with open(file_path, 'w') as file:
        for command in commands:
            file.write(command + '\n')

def launch_interface(output_file):
    def toggle_cell(row, col):
        grid_vars[row][col].set(1 - grid_vars[row][col].get())  # Toggle between 0 and 1
        buttons[row][col].config(bg="black" if grid_vars[row][col].get() else "white")

    def confirm():
        grid = []
        for row in grid_vars:
            grid.append([cell.get() for cell in row])
        commands = interpret_grid(grid)
        write_output_file(commands, output_file)
        messagebox.showinfo("Success", f"Interpreted commands have been written to {output_file}")
        root.destroy()

    root = tk.Tk()
    root.title("Knitting Grid Interface")
    grid_frame = tk.Frame(root)
    grid_frame.pack(padx=10, pady=10)

    grid_vars = []
    buttons = []
    for row in range(25):
        row_vars = []
        row_buttons = []
        for col in range(25):
            var = tk.IntVar(value=0)
            btn = tk.Button(grid_frame, width=2, height=1, bg="white",
                            command=lambda r=row, c=col: toggle_cell(r, c))
            btn.grid(row=row, column=col, padx=1, pady=1)
            row_vars.append(var)
            row_buttons.append(btn)
        grid_vars.append(row_vars)
        buttons.append(row_buttons)

    confirm_button = tk.Button(root, text="Confirm", command=confirm)
    confirm_button.pack(pady=10)

    root.mainloop()

def main():
    if len(sys.argv) >= 2 and sys.argv[1].lower() == "interface":
        if len(sys.argv) >= 3:
            output_file = sys.argv[2]
        else:
            output_file = 'output.txt'
        launch_interface(output_file)
    else:
        if len(sys.argv) >= 2:
            input_file = sys.argv[1]
        else:
            input_file = 'input.txt'

        if len(sys.argv) >= 3:
            output_file = sys.argv[2]
        else:
            output_file = 'output.txt'

        grid = read_input_file(input_file)
        commands = interpret_grid(grid)
        write_output_file(commands, output_file)
        print(f"Interpreted commands have been written to {output_file}")

if __name__ == "__main__":
    main()
