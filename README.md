<div  align="center"> 

# Open Modular Controller for Automation Technologies
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)](https://opensource.org/licenses/MIT)
[![DOI](https://zenodo.org/badge/DOI/10.1109/ICPS59941.2024.10639979.svg)](https://doi.org/10.1109/ICPS59941.2024.10639979)

[Joao Potier](https://pt.linkedin.com/in/jo%C3%A3o-potier-5b1301228?trk=public_profile_samename-profile)<sup>1</sup>, 
[Miguel Arvana](https://scholar.google.com/citations?user=UBvr388AAAAJ&hl=pt-PT)<sup>1</sup>,
[Leandro Filipe](https://scholar.google.pt/citations?user=SoIohJwAAAAJ&hl=en)<sup>1</sup>,
[Fabio M-Oliveira](https://www.researchgate.net/profile/Fabio-M-Oliveira)<sup>1</sup>,
[Andre Rocha](https://scholar.google.pt/citations?user=k1GIyqcAAAAJ&hl=pt-PT)<sup>1</sup>,
[Jose Barata](https://scholar.google.pt/citations?user=4G8tKCsAAAAJ&hl=en)<sup>1</sup>

<sup>1</sup> **NOVA School of Science and Technology, Center of Technology and Systems (UNINOVA-CTS)**,
and Associated Lab of Intelligent Systems (LASI), NOVA University
Lisbon, 2829-516 Lisbon, Portugal

<table>
  <tr>
    <td style="vertical-align: top;">
      This work proposes the development of a controller, with modularity and flexibility as the core ideas, that allows for the integration of open-source standards like the proprietary technologies used in emergent factories and automation technologies. The implementation of this architecture led to the development of a prototype modular industrial controller that is, on average, a quarter of the cost of the new generation of industrial controllers. The developed controller was tested and validated using some educational kits.
    </td>
    <td style="vertical-align: top;">
      <img style="width: 1100px" src="imgs/PCB_4.jpg" alt="pcb" width="200"/>
    </td>
  </tr>
</table>

</div>

## <div align="center">Get Started</div>
Follow these steps to create your own functional PCB and set up the ESP:

1. **Order or Print the PCB**
   - Locate the PCB Gerber files in the repository at [Gerber.zip](./docs/pcb/Gerbers.zip).
   - Upload this zip file to a PCB manufacturer (such as [JLCPCB](https://jlcpcb.com/) or a similar service) to order the PCB, or print it yourself if you have access to the necessary equipment.

2. **Gather Components**
   - Obtain all components listed in [materials.xtml](./docs/pcb/schematic_and_materials/materials.pdf).
   - Ensure that you source parts that match the specifications provided for optimal functionality.

3. **Assemble the PCB**
   - Carefully assemble the PCB following the schematic available [here](./docs/pcb/Schematic_and_materials/schematic.png).
   - Use appropriate tools and ensure correct orientation and placement of components.

4. **Test the PCB**
   - Before powering up, inspect the PCB for short circuits, weak solder joints, or other assembly issues.
   - Use a multimeter to verify connections and confirm proper voltage levels across components.

5. **Program and Test the ESP**
   - Program the ESP with the provided code, following the setup instructions in the [code](./src/) folder.
   - Test each pin individually to verify its input and output behavior. The ESP should handle a standard 24V input/output.

If all tests pass, congratulations! Your board is now ready for operation.

---

### Usage instructions
Once your PCB and ESP setup is complete, you can begin using the device. The ESP manages the input and output for each control pin, with a standard operating voltage of 24V. Please note:

- **Control Limitations**: These pins are designed for control signals only. Avoid applying high current loads to prevent damage.
- **Testing & Example Code**: Refer to the [tests](./tests/) folder for example code and tests that help validate board functionality. Additionally, the [code](./src/) folder provides example libraries and initial setup steps.

@TODO - redirecionar exatamente para os scripts a usar, circuito e testes

Follow these guidelines, and your project should operate as expected!

---

### Project Structure
For you to better understand this repository organization here is a quick overview of its structure and where to find what you might be looking for:
```c
open-modular-controller
├── docs                # documentation assets
│   ├── circuits            # digital and analog circuit study
│   ├── pcb                 # pcb assets and materials
│   └── thesis.pdf          # master thesis
├── imgs                # images from this project
├── src                 # evaluation code
│   ├── libs                # developed libraries
│   └── circuit.ino         # main circuit script
└── tests               # test examples scripts
```

## <div align="center">Documentation</div>

The [docs](./docs/) directory contains extensive resources, including schematics, materials lists, and PCB files, as well as the original master’s dissertation that inspired this project. Explore this folder to access all necessary assets for building, assembling, and understanding the hardware.

> **Note**: The resistors R1, R4, R5, R6, R9, R13, and R21, **originally specified as 1.1K, have been updated to 33K** in both the schematic and materials list. This adjustment was made due to performance issues with certain conveyor belts that were not functional with the previous resistor values. Documenting this change is essential for any future debugging.


## <div align="center">Contribution Guidelines</div>
NOVA RICS Open Lab open source, and we welcome contributions from the community! See the [Contribution](CONTRIBUTING.md) guide for more information on the development workflow and the internals of the wandb library. For project related bugs and feature requests, visit [GitHub Issues](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller/issues) or contact novaricsopenlab@gmail.com

## <div align="center">Citation</div>
If you use or intend to build on top of  the work in this repo, please consider citing our project:
```bibtex
@inproceedings{10639979,
  author={Potier, João and Arvana, Miguel and Filipe, Leandro and M-Oliveira, Fabio and Rocha, Andre Dionisio and Barata, Jose},
  booktitle={2024 IEEE 7th International Conference on Industrial Cyber-Physical Systems (ICPS)}, 
  title={Development of an Open, Modular Controller for Training in Emergent Automation Technologies}, 
  year={2024},
  doi={10.1109/ICPS59941.2024.10639979}
}
```

## <div align="center">License</div>
This repository is released under the MIT License. Please see the [LICENSE](LICENSE) file for more details.

## <div align="center">Contacts</div>
For any questions regarding this or any other project please contact us at novaricsopenlab@gmail.com or enroll in our [Discussionw Forum](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller/discussions) for sharing your ideas and sharing projects.
