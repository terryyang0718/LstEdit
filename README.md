# AutoSchGen  
Automated Schematic Generator & Netlist Processor for CAD/IC Design Flows

AutoSchGen is a C++ tool designed for semiconductor and IC schematic workflows.  
It parses `.lst`, `.sym`, `.net` and directory structures to automatically:

- Extract SCH blocks  
- Detect and index IP / DIP / AIP / IO / PIN  
- Generate hierarchical schematic pages  
- Reconstruct symbol locations  
- Produce net connections  
- Remove or edit lines in LSTs  
- Convert LST → SCH with auto-placement  
- Handle buses, pin types, and multi-level hierarchy  

This tool is especially useful for legacy CAD flows where symbol libraries, IP blocks,  
and schematic pages must be auto-constructed through file parsing.

---

## ✨ Features

### **📌 LST Processing**
- Extracts `#SCH:` sections and corresponding detail blocks  
- Automatically deduplicates repeated schematic blocks  
- Supports editing and deleting specific LST line indices  
- Generates new LST output files with time-stamped filenames  

### **📌 Symbol / IP Handling**
- Searches IP definitions across directories (aip/dip/sym/macro)  
- Auto-detects pin definitions, pin directions, and bus width  
- Local fallback search (`ip_tmp/`) for missing symbols  

### **📌 Automatic Schematic Generation**
- Places IP symbols on schematic pages  
- Auto-computes spacing (x/y/z placement)  
- Generates net connections based on pin type (IN/OUT/BI)  
- Supports bus syntax like `[7:0]`, `[max:min]`  
- Produces page files with metadata (version, date, coordinates)

### **📌 Utility Functions**
- String parsing helpers  
- Net grouping/compression (`Combine_net`)  
- Time and date stamping  
- Directory walking  
- Coordinate transformations (L ↔ I mapping)

