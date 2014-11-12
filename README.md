tarantula README.md

These c libraries are meant to increase productivity on developing stuff with
Digital AD Technics' Expansion Board REV2.1 "Tarantula".

12/11/2014
- added the loopback() and instruct() functions to the Qcumber API

08/11/2014
- Start revision of SpuQcom, under the new name "Qcumber". Added API to repository.

05/11/2014
- Andreas took over the coding for the gpio wrapper functions
- Start development of the dedicated hardware-dependend I/O layer + api, just to elimintate
directives like 'DDRA' in higher levels of code (for the softwarepeople)

04/11/2014
- Start clean-up of an aweful lot of quick&dirty code snippets (not in repository yet)
 -> onboard io driver included
- Start development of gpio wrapper (api in .h file), according to Andreas' needs
