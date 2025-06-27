# Minimal Layout, Maximum Efficiency

A collection of macro keyboards to boost your productivity without crowding your workspace.

![Project Image](https://github.com/ImSeanConroy/macro-keyboard/blob/main/.github/repo-img.png)

## Features and Development Roadmap

This project is a work in progress, the following outlines the current features and planned improvements:

### Current Features
- Compact Design: Space-saving with minimal desk footprint.
- Customizable Macros: Assign any key functions to match your workflow.
- Layout Variations: Supports various configurations (e.g., 1x1, 1x2, 1x4, 2x4, and 3x3).

### Upcoming Features
- Bluetooth Functionality: Add and test wireless connectivity.
- Custom PCB Design: Move away from prebuilt Seeed Studio development boards. (A previous attempt was made, but limited electronics knowledge made debugging and identifying issues difficult.)

## Getting Started

1. **Open the Project** - Open the `.kicad_pro` file in KiCad to view the project.
2. **Review the Design** - Inspect the schematic and PCB layout to ensure it meets your needs.
3. **Customize or Export** - Make any modifications and export the Gerber files for fabrication.
4. **Order the PCB** - Submit the Gerber files to your preferred PCB manufacturer.
5. **Get the Components** - Purchase the components from the BOM and a compatible board.
6. **3D Print the Case** - Download the STL files for your chosen configuration and print them on a 3D printer.
7. **Assemble the Hardware** - Solder the components and assemble the board and case.
8. **Upload the Firmware** - Connect the board via USB and upload the firmware.

## Required Components

The following are the required components to build any of the macro keyboards:

| Quantity | Component | Description | Source |
| - | - | - | - |
| 1 | Seeed XIAO SAMD21 | Microcontroller board | [PiHut](https://thepihut.com/products/seeed-xiao-samd21?srsltid=AfmBOopsKYftJU7zJh318_QIbgNfs8Iwz2q-IXUMCA7OXGZDiutoXrOy) |
| 12 | Kailh Mechanical Key Switches | Tactile switches | [PiHut](https://thepihut.com/products/kailh-mechanical-key-switches-linear-red-12-pack?variant=40151684677827) |
| 20 | Kailh Switch Sockets | For hot-swapping switches | [PiHut](https://thepihut.com/products/kailh-switch-sockets-for-mx-compatible-mechanical-keys-20-pack?variant=40019715588291) |
| 12 | White DSA Keycaps | Keycap set | [PiHut](https://thepihut.com/products/white-dsa-keycaps-for-mx-compatible-switches-10-pack?variant=40000301301955) |
| 12 | Orange DSA Keycaps | Keycap set | [PiHut](https://thepihut.com/products/orange-dsa-keycaps-for-mx-compatible-switches-10-pack?variant=40000347439299) |
| 10 | Neon Green DSA Keycaps | Keycap set | [PiHut](https://thepihut.com/products/neon-green-dsa-keycaps-for-mx-compatible-switches-10-pack?variant=40000348520643) |

## Contributing

Contributions are welcome. Please open an issue or submit a pull request for any enhancements or bug fixes.

## License

This project is Distributed under the MIT License - see the [LICENSE](LICENSE) file for information.

## Support

If you are having problems, please let me know by [raising a new issue](https://github.com/ImSeanConroy/macro-keyboard/issues/new/choose).

## Acknowledgments

This project was made possible thanks to the following resources:

- [Masterzen's Blog](https://www.masterzen.fr/) - Designing a keyboard from scratch
- [Keyboard Designer Wiki](https://wiki.ai03.com/books/pcb-design/chapter/pcb-designer-guide) - PCB Designer Guide 
- [Seeed Studio Wiki](https://wiki.seeedstudio.com/Seeeduino-XIAO/#resourses) - Getting Started with Seeed Studio XIAO SAMD21