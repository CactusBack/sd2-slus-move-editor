# SD2 SLUS Move Editor

<img src="https://github.com/user-attachments/assets/73fb6a06-861b-4c72-9057-f53dece79cb5" alt="SD2 SLUS Move Editor Screenshot" width="800"/>

A small open-source ImGui-based desktop tool for viewing and editing move data stored inside the `SLUS_012.34` executable used by the NTSC version of *WWF SmackDown! 2: Know Your Role*.

This project focuses on:

* Binary file parsing and safe modification
* Immediate-mode GUI design with Dear ImGui
* Clean and minimal C++ project structure
* Preserving original file layout and data

## Features

* View and edit move entries in the SLUS file
* Supports both **original** and **expanded (new moves hack)** move tables
* Edit move properties including:
  * ID
  * Type
  * Category
  * Impact
  * Limb damage values (Head/Torso/Arms/Legs)
* Hex editing of raw move entry data
* Automatic move name lookup via `WAZA.dat` from `CAW.pac`
* Add and delete move entries
* Preserves file size, offsets, and padding when saving

## Format Documentation

If you are interested in the breakdown of the SLUS move data format, you can find it here: [How Damage Works in SmackDown 2](https://docs.google.com/document/d/1FTKJWwvAdlmFp0uq7qq2erMiQhkUPrjcuW9BXvSpwUY)

This editor follows the structure described in that document and preserves unknown data.

## Build Instructions

### Requirements

* C++20 compatible compiler
* OpenGL 3.3+
* GLFW
* GLAD
* Dear ImGui

### Building (Visual Studio – Windows)

1. Clone the repository:

   ```bash
   git clone https://github.com/CactusBack/sd2-slus-move-editor.git
   ```

2. Open the project in Visual Studio

3. Ensure the following dependencies are available:

   * GLFW linked
   * GLAD source included
   * Dear ImGui source included

4. Build and run

> Note: The project currently targets Windows + OpenGL. Other platforms may require minor adjustments.

## Usage

1. Place the following files in the same directory as the executable:

   * `SLUS_012.34`
   * `WAZA.dat`

2. Launch the editor

3. Edit move values as needed

4. Click **Save File** to write changes back to the SLUS file

If the new moves expansion hack is detected, both **Old** and **New** move tables will be available.

## License

MIT License

See `LICENSE.txt` for details.

## Third-Party Assets

This project includes the **Inconsolata** font, licensed under the  **SIL Open Font License (OFL)**.

Font source: https://github.com/googlefonts/Inconsolata

## AI-Assisted Development Disclosure

This project was developed with assistance from **ChatGPT (OpenAI)**.

AI assistance was used for:

* Code organization and refactoring suggestions
* Dear ImGui usage guidance
* C++ best-practice discussions

All design decisions, testing, and final implementation choices were made by the project author.

## Disclaimer

This tool is not affiliated with Sony, WWE, THQ, or Yuke’s.  
It is intended for educational and personal modding use only.

## Contributing

Pull requests are welcome. If you have ideas for improvements or refactors, feel free to open an issue.

## Contact Email

smackdown2modded@gmail.com
