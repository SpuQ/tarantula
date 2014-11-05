README.md

These c libraries are meant to increase productivity on developing stuff with
Digital AD Technics' Expansion Board REV2.1 "Tarantula".

04/11/2014
- Start clean-up of an aweful lot of quick&dirty code snippets (not in repository yet)
 -> onboard io driver included
- Start development of gpio wrapper (api in .h file), according to Andreas' needs

05/11/2014
- Andreas took over the coding behind the api-functions, a lot of lookups and/or
switches comming your way bro!
- Start development of the dedicated hardware-dependend I/O layer + api, just to elimintate
directives like 'DDRA' in higher levels of code (for the softwarepeople)
