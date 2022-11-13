# WinrarNoPopup
## How to use
Drag and drop WinRAR onto WinrarNoPopup. Profit.
A backup is created in case something goes wrong.
You can delete WinrarNoPopup afterwards since the changes are made to WinRAR.exe itself.

## Technicals
A signature scan finds the two places where the two different kinds of popups are made and just replaces them with NOPs.

## Images of patched code (from ghidra)

![Capture](https://user-images.githubusercontent.com/115924828/201542174-90fc1c70-7ec6-495e-bfda-6ce968cc47d1.PNG)
![Capture](https://user-images.githubusercontent.com/115924828/201542196-5ca6207d-4b2c-470f-b427-7df892b0637e.PNG)
